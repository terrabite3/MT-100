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

#include "adsr_editor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TvfPanel  : public juce::Component,
                  public juce::Slider::Listener
{
public:
    //==============================================================================
    TvfPanel ();
    ~TvfPanel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ADSREditor> adsr;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Slider> time1_slider;
    std::unique_ptr<juce::Slider> time2_slider;
    std::unique_ptr<juce::Label> juce__label3;
    std::unique_ptr<juce::Label> juce__label4;
    std::unique_ptr<juce::Slider> time3_slider;
    std::unique_ptr<juce::Slider> time4_slider;
    std::unique_ptr<juce::Label> juce__label5;
    std::unique_ptr<juce::Label> juce__label6;
    std::unique_ptr<juce::Slider> time5_slider;
    std::unique_ptr<juce::Slider> level1_slider;
    std::unique_ptr<juce::Label> juce__label7;
    std::unique_ptr<juce::Slider> level2_slider;
    std::unique_ptr<juce::Label> juce__label8;
    std::unique_ptr<juce::Slider> level3_slider;
    std::unique_ptr<juce::Label> juce__label9;
    std::unique_ptr<juce::Slider> level_sustain_slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TvfPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

