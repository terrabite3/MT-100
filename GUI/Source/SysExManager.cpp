/*
  ==============================================================================

    SysExManager.cpp
    Created: 16 Aug 2020 1:56:29pm
    Author:  Stefan Titus

  ==============================================================================
*/

#include "SysExManager.h"

using namespace juce;

SysExManager::SysExManager()
: mThread(std::make_unique<SysExThread>(this))
{
    mThread->startThread();
}

SysExManager::~SysExManager()
{
    mThread->stopThread(100);
}

void SysExManager::setUpdateMode(UpdateMode mode)
{
    const ScopedLock lock(mUpdateModeLock);
    mUpdateMode = mode;
}

void SysExManager::flush()
{
    const ScopedLock lock(mUpdateModeLock);
    mFlush = true;
}

void SysExManager::flushAll()
{
    const ScopedLock lock(mUpdateModeLock);
    mFlushAll = true;
}

void SysExManager::openMidiIn(String name)
{
    // If we're already using the requested MIDI device, do nothing
    if (mMidiIn && mMidiIn->getName() == name) return;
    
    for (auto input : MidiInput::getAvailableDevices())
    {
        if (name == input.name)
        {
            mMidiIn = MidiInput::openDevice(input.identifier, this);
            if (mMidiIn)
                mMidiIn->start();
            return;
        }
    }
    
    // If we didn't find the requested MIDI device (perhaps because it's "Disabled"), close the current device
    mMidiIn = nullptr;
}

void SysExManager::openMidiOut(juce::String name)
{
    const ScopedLock lock(mMidiOutLock);
    // If we're already using the requested MIDI device, do nothing
    if (mMidiOut && mMidiOut->getName() == name) return;
    
    
    for (auto output : MidiOutput::getAvailableDevices())
    {
        if (name == output.name)
        {
            mMidiOut = MidiOutput::openDevice(output.identifier);
            return;
        }
    }
    
    // If we didn't find the requested MIDI device (perhaps because it's "Disabled"), close the current device
    mMidiOut = nullptr;
}

void SysExManager::updateFromProperty(IProperty* prop)
{
    const ScopedLock lock(mUserMemLock);
    
    prop->writeMemory(mUserMem);
    
    mUserMemDirty = true;
}

SysExManager::SysExThread::SysExThread(SysExManager* parent)
: Thread("SysExThread")
, mParent(parent)
{}

void SysExManager::SysExThread::run()
{
    while (!threadShouldExit())
    {
        sleep(10);
        
        bool shouldSend;
        bool shouldSendAll;
        {
            const ScopedLock lock(mParent->mUpdateModeLock);
            
            shouldSend = mParent->mFlush || (mParent->mUpdateMode == UpdateMode::AUTO);
            shouldSendAll = mParent->mFlushAll;
            
            mParent->mFlush = false;
            mParent->mFlushAll = false;
        }
        
        if (!(shouldSend || shouldSendAll)) continue;
        
        SysExMemory diff;
        {
            const ScopedLock lock(mParent->mUserMemLock);
            if (!mParent->mUserMemDirty)
            {
                continue;
            }
            
            diff = mParent->mUserMem.diff(mParent->mDeviceMem);
        }
        
        auto diffMessage = diff.writeSyx();
        
        // Update our cache of the device memory with the changes
        mParent->mDeviceMem.readSyx(diffMessage);
        
        // If the user asked us to send the entire memory cache contents, replace the message with our cache
        if (shouldSendAll)
        {
            diffMessage = mParent->mDeviceMem.writeSyx();
        }
        
        if (diffMessage.empty()) continue;
        
        // Strip off the start and end bytes because createSysExMessage() adds them too
        diffMessage.erase(diffMessage.begin());
        diffMessage.erase(diffMessage.end() - 1);
        
        auto message = MidiMessage::createSysExMessage((void*)diffMessage.data(), (int)diffMessage.size());
        
        {
            const ScopedLock lock(mParent->mMidiOutLock);
            if (mParent->mMidiOut) mParent->mMidiOut->sendMessageNow(message);
        }
    }
    
    
}


void SysExManager::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    const ScopedLock lock(mMidiOutLock);
    if (mMidiOut) mMidiOut->sendMessageNow(message);
}

