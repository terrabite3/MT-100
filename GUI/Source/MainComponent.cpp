#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(mSystemPanel);
    setSize (600, 400);
    
    
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
        
        mJson = nlohmann::json::parse(jsonText.toStdString());
        
        refresh();
    }
}

void MainComponent::refresh()
{
    if (mJson.count("system"))
    {
        mSystemPanel.refresh(mJson["system"]);
    }
}