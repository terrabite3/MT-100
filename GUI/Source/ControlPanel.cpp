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

//[Headers] You can add your own extra header files here...
#include "MainComponent.h"
//[/Headers]

#include "ControlPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ControlPanel::ControlPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    midiIn_combo.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (midiIn_combo.get());
    midiIn_combo->setEditableText (false);
    midiIn_combo->setJustificationType (juce::Justification::centredLeft);
    midiIn_combo->setTextWhenNothingSelected (juce::String());
    midiIn_combo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiIn_combo->addListener (this);

    midiIn_combo->setBounds (120, 40, 206, 24);

    midiOut_combo.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (midiOut_combo.get());
    midiOut_combo->setEditableText (false);
    midiOut_combo->setJustificationType (juce::Justification::centredLeft);
    midiOut_combo->setTextWhenNothingSelected (juce::String());
    midiOut_combo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiOut_combo->addListener (this);

    midiOut_combo->setBounds (120, 72, 206, 24);

    load_button.reset (new juce::TextButton ("load_button"));
    addAndMakeVisible (load_button.get());
    load_button->setButtonText (TRANS("Load File..."));
    load_button->addListener (this);

    load_button->setBounds (8, 8, 96, 24);

    save_button.reset (new juce::TextButton ("save_button"));
    addAndMakeVisible (save_button.get());
    save_button->setButtonText (TRANS("Save File..."));
    save_button->addListener (this);

    save_button->setBounds (120, 8, 96, 24);

    sendSysEx_button.reset (new juce::TextButton ("load_button"));
    addAndMakeVisible (sendSysEx_button.get());
    sendSysEx_button->setButtonText (TRANS("Send SysEx"));
    sendSysEx_button->addListener (this);

    sendSysEx_button->setBounds (232, 8, 96, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("MIDI Out")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (8, 72, 96, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("MIDI In")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (8, 40, 96, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (336, 104);


    //[Constructor] You can add your own custom stuff here..
    
    mCallback = std::make_unique<Callback>(this);
    
    juce::StringArray midiInputNames;
    midiInputNames.add("Disabled");
    for (auto input : juce::MidiInput::getAvailableDevices())
    {
        midiInputNames.add(input.name);
    }
    midiIn_combo->addItemList(midiInputNames, 1);
    
    juce::StringArray midiOutputNames;
    midiOutputNames.add("Disabled");
    for (auto output : juce::MidiOutput::getAvailableDevices())
    {
        midiOutputNames.add(output.name);
    }
    midiOut_combo->addItemList(midiOutputNames, 1);
         
    //[/Constructor]
}

ControlPanel::~ControlPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    midiIn_combo = nullptr;
    midiOut_combo = nullptr;
    load_button = nullptr;
    save_button = nullptr;
    sendSysEx_button = nullptr;
    juce__label2 = nullptr;
    juce__label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControlPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControlPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ControlPanel::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
//    auto main = findParentComponentOfClass<MainComponent>();
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiIn_combo.get())
    {
        //[UserComboBoxCode_midiIn_combo] -- add your combo box handling code here..
        auto selectedName = comboBoxThatHasChanged->getText();
        if (selectedName == "Disabled")
        {
            mMidiIn = nullptr;
        }
        else if (mMidiIn && mMidiIn->getName() == selectedName)
        {
            // Do nothing
        }
        else
        {
            for (auto input : juce::MidiInput::getAvailableDevices())
            {
                if (selectedName == input.name)
                {
                    mMidiIn = juce::MidiInput::openDevice(input.identifier, mCallback.get());
                    if (mMidiIn)
                        mMidiIn->start();
                    break;
                }
            }
        }
        
        //[/UserComboBoxCode_midiIn_combo]
    }
    else if (comboBoxThatHasChanged == midiOut_combo.get())
    {
        //[UserComboBoxCode_midiOut_combo] -- add your combo box handling code here..
        auto selectedName = comboBoxThatHasChanged->getText();
        if (selectedName == "Disabled")
        {
            mMidiOut = nullptr;
        }
        else if (mMidiOut && mMidiOut->getName() == selectedName)
        {
            // Do nothing
        }
        else
        {
            for (auto output : juce::MidiOutput::getAvailableDevices())
            {
                if (selectedName == output.name)
                {
                    mMidiOut = juce::MidiOutput::openDevice(output.identifier);
                    break;
                }
            }
        }
        //[/UserComboBoxCode_midiOut_combo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ControlPanel::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    auto main = findParentComponentOfClass<MainComponent>();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == load_button.get())
    {
        //[UserButtonCode_load_button] -- add your button handler code here..
        main->loadJson();
        //[/UserButtonCode_load_button]
    }
    else if (buttonThatWasClicked == save_button.get())
    {
        //[UserButtonCode_save_button] -- add your button handler code here..
        main->saveJson();
        //[/UserButtonCode_save_button]
    }
    else if (buttonThatWasClicked == sendSysEx_button.get())
    {
        //[UserButtonCode_sendSysEx_button] -- add your button handler code here..
        main->sendSysEx();
        //[/UserButtonCode_sendSysEx_button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void ControlPanel::sendMidi(const juce::MidiMessage& message) const
{
    if (mMidiOut)
    {
        mMidiOut->sendMessageNow(message);
    }
}

void Callback::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    if (mParent->mMidiOut)
        mParent->mMidiOut->sendMessageNow(message);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ControlPanel" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="336" initialHeight="104">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="new combo box" id="f3df4114d4adac0" memberName="midiIn_combo"
            virtualName="" explicitFocusOrder="0" pos="120 40 206 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="f55ca67533510438" memberName="midiOut_combo"
            virtualName="" explicitFocusOrder="0" pos="120 72 206 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="load_button" id="72ddefec56efcea6" memberName="load_button"
              virtualName="" explicitFocusOrder="0" pos="8 8 96 24" buttonText="Load File..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="save_button" id="a01f461b7218c5fd" memberName="save_button"
              virtualName="" explicitFocusOrder="0" pos="120 8 96 24" buttonText="Save File..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="load_button" id="cda7a9124fceccc6" memberName="sendSysEx_button"
              virtualName="" explicitFocusOrder="0" pos="232 8 96 24" buttonText="Send SysEx"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="e573f6dc0385be1" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="8 72 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI Out" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="55cd72467155de36" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="8 40 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI In" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

