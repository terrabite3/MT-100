#include "MainComponent.h"

#include "Memory/IMemory.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(mSystemPanel);
    addAndMakeVisible(mControlPanel);
    addAndMakeVisible(mPartial);
    
    mControlPanel.setTopLeftPosition(0, 0);
    mSystemPanel.setTopLeftPosition(0, 176);
    mPartial.setTopLeftPosition(350, 0);
    
    mProp.registerListener(this);
    
    mSystemPanel.bindProperty(&mProp.system);
    mPartial.bindProperty(&mProp.timbreTemp.children[0].get()->partial1);
    
    setSize (1250, 900);
    
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
        
        mProp.readJson(json);
        
        mSystemPanel.refresh();
        mPartial.refreshFromProperty();
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
        mProp.writeJson(json);
        
        auto jsonText = json.dump(4);
        
        jsonFile.replaceWithText(jsonText);
    }
}


void MainComponent::updateValue(juce::String address, int value)
{
    auto addr = address.getHexValue32();
    
    IntProperty temp("name", addr);
    temp.setValue(value);
    
    mControlPanel.updateFromProperty(&temp);
}

void MainComponent::notify(std::string name)
{
    mControlPanel.updateFromProperty(&mProp);
}


