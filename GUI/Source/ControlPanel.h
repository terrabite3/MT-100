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

class Callback;
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
    void sendMidi(const juce::MidiMessage& message) const;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    friend Callback;
    
    std::unique_ptr<Callback> mCallback;
    std::unique_ptr<juce::MidiInput> mMidiIn;
    std::unique_ptr<juce::MidiOutput> mMidiOut;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> midiIn_combo;
    std::unique_ptr<juce::ComboBox> midiOut_combo;
    std::unique_ptr<juce::TextButton> load_button;
    std::unique_ptr<juce::TextButton> save_button;
    std::unique_ptr<juce::TextButton> sendSysEx_button;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> juce__label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};

//[EndFile] You can add extra defines here...

class Callback : public juce::MidiInputCallback
{
public:
    Callback(ControlPanel* parent)
    : mParent(parent)
    {}
    
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    
private:
    ControlPanel* mParent;
};

//[/EndFile]

