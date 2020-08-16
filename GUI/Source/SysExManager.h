/*
  ==============================================================================

    SysExManager.h
    Created: 16 Aug 2020 1:56:29pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "Memory/SysExMemory.h"
#include "Property/IProperty.h"

#include <JuceHeader.h>

class SysExManager : public juce::MidiInputCallback
{
public:
    SysExManager();
    ~SysExManager();
    SysExManager(const SysExManager&) = delete;
    SysExManager& operator=(const SysExManager&) = delete;
    
    enum class UpdateMode
    {
        MANUAL,
        NOTE_OFF, // Not implemeneted, operates same as MANUAL
        AUTO
    };
    
    void setUpdateMode(UpdateMode mode);
    
    void flush();
    void flushAll();
    
    void openMidiIn(juce::String name);
    void openMidiOut(juce::String name);
    
    void updateFromProperty(IProperty* prop);
    
private:
    UpdateMode mUpdateMode;
    bool mFlush = false;
    bool mFlushAll = false;
    juce::CriticalSection mUpdateModeLock;
    
    SysExMemory mUserMem;
    SysExMemory mDeviceMem;
    
    juce::CriticalSection mUserMemLock;
    bool mUserMemDirty = false;
    
    class SysExThread : public juce::Thread
    {
    public:
        SysExThread(SysExManager* parent);
        
    protected:
        SysExManager* mParent;
        void run();
    };
    
    std::unique_ptr<SysExThread> mThread;
    
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    
    std::unique_ptr<juce::MidiInput> mMidiIn;
    std::unique_ptr<juce::MidiOutput> mMidiOut;
    
    juce::CriticalSection mMidiOutLock;
    
};