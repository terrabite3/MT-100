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

#include "SysExManager.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ControlPanel  : public juce::Component,
                      public juce::ComboBox::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    ControlPanel ();
    ~ControlPanel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateFromProperty(IProperty* prop);
    std::string getSyncMode() const;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<SysExManager> mSysExManager;
    
    void configureSlidersToNotifyOnRelease(Component* comp, bool notifyOnRelease) const;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> midiIn_combo;
    std::unique_ptr<juce::ComboBox> midiOut_combo;
    std::unique_ptr<juce::TextButton> load_button;
    std::unique_ptr<juce::TextButton> save_button;
    std::unique_ptr<juce::TextButton> sendSysEx_button;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::ComboBox> syncMode_combo;
    std::unique_ptr<juce::Label> juce__label3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

