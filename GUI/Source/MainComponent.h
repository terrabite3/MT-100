#pragma once

#include "SystemPanel.h"
#include "ControlPanel.h"

#include "TvfPanel.h"
#include "PartialPanel.h"
#include "Property/SystemProperty.h"

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public IPropertyListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    void loadJson();
    void saveJson();
    
    void sendSysEx();
    void sendNote();
    void fuzz();
    void updateValue(juce::String address, int value);

private:
    //==============================================================================
    // Your private member variables go here...
    
    ControlPanel mControlPanel;
    SystemPanel mSystemPanel;
//    TvfPanel mTvf;
    PartialPanel mPartial;

    SystemProperty mSystemProp;
    ChoiceProperty mWaveformProp;
    
    void notify(std::string name) override;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
