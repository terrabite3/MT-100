#include "MainComponent.h"

#include "Memory/IMemory.h"

//==============================================================================
MainComponent::MainComponent()
: mSystemProp(SevenAddr(0x10, 0, 0).toNative())
, mWaveformProp("waveform", SevenAddr(8, 1 + 1, 0x2 + 4).toNative(), {"SQU", "SAW"})
{
    addAndMakeVisible(mSystemPanel);
    addAndMakeVisible(mControlPanel);
    addAndMakeVisible(mTvf);
    
    mControlPanel.setTopLeftPosition(0, 0);
    mSystemPanel.setTopLeftPosition(0, 176);
    mTvf.setTopLeftPosition(350, 0);
    
    mSystemProp.registerListener(this);
    mWaveformProp.registerListener(this);
    
    mSystemPanel.bindProperty(&mSystemProp);
    mSystemPanel.bindWaveformProp(&mWaveformProp);
    
    setSize (620, 436);
    
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
    SysExMemory mem;
    mSystemProp.writeMemory(mem);
    mWaveformProp.writeMemory(mem);
    
    auto sysEx = mem.writeSyx();
    
    if (sysEx.empty()) return;
    
    // Strip off the start and end bytes because createSysExMessage() adds them too
    sysEx.erase(sysEx.begin());
    sysEx.erase(sysEx.end() - 1);
    
    auto message = juce::MidiMessage::createSysExMessage((void*)sysEx.data(), (int)sysEx.size());
    
    mControlPanel.sendMidi(message);
}

void MainComponent::sendNote()
{
    auto message = juce::MidiMessage::noteOn(2, 60, (uint8_t)127);
    mControlPanel.sendMidi(message);
}



void MainComponent::fuzz()
{
    juce::Random rand;
    
    std::vector<uint8_t> message
    {
        0x41, 0x10, 0x16, 0x12
    };
    
    uint8_t sum = 0;
    
    static int address = 0;
    
    // address
    uint8_t a2 = (address >> 14) & 0x7f;
    uint8_t a1 = (address >> 7)  & 0x7f;
    uint8_t a0 =  address        & 0x7f;
    
    sum += a2 + a1 + a0;
    message.emplace_back(a2);
    message.emplace_back(a1);
    message.emplace_back(a0);
    
    address += 256;
    
    // data
    for (int i = 0; i < 256; ++i)
    {
        uint8_t d = rand.nextInt(0x7f);
        sum += d;
        message.emplace_back(d);
    }
    
    // sum
    message.emplace_back(0x80 - (sum & 0x7f));
    
    mControlPanel.sendMidi(juce::MidiMessage::createSysExMessage((void*)message.data(), (int)message.size()));
}

void MainComponent::updateValue(juce::String address, int value)
{
    auto addr = address.getHexValue32();
    
    std::vector<uint8_t> message
    {
        0x41, 0x10, 0x16, 0x12
    };
    
    uint8_t sum = 0;
    
    // address
    uint8_t a2 = (addr >> 16) & 0x7f;
    uint8_t a1 = (addr >> 8)  & 0x7f;
    uint8_t a0 =  addr        & 0x7f;
    
    sum += a2 + a1 + a0;
    message.emplace_back(a2);
    message.emplace_back(a1);
    message.emplace_back(a0);
    
    // data
    uint8_t d = value;
    sum += d;
    message.emplace_back(d);
    
    // sum
    message.emplace_back(0x80 - (sum & 0x7f));
    
    mControlPanel.sendMidi(juce::MidiMessage::createSysExMessage((void*)message.data(), (int)message.size()));
    
    
}

void MainComponent::notify(std::string name)
{
    if (mControlPanel.getSyncMode() != "Manual")
    {
        sendSysEx();
    }
}


