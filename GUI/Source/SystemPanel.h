/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "json.hpp"
#include "Property/IntProperty.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SystemPanel  : public juce::Component,
                     public juce::Slider::Listener,
                     public juce::ComboBox::Listener,
                     public juce::Button::Listener
{
public:
    //==============================================================================
    SystemPanel ();
    ~SystemPanel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void refresh();
    void bindProperty(std::shared_ptr<IntProperty> prop);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::shared_ptr<IntProperty> mMasterVolume;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> juce__groupComponent;
    std::unique_ptr<juce::Slider> masterTune_slider;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::ComboBox> reverbMode_comboBox;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> juce__label3;
    std::unique_ptr<juce::Slider> reverbTime_slider;
    std::unique_ptr<juce::Slider> reverbLevel_slider;
    std::unique_ptr<juce::Label> juce__label4;
    std::unique_ptr<juce::Slider> masterVolume_slider;
    std::unique_ptr<juce::Label> juce__label5;
    std::unique_ptr<juce::TextButton> loadJson_button;
    std::unique_ptr<juce::TextButton> saveJson_button;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SystemPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

