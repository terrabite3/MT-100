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

#include "Component/Keyfollow.h"

#include "Property/PartialProperty.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PartialPanel  : public juce::Component,
                      public juce::Button::Listener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PartialPanel ();
    ~PartialPanel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void refreshFromProperty();
    void bindProperty(PartialProperty* prop);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* keyfollow_png;
    static const int keyfollow_pngSize;
    static const char* filterEnv_png;
    static const int filterEnv_pngSize;
    static const char* bias_png;
    static const int bias_pngSize;
    static const char* pitchEnv_png;
    static const int pitchEnv_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> juce__groupComponent2;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent5;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent4;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent;
    std::unique_ptr<juce::ToggleButton> juce__toggleButton;
    std::unique_ptr<juce::Slider> juce__slider;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::Slider> juce__slider2;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Slider> juce__slider3;
    std::unique_ptr<juce::Label> juce__label3;
    std::unique_ptr<juce::Slider> juce__slider4;
    std::unique_ptr<juce::Label> juce__label4;
    std::unique_ptr<juce::Label> juce__label5;
    std::unique_ptr<juce::ToggleButton> juce__toggleButton2;
    std::unique_ptr<juce::Slider> juce__slider6;
    std::unique_ptr<juce::Label> juce__label6;
    std::unique_ptr<juce::Slider> juce__slider7;
    std::unique_ptr<juce::Label> juce__label7;
    std::unique_ptr<juce::Slider> juce__slider8;
    std::unique_ptr<juce::Label> juce__label8;
    std::unique_ptr<juce::ImageButton> juce__imageButton2;
    std::unique_ptr<juce::Slider> juce__slider9;
    std::unique_ptr<juce::Label> juce__label9;
    std::unique_ptr<juce::Slider> juce__slider10;
    std::unique_ptr<juce::Label> juce__label10;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent3;
    std::unique_ptr<juce::Slider> juce__slider11;
    std::unique_ptr<juce::Label> juce__label11;
    std::unique_ptr<juce::Slider> juce__slider12;
    std::unique_ptr<juce::Label> juce__label12;
    std::unique_ptr<juce::ImageButton> juce__imageButton3;
    std::unique_ptr<juce::ImageButton> juce__imageButton4;
    std::unique_ptr<juce::Label> juce__label13;
    std::unique_ptr<juce::ImageButton> juce__imageButton5;
    std::unique_ptr<juce::ImageButton> juce__imageButton6;
    std::unique_ptr<juce::Slider> juce__slider13;
    std::unique_ptr<juce::Label> juce__label14;
    std::unique_ptr<juce::Slider> juce__slider14;
    std::unique_ptr<juce::Label> juce__label15;
    std::unique_ptr<juce::ImageButton> juce__imageButton7;
    std::unique_ptr<juce::ImageButton> juce__imageButton8;
    std::unique_ptr<juce::Label> juce__label16;
    std::unique_ptr<juce::Label> juce__label17;
    std::unique_ptr<juce::Slider> juce__slider15;
    std::unique_ptr<juce::Label> juce__label18;
    std::unique_ptr<juce::Slider> juce__slider16;
    std::unique_ptr<juce::Label> juce__label19;
    std::unique_ptr<juce::Slider> juce__slider17;
    std::unique_ptr<juce::Label> juce__label20;
    std::unique_ptr<juce::ImageButton> juce__imageButton9;
    std::unique_ptr<juce::Label> juce__label21;
    std::unique_ptr<juce::ImageButton> juce__imageButton10;
    std::unique_ptr<juce::Label> juce__label22;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent6;
    std::unique_ptr<Keyfollow> pitch_keyfollow;
    std::unique_ptr<juce::Label> juce__label23;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PartialPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

