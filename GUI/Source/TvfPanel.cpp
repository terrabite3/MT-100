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
//[/Headers]

#include "TvfPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TvfPanel::TvfPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    adsr.reset (new AdsrEditor());
    addAndMakeVisible (adsr.get());
    adsr->setName ("new component");

    adsr->setBounds (40, 40, 248, 120);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Time 1")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (48, 176, 104, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Time 2")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (48, 200, 104, 24);

    time1_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (time1_slider.get());
    time1_slider->setRange (0, 1, 0);
    time1_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    time1_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    time1_slider->addListener (this);

    time1_slider->setBounds (144, 176, 150, 24);

    time2_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (time2_slider.get());
    time2_slider->setRange (0, 1, 0);
    time2_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    time2_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    time2_slider->addListener (this);

    time2_slider->setBounds (144, 200, 150, 24);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Time 3")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (48, 224, 104, 24);

    juce__label4.reset (new juce::Label ("new label",
                                         TRANS("Time 4")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label4->setBounds (48, 248, 104, 24);

    time3_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (time3_slider.get());
    time3_slider->setRange (0, 1, 0);
    time3_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    time3_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    time3_slider->addListener (this);

    time3_slider->setBounds (144, 224, 150, 24);

    time4_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (time4_slider.get());
    time4_slider->setRange (0, 1, 0);
    time4_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    time4_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    time4_slider->addListener (this);

    time4_slider->setBounds (144, 248, 150, 24);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Time 5")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (48, 272, 104, 24);

    juce__label6.reset (new juce::Label ("new label",
                                         TRANS("Level 1")));
    addAndMakeVisible (juce__label6.get());
    juce__label6->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label6->setJustificationType (juce::Justification::centredLeft);
    juce__label6->setEditable (false, false, false);
    juce__label6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label6->setBounds (48, 304, 104, 24);

    time5_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (time5_slider.get());
    time5_slider->setRange (0, 1, 0);
    time5_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    time5_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    time5_slider->addListener (this);

    time5_slider->setBounds (144, 272, 150, 24);

    level1_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (level1_slider.get());
    level1_slider->setRange (0, 1, 0);
    level1_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    level1_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    level1_slider->addListener (this);

    level1_slider->setBounds (144, 304, 150, 24);

    juce__label7.reset (new juce::Label ("new label",
                                         TRANS("Level 2")));
    addAndMakeVisible (juce__label7.get());
    juce__label7->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label7->setJustificationType (juce::Justification::centredLeft);
    juce__label7->setEditable (false, false, false);
    juce__label7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label7->setBounds (48, 328, 104, 24);

    level2_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (level2_slider.get());
    level2_slider->setRange (0, 1, 0);
    level2_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    level2_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    level2_slider->addListener (this);

    level2_slider->setBounds (144, 328, 150, 24);

    juce__label8.reset (new juce::Label ("new label",
                                         TRANS("Level 3")));
    addAndMakeVisible (juce__label8.get());
    juce__label8->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label8->setJustificationType (juce::Justification::centredLeft);
    juce__label8->setEditable (false, false, false);
    juce__label8->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label8->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label8->setBounds (48, 352, 104, 24);

    level3_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (level3_slider.get());
    level3_slider->setRange (0, 1, 0);
    level3_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    level3_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    level3_slider->addListener (this);

    level3_slider->setBounds (144, 352, 150, 24);

    juce__label9.reset (new juce::Label ("new label",
                                         TRANS("Level Sustain")));
    addAndMakeVisible (juce__label9.get());
    juce__label9->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label9->setJustificationType (juce::Justification::centredLeft);
    juce__label9->setEditable (false, false, false);
    juce__label9->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label9->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label9->setBounds (48, 376, 104, 24);

    level_sustain_slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (level_sustain_slider.get());
    level_sustain_slider->setRange (0, 1, 0);
    level_sustain_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    level_sustain_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    level_sustain_slider->addListener (this);

    level_sustain_slider->setBounds (144, 376, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    adsr->addListener(this);
    //[/Constructor]
}

TvfPanel::~TvfPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    adsr = nullptr;
    juce__label = nullptr;
    juce__label2 = nullptr;
    time1_slider = nullptr;
    time2_slider = nullptr;
    juce__label3 = nullptr;
    juce__label4 = nullptr;
    time3_slider = nullptr;
    time4_slider = nullptr;
    juce__label5 = nullptr;
    juce__label6 = nullptr;
    time5_slider = nullptr;
    level1_slider = nullptr;
    juce__label7 = nullptr;
    level2_slider = nullptr;
    juce__label8 = nullptr;
    level3_slider = nullptr;
    juce__label9 = nullptr;
    level_sustain_slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TvfPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TvfPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TvfPanel::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == time1_slider.get())
    {
        //[UserSliderCode_time1_slider] -- add your slider handling code here..
        adsr->getData().attackTime = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_time1_slider]
    }
    else if (sliderThatWasMoved == time2_slider.get())
    {
        //[UserSliderCode_time2_slider] -- add your slider handling code here..
        adsr->getData().retreatTime = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_time2_slider]
    }
    else if (sliderThatWasMoved == time3_slider.get())
    {
        //[UserSliderCode_time3_slider] -- add your slider handling code here..
        adsr->getData().regroupTime = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_time3_slider]
    }
    else if (sliderThatWasMoved == time4_slider.get())
    {
        //[UserSliderCode_time4_slider] -- add your slider handling code here..
        adsr->getData().decayTime = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_time4_slider]
    }
    else if (sliderThatWasMoved == time5_slider.get())
    {
        //[UserSliderCode_time5_slider] -- add your slider handling code here..
        adsr->getData().releaseTime = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_time5_slider]
    }
    else if (sliderThatWasMoved == level1_slider.get())
    {
        //[UserSliderCode_level1_slider] -- add your slider handling code here..
        adsr->getData().attackLevel = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_level1_slider]
    }
    else if (sliderThatWasMoved == level2_slider.get())
    {
        //[UserSliderCode_level2_slider] -- add your slider handling code here..
        adsr->getData().retreatLevel = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_level2_slider]
    }
    else if (sliderThatWasMoved == level3_slider.get())
    {
        //[UserSliderCode_level3_slider] -- add your slider handling code here..
        adsr->getData().regroupLevel = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_level3_slider]
    }
    else if (sliderThatWasMoved == level_sustain_slider.get())
    {
        //[UserSliderCode_level_sustain_slider] -- add your slider handling code here..
        adsr->getData().sustainLevel = sliderThatWasMoved->getValue();
        adsr->update();
        //[/UserSliderCode_level_sustain_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TvfPanel::adsrValueChanged(AdsrEditor::EnvelopeData* envelope)
{
    time1_slider->setValue(envelope->attackTime, juce::NotificationType::dontSendNotification);
    time2_slider->setValue(envelope->retreatTime, juce::NotificationType::dontSendNotification);
    time3_slider->setValue(envelope->regroupTime, juce::NotificationType::dontSendNotification);
    time4_slider->setValue(envelope->decayTime, juce::NotificationType::dontSendNotification);
    time5_slider->setValue(envelope->releaseTime, juce::NotificationType::dontSendNotification);
    level1_slider->setValue(envelope->attackLevel, juce::NotificationType::dontSendNotification);
    level2_slider->setValue(envelope->retreatLevel, juce::NotificationType::dontSendNotification);
    level3_slider->setValue(envelope->regroupLevel, juce::NotificationType::dontSendNotification);
    level_sustain_slider->setValue(envelope->sustainLevel, juce::NotificationType::dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TvfPanel" componentName=""
                 parentClasses="public juce::Component, public AdsrEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="new component" id="ee5f91a94c06992f" memberName="adsr"
                    virtualName="" explicitFocusOrder="0" pos="40 40 248 120" class="AdsrEditor"
                    params=""/>
  <LABEL name="new label" id="61fb3d84b4c83161" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="48 176 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6490b3f22410c753" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="48 200 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="b6efd0f393662a98" memberName="time1_slider"
          virtualName="" explicitFocusOrder="0" pos="144 176 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="bfbb95726b4ab430" memberName="time2_slider"
          virtualName="" explicitFocusOrder="0" pos="144 200 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="36b5c9dc84b46c77" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="48 224 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="41ee18167be224ef" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="48 248 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 4" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="17114648483bff81" memberName="time3_slider"
          virtualName="" explicitFocusOrder="0" pos="144 224 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="911176dfa3298844" memberName="time4_slider"
          virtualName="" explicitFocusOrder="0" pos="144 248 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="5a0a176034468dde" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="48 272 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 5" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1d62160628e4ef4e" memberName="juce__label6"
         virtualName="" explicitFocusOrder="0" pos="48 304 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="3eb7d71eba175f10" memberName="time5_slider"
          virtualName="" explicitFocusOrder="0" pos="144 272 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="3d8ba11ce25327f" memberName="level1_slider"
          virtualName="" explicitFocusOrder="0" pos="144 304 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="e4dbaae1b8a038da" memberName="juce__label7"
         virtualName="" explicitFocusOrder="0" pos="48 328 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="59647bdff027da2e" memberName="level2_slider"
          virtualName="" explicitFocusOrder="0" pos="144 328 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="3aad0890d28ac367" memberName="juce__label8"
         virtualName="" explicitFocusOrder="0" pos="48 352 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="37f4ba3330d29209" memberName="level3_slider"
          virtualName="" explicitFocusOrder="0" pos="144 352 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="81b2807d6e29d832" memberName="juce__label9"
         virtualName="" explicitFocusOrder="0" pos="48 376 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level Sustain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="9435bba427c2f77d" memberName="level_sustain_slider"
          virtualName="" explicitFocusOrder="0" pos="144 376 150 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

