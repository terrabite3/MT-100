#include "MainComponent.h"

#include "Memory/IMemory.h"

//==============================================================================
MainComponent::MainComponent()
: mMasterVolume(std::make_shared<IntProperty>("master_volume", SevenAddr(0x10, 0, 0x16).toNative(), 100))
{
    addAndMakeVisible(mSystemPanel);
    
    mSystemPanel.bindProperty(mMasterVolume);
    
    setSize (600, 400);
    
    addAndMakeVisible(mTvf);
    
    mTvf.setBounds(300, 0, 400, 400);
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
        
        if (json.count("system"))
        {
            auto jSystem = json["system"];
            mMasterVolume->readJson(jSystem);
            
            mSystemPanel.refresh();
        }
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
        json["system"] = nlohmann::json::object();
        
        auto& jSystem = json["system"];
        mMasterVolume->writeJson(jSystem);
        
        auto jsonText = json.dump(4);
        
        jsonFile.replaceWithText(jsonText);
    }
}