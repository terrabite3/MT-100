#include "MainComponent.h"

#include "Memory/IMemory.h"

//==============================================================================
MainComponent::MainComponent()
: mSystemProp(SevenAddr(0x10, 0, 0).toNative())
{
    addAndMakeVisible(mSystemPanel);
    
    mSystemPanel.bindProperty(&mSystemProp);
    
    setSize (600, 400);
    
    addAndMakeVisible(mTvf);
    
    mTvf.setBounds(300, 0, 400, 400);
    

    
    auto devInfo = juce::MidiOutput::getDefaultDevice();
    mMidiOut = juce::MidiOutput::openDevice(devInfo.identifier);
    
    if (!mMidiOut)
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "MIDI", "Could not open MIDI device");
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}


void MainComponent::loadJson()
{
    juce::FileChooser chooser ("Select a JSON file to load...",
                               juce::File::getSpecialLocation(juce::File::currentApplicationFile),
                               "*.json");
    if (chooser.browseForFileToOpen())
    {
        juce::File jsonFile = chooser.getResult();
        
        auto jsonText = jsonFile.loadFileAsString();
        
        auto json = nlohmann::json::parse(jsonText.toStdString());
        
        mSystemProp.readJson(json);
        
        mSystemPanel.refresh();
    }
}

void MainComponent::saveJson()
{
    juce::FileChooser chooser ("Select a JSON file to save...",
                               juce::File::getSpecialLocation(juce::File::currentApplicationFile),
                               "*.json");
    if (chooser.browseForFileToSave(true))
    {
        juce::File jsonFile = chooser.getResult();
        
        nlohmann::json json;
        mSystemProp.writeJson(json);
        
        auto jsonText = json.dump(4);
        
        jsonFile.replaceWithText(jsonText);
    }
}

void MainComponent::sendSysEx()
{
    if (mMidiOut)
    {
        SysExMemory mem;
        mSystemProp.writeMemory(mem);
        
        auto sysEx = mem.writeSyx();
        
        if (sysEx.empty()) return;
        
        // Strip off the start and end bytes because createSysExMessage() adds them too
        sysEx.erase(sysEx.begin());
        sysEx.erase(sysEx.end() - 1);
        
        auto message = juce::MidiMessage::createSysExMessage((void*)sysEx.data(), (int)sysEx.size());
        
        mMidiOut->sendMessageNow(message);
    }
}

void MainComponent::sendNote()
{
    if (mMidiOut)
    {
        mMidiOut->sendMessageNow(juce::MidiMessage::noteOn(2, 60, (uint8_t)127));
    }
}




