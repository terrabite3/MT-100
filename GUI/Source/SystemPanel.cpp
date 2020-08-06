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

#include "SystemPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SystemPanel::SystemPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__groupComponent.reset (new juce::GroupComponent ("new group",
                                                          TRANS("Reverb")));
    addAndMakeVisible (juce__groupComponent.get());

    juce__groupComponent->setBounds (8, 72, 280, 136);

    masterTune_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (masterTune_slider.get());
    masterTune_slider->setRange (432.1, 457.6, 0.2);
    masterTune_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    masterTune_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    masterTune_slider->addListener (this);

    masterTune_slider->setBounds (129, 8, 150, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Master Tune")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (8, 8, 120, 24);

    reverbMode_comboBox.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (reverbMode_comboBox.get());
    reverbMode_comboBox->setEditableText (false);
    reverbMode_comboBox->setJustificationType (juce::Justification::centredLeft);
    reverbMode_comboBox->setTextWhenNothingSelected (juce::String());
    reverbMode_comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    reverbMode_comboBox->addItem (TRANS("Room"), 1);
    reverbMode_comboBox->addItem (TRANS("Hall"), 2);
    reverbMode_comboBox->addItem (TRANS("Plate"), 3);
    reverbMode_comboBox->addItem (TRANS("Tap delay"), 4);
    reverbMode_comboBox->addListener (this);

    reverbMode_comboBox->setBounds (112, 104, 150, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Mode")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (32, 104, 72, 24);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Time")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (32, 136, 70, 24);

    reverbTime_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (reverbTime_slider.get());
    reverbTime_slider->setRange (1, 8, 1);
    reverbTime_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    reverbTime_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    reverbTime_slider->addListener (this);

    reverbTime_slider->setBounds (112, 136, 150, 24);

    reverbLevel_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (reverbLevel_slider.get());
    reverbLevel_slider->setRange (0, 7, 1);
    reverbLevel_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    reverbLevel_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    reverbLevel_slider->addListener (this);

    reverbLevel_slider->setBounds (112, 168, 150, 24);

    juce__label4.reset (new juce::Label ("new label",
                                         TRANS("Level")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label4->setBounds (32, 168, 70, 24);

    masterVolume_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (masterVolume_slider.get());
    masterVolume_slider->setRange (0, 100, 1);
    masterVolume_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    masterVolume_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    masterVolume_slider->addListener (this);

    masterVolume_slider->setBounds (129, 40, 150, 24);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Master Volume")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (8, 40, 120, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (296, 216);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SystemPanel::~SystemPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__groupComponent = nullptr;
    masterTune_slider = nullptr;
    juce__label = nullptr;
    reverbMode_comboBox = nullptr;
    juce__label2 = nullptr;
    juce__label3 = nullptr;
    reverbTime_slider = nullptr;
    reverbLevel_slider = nullptr;
    juce__label4 = nullptr;
    masterVolume_slider = nullptr;
    juce__label5 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SystemPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SystemPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SystemPanel::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == masterTune_slider.get())
    {
        //[UserSliderCode_masterTune_slider] -- add your slider handling code here..
        mMasterTune->setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_masterTune_slider]
    }
    else if (sliderThatWasMoved == reverbTime_slider.get())
    {
        //[UserSliderCode_reverbTime_slider] -- add your slider handling code here..
        mReverbTime->setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_reverbTime_slider]
    }
    else if (sliderThatWasMoved == reverbLevel_slider.get())
    {
        //[UserSliderCode_reverbLevel_slider] -- add your slider handling code here..
        mReverbLevel->setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_reverbLevel_slider]
    }
    else if (sliderThatWasMoved == masterVolume_slider.get())
    {
        //[UserSliderCode_masterVolume_slider] -- add your slider handling code here..
        mMasterVolume->setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_masterVolume_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SystemPanel::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == reverbMode_comboBox.get())
    {
        //[UserComboBoxCode_reverbMode_comboBox] -- add your combo box handling code here..
        mReverbMode->setValue(comboBoxThatHasChanged->getText().toStdString());
        //[/UserComboBoxCode_reverbMode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void SystemPanel::refresh()
{
    if (mMasterTune && mMasterTune->isSet())
    {
        masterTune_slider->setValue(mMasterTune->value(), juce::NotificationType::dontSendNotification);
    }
    
    if (mReverbMode && mReverbMode->isSet())
    {
        reverbMode_comboBox->setText(mReverbMode->value(), juce::NotificationType::dontSendNotification);
    }
    
    if (mReverbTime && mReverbTime->isSet())
    {
        reverbTime_slider->setValue(mReverbTime->value(), juce::NotificationType::dontSendNotification);
    }
    
    if (mReverbLevel && mReverbLevel->isSet())
    {
        reverbLevel_slider->setValue(mReverbLevel->value(), juce::NotificationType::dontSendNotification);
    }


    if (mMasterVolume && mMasterVolume->isSet())
    {
        masterVolume_slider->setValue(mMasterVolume->value(), juce::NotificationType::dontSendNotification);
    }
}

void SystemPanel::bindProperty(SystemProperty* prop)
{
    mMasterTune = &prop->masterTune;
    masterTune_slider->setRange({mMasterTune->getMin(), mMasterTune->getMax()}, mMasterTune->getStep());
    masterTune_slider->setNumDecimalPlacesToDisplay(1);
    
    mReverbMode = &prop->reverbMode;
    reverbMode_comboBox->clear();
    for (auto choice : mReverbMode->getChoices())
    {
        reverbMode_comboBox->addItem(choice, reverbMode_comboBox->getNumItems() + 1);
    }
    
    mReverbTime = &prop->reverbTime;
    reverbTime_slider->setRange(mReverbTime->getMin(), mReverbTime->getMax(), 1);
    
    mReverbLevel = &prop->reverbLevel;
    reverbLevel_slider->setRange(mReverbLevel->getMin(), mReverbLevel->getMax(), 1);
    
    mMasterVolume = &prop->masterVolume;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SystemPanel" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="296" initialHeight="216">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="new group" id="8c61cd31a96458fe" memberName="juce__groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 72 280 136" title="Reverb"/>
  <SLIDER name="new slider" id="536593ca9edbe74e" memberName="masterTune_slider"
          virtualName="" explicitFocusOrder="0" pos="129 8 150 24" min="432.1"
          max="457.6" int="0.2" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="b49a9c11373decc8" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="8 8 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master Tune" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="fbc69bb10c1e060e" memberName="reverbMode_comboBox"
            virtualName="" explicitFocusOrder="0" pos="112 104 150 24" editable="0"
            layout="33" items="Room&#10;Hall&#10;Plate&#10;Tap delay" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="75f662e1f1b8cdab" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="32 104 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5003a96c77b2cbb7" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="32 136 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="7a5a00097533061a" memberName="reverbTime_slider"
          virtualName="" explicitFocusOrder="0" pos="112 136 150 24" min="1.0"
          max="8.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="c8f7c9ced28f8ad0" memberName="reverbLevel_slider"
          virtualName="" explicitFocusOrder="0" pos="112 168 150 24" min="0.0"
          max="7.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="893d27a9a430f55d" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="32 168 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="a50251e38f0886b" memberName="masterVolume_slider"
          virtualName="" explicitFocusOrder="0" pos="129 40 150 24" min="0.0"
          max="100.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="8df0bca0698f1f39" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="8 40 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master Volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

