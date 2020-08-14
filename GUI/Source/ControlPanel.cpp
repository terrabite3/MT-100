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

    midiIn_combo->setBounds (120, 88, 206, 24);

    midiOut_combo.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (midiOut_combo.get());
    midiOut_combo->setEditableText (false);
    midiOut_combo->setJustificationType (juce::Justification::centredLeft);
    midiOut_combo->setTextWhenNothingSelected (juce::String());
    midiOut_combo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiOut_combo->addListener (this);

    midiOut_combo->setBounds (120, 120, 206, 24);

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

    juce__label2->setBounds (8, 120, 96, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("MIDI In")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (8, 88, 96, 24);

    syncMode_combo.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (syncMode_combo.get());
    syncMode_combo->setEditableText (false);
    syncMode_combo->setJustificationType (juce::Justification::centredLeft);
    syncMode_combo->setTextWhenNothingSelected (juce::String());
    syncMode_combo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    syncMode_combo->addItem (TRANS("Manual"), 1);
    syncMode_combo->addItem (TRANS("Note Release"), 2);
    syncMode_combo->addItem (TRANS("Immediate"), 3);
    syncMode_combo->addItem (TRANS("Continuous"), 4);
    syncMode_combo->addListener (this);

    syncMode_combo->setBounds (120, 48, 206, 24);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Sync Mode")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (8, 48, 96, 24);

    fuzz_button.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (fuzz_button.get());
    fuzz_button->setButtonText (TRANS("Fuzz"));
    fuzz_button->addListener (this);

    fuzz_button->setBounds (40, 72, 64, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (336, 160);


    //[Constructor] You can add your own custom stuff here..

    syncMode_combo->setText(syncMode_combo->getItemText(0));


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
    syncMode_combo = nullptr;
    juce__label3 = nullptr;
    fuzz_button = nullptr;


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

        numPressedNotes = 0;
        mPendingMessage = {};

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

        numPressedNotes = 0;
        mPendingMessage = {};

        //[/UserComboBoxCode_midiOut_combo]
    }
    else if (comboBoxThatHasChanged == syncMode_combo.get())
    {
        //[UserComboBoxCode_syncMode_combo] -- add your combo box handling code here..
        auto main = findParentComponentOfClass<MainComponent>();
        auto mode = comboBoxThatHasChanged->getText();
        if (mode == "Manual")
        {
            configureSlidersToNotifyOnRelease(main, true);
        }
        else if (mode == "Note Release")
        {
            configureSlidersToNotifyOnRelease(main, false);
        }
        else if (mode == "Immediate")
        {
            configureSlidersToNotifyOnRelease(main, true);
        }
        else if (mode == "Continuous")
        {
            configureSlidersToNotifyOnRelease(main, false);
        }
        //[/UserComboBoxCode_syncMode_combo]
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
    else if (buttonThatWasClicked == fuzz_button.get())
    {
        //[UserButtonCode_fuzz_button] -- add your button handler code here..
        main->fuzz();
        //[/UserButtonCode_fuzz_button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void ControlPanel::sendMidi(const juce::MidiMessage& message)
{
    if (mMidiOut)
    {
        if (getSyncMode() == "Note Release" && numPressedNotes > 0)
        {
            mPendingMessage = new juce::MidiMessage(message);
        }
        else
            mMidiOut->sendMessageNow(message);
    }
}

std::string ControlPanel::getSyncMode() const
{
    return syncMode_combo->getText().toStdString();
}

void ControlPanel::configureSlidersToNotifyOnRelease(Component* comp, bool notifyOnRelease) const
{
    auto compAsSlider = dynamic_cast<juce::Slider*>(comp);
    if (compAsSlider)
    {
        compAsSlider->setChangeNotificationOnlyOnRelease(notifyOnRelease);
    }

    for (auto child : comp->getChildren())
    {
        configureSlidersToNotifyOnRelease(child, notifyOnRelease);
    }
}

void Callback::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    if (mParent->mMidiOut)
        mParent->mMidiOut->sendMessageNow(message);

    if (message.isNoteOn())
    {
        auto& count = mParent->numPressedNotes;
        count++;
    }
    if (message.isNoteOff())
    {
        auto& count = mParent->numPressedNotes;
        count--;
        if (mParent->numPressedNotes == 0 && mParent->mPendingMessage != nullptr)
        {
            mParent->sendMidi(*mParent->mPendingMessage);
            mParent->mPendingMessage = nullptr;
        }
    }
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
                 fixedSize="0" initialWidth="336" initialHeight="160">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="new combo box" id="f3df4114d4adac0" memberName="midiIn_combo"
            virtualName="" explicitFocusOrder="0" pos="120 88 206 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="f55ca67533510438" memberName="midiOut_combo"
            virtualName="" explicitFocusOrder="0" pos="120 120 206 24" editable="0"
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
         virtualName="" explicitFocusOrder="0" pos="8 120 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI Out" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="55cd72467155de36" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="8 88 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI In" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="481a2ddc073e522a" memberName="syncMode_combo"
            virtualName="" explicitFocusOrder="0" pos="120 48 206 24" editable="0"
            layout="33" items="Manual&#10;Note Release&#10;Immediate&#10;Continuous"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6c876079d0de6ab2" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="8 48 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sync Mode" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="2879a1b4ce82cfa3" memberName="fuzz_button"
              virtualName="" explicitFocusOrder="0" pos="40 72 64 24" buttonText="Fuzz"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

