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

#include "PartialPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PartialPanel::PartialPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__groupComponent.reset (new juce::GroupComponent ("new group",
                                                          TRANS("Wave Generator")));
    addAndMakeVisible (juce__groupComponent.get());

    juce__groupComponent->setBounds (32, 32, 360, 296);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Pitch Coarse")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (48, 56, 150, 24);

    juce__slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider.get());
    juce__slider->setRange (0, 10, 0);
    juce__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider->addListener (this);

    juce__slider->setBounds (216, 56, 150, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Pitch Fine")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (48, 88, 150, 24);

    juce__slider2.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider2.get());
    juce__slider2->setRange (0, 10, 0);
    juce__slider2->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider2->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider2->addListener (this);

    juce__slider2->setBounds (216, 88, 150, 24);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Pitch Keyfollow")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (48, 120, 150, 24);

    juce__comboBox.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox.get());
    juce__comboBox->setEditableText (false);
    juce__comboBox->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox->setTextWhenNothingSelected (juce::String());
    juce__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox->addItem (TRANS("-1"), 1);
    juce__comboBox->addItem (TRANS("-1/2"), 2);
    juce__comboBox->addItem (TRANS("-1/4"), 3);
    juce__comboBox->addItem (TRANS("0"), 4);
    juce__comboBox->addItem (TRANS("1/8"), 5);
    juce__comboBox->addItem (TRANS("1/4"), 6);
    juce__comboBox->addItem (TRANS("3/8"), 7);
    juce__comboBox->addItem (TRANS("1/2"), 8);
    juce__comboBox->addItem (TRANS("5/8"), 9);
    juce__comboBox->addItem (TRANS("3/4"), 10);
    juce__comboBox->addItem (TRANS("7/8"), 11);
    juce__comboBox->addItem (TRANS("1"), 12);
    juce__comboBox->addItem (TRANS("5/4"), 13);
    juce__comboBox->addItem (TRANS("3/2"), 14);
    juce__comboBox->addItem (TRANS("2"), 15);
    juce__comboBox->addItem (TRANS("s1"), 16);
    juce__comboBox->addItem (TRANS("s2"), 17);
    juce__comboBox->addListener (this);

    juce__comboBox->setBounds (216, 120, 150, 24);

    juce__label4.reset (new juce::Label ("new label",
                                         TRANS("Pitch Bend")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label4->setBounds (48, 152, 150, 24);

    juce__toggleButton.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (juce__toggleButton.get());
    juce__toggleButton->setButtonText (juce::String());
    juce__toggleButton->addListener (this);

    juce__toggleButton->setBounds (216, 152, 150, 24);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Waveform")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (48, 184, 150, 24);

    juce__comboBox2.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox2.get());
    juce__comboBox2->setEditableText (false);
    juce__comboBox2->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox2->setTextWhenNothingSelected (juce::String());
    juce__comboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox2->addItem (TRANS("SQU"), 1);
    juce__comboBox2->addItem (TRANS("SAW"), 2);
    juce__comboBox2->addListener (this);

    juce__comboBox2->setBounds (216, 184, 150, 24);

    juce__label6.reset (new juce::Label ("new label",
                                         TRANS("PCM Wave")));
    addAndMakeVisible (juce__label6.get());
    juce__label6->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label6->setJustificationType (juce::Justification::centredLeft);
    juce__label6->setEditable (false, false, false);
    juce__label6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label6->setBounds (48, 280, 150, 24);

    juce__comboBox3.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox3.get());
    juce__comboBox3->setEditableText (false);
    juce__comboBox3->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox3->setTextWhenNothingSelected (juce::String());
    juce__comboBox3->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox3->addItem (TRANS("Are the waveforms in the D50 manual correct?"), 1);
    juce__comboBox3->addListener (this);

    juce__comboBox3->setBounds (216, 280, 150, 24);

    juce__label7.reset (new juce::Label ("new label",
                                         TRANS("Pulse Width")));
    addAndMakeVisible (juce__label7.get());
    juce__label7->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label7->setJustificationType (juce::Justification::centredLeft);
    juce__label7->setEditable (false, false, false);
    juce__label7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label7->setBounds (48, 216, 150, 24);

    juce__slider3.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider3.get());
    juce__slider3->setRange (0, 10, 0);
    juce__slider3->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider3->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider3->addListener (this);

    juce__slider3->setBounds (216, 216, 150, 24);

    juce__label8.reset (new juce::Label ("new label",
                                         TRANS("Velocity Sensitivity")));
    addAndMakeVisible (juce__label8.get());
    juce__label8->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label8->setJustificationType (juce::Justification::centredLeft);
    juce__label8->setEditable (false, false, false);
    juce__label8->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label8->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label8->setBounds (48, 248, 150, 24);

    juce__slider4.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider4.get());
    juce__slider4->setRange (0, 10, 0);
    juce__slider4->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider4->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider4->addListener (this);

    juce__slider4->setBounds (216, 248, 150, 24);

    juce__groupComponent2.reset (new juce::GroupComponent ("new group",
                                                           TRANS("Pitch Envelope")));
    addAndMakeVisible (juce__groupComponent2.get());

    juce__groupComponent2->setBounds (32, 344, 360, 424);

    juce__label9.reset (new juce::Label ("new label",
                                         TRANS("Depth")));
    addAndMakeVisible (juce__label9.get());
    juce__label9->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label9->setJustificationType (juce::Justification::centredLeft);
    juce__label9->setEditable (false, false, false);
    juce__label9->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label9->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label9->setBounds (48, 368, 150, 24);

    juce__slider5.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider5.get());
    juce__slider5->setRange (0, 10, 0);
    juce__slider5->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider5->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider5->addListener (this);

    juce__slider5->setBounds (216, 368, 150, 24);

    juce__label10.reset (new juce::Label ("new label",
                                          TRANS("Velocity Sensitivity")));
    addAndMakeVisible (juce__label10.get());
    juce__label10->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label10->setJustificationType (juce::Justification::centredLeft);
    juce__label10->setEditable (false, false, false);
    juce__label10->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label10->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label10->setBounds (48, 400, 166, 24);

    juce__slider6.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider6.get());
    juce__slider6->setRange (0, 10, 0);
    juce__slider6->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider6->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider6->addListener (this);

    juce__slider6->setBounds (216, 400, 152, 24);

    juce__label11.reset (new juce::Label ("new label",
                                          TRANS("Time Keyfollow")));
    addAndMakeVisible (juce__label11.get());
    juce__label11->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label11->setJustificationType (juce::Justification::centredLeft);
    juce__label11->setEditable (false, false, false);
    juce__label11->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label11->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label11->setBounds (48, 432, 150, 24);

    juce__slider7.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider7.get());
    juce__slider7->setRange (0, 10, 0);
    juce__slider7->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider7->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider7->addListener (this);

    juce__slider7->setBounds (216, 432, 150, 24);

    juce__label12.reset (new juce::Label ("new label",
                                          TRANS("Time 1")));
    addAndMakeVisible (juce__label12.get());
    juce__label12->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label12->setJustificationType (juce::Justification::centredLeft);
    juce__label12->setEditable (false, false, false);
    juce__label12->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label12->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label12->setBounds (48, 464, 150, 24);

    juce__slider8.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider8.get());
    juce__slider8->setRange (0, 10, 0);
    juce__slider8->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider8->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider8->addListener (this);

    juce__slider8->setBounds (216, 464, 150, 24);

    juce__label13.reset (new juce::Label ("new label",
                                          TRANS("Time 2")));
    addAndMakeVisible (juce__label13.get());
    juce__label13->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label13->setJustificationType (juce::Justification::centredLeft);
    juce__label13->setEditable (false, false, false);
    juce__label13->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label13->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label13->setBounds (48, 496, 150, 24);

    juce__slider9.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider9.get());
    juce__slider9->setRange (0, 10, 0);
    juce__slider9->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider9->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider9->addListener (this);

    juce__slider9->setBounds (216, 496, 150, 24);

    juce__label14.reset (new juce::Label ("new label",
                                          TRANS("Time 3")));
    addAndMakeVisible (juce__label14.get());
    juce__label14->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label14->setJustificationType (juce::Justification::centredLeft);
    juce__label14->setEditable (false, false, false);
    juce__label14->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label14->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label14->setBounds (48, 528, 150, 24);

    juce__slider10.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider10.get());
    juce__slider10->setRange (0, 10, 0);
    juce__slider10->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider10->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider10->addListener (this);

    juce__slider10->setBounds (216, 528, 150, 24);

    juce__label15.reset (new juce::Label ("new label",
                                          TRANS("Time 4")));
    addAndMakeVisible (juce__label15.get());
    juce__label15->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label15->setJustificationType (juce::Justification::centredLeft);
    juce__label15->setEditable (false, false, false);
    juce__label15->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label15->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label15->setBounds (48, 560, 150, 24);

    juce__slider11.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider11.get());
    juce__slider11->setRange (0, 10, 0);
    juce__slider11->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider11->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider11->addListener (this);

    juce__slider11->setBounds (216, 560, 150, 24);

    juce__label16.reset (new juce::Label ("new label",
                                          TRANS("Level 0")));
    addAndMakeVisible (juce__label16.get());
    juce__label16->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label16->setJustificationType (juce::Justification::centredLeft);
    juce__label16->setEditable (false, false, false);
    juce__label16->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label16->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label16->setBounds (48, 592, 150, 24);

    juce__slider12.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider12.get());
    juce__slider12->setRange (0, 10, 0);
    juce__slider12->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider12->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider12->addListener (this);

    juce__slider12->setBounds (216, 592, 150, 24);

    juce__label17.reset (new juce::Label ("new label",
                                          TRANS("Level 1")));
    addAndMakeVisible (juce__label17.get());
    juce__label17->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label17->setJustificationType (juce::Justification::centredLeft);
    juce__label17->setEditable (false, false, false);
    juce__label17->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label17->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label17->setBounds (48, 624, 150, 24);

    juce__slider13.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider13.get());
    juce__slider13->setRange (0, 10, 0);
    juce__slider13->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider13->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider13->addListener (this);

    juce__slider13->setBounds (216, 624, 150, 24);

    juce__label18.reset (new juce::Label ("new label",
                                          TRANS("Level 2")));
    addAndMakeVisible (juce__label18.get());
    juce__label18->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label18->setJustificationType (juce::Justification::centredLeft);
    juce__label18->setEditable (false, false, false);
    juce__label18->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label18->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label18->setBounds (48, 656, 150, 24);

    juce__slider14.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider14.get());
    juce__slider14->setRange (0, 10, 0);
    juce__slider14->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider14->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider14->addListener (this);

    juce__slider14->setBounds (216, 656, 150, 24);

    juce__label19.reset (new juce::Label ("new label",
                                          TRANS("Level Sustain")));
    addAndMakeVisible (juce__label19.get());
    juce__label19->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label19->setJustificationType (juce::Justification::centredLeft);
    juce__label19->setEditable (false, false, false);
    juce__label19->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label19->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label19->setBounds (48, 688, 150, 24);

    juce__slider15.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider15.get());
    juce__slider15->setRange (0, 10, 0);
    juce__slider15->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider15->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider15->addListener (this);

    juce__slider15->setBounds (216, 688, 150, 24);

    juce__label20.reset (new juce::Label ("new label",
                                          TRANS("Level End")));
    addAndMakeVisible (juce__label20.get());
    juce__label20->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label20->setJustificationType (juce::Justification::centredLeft);
    juce__label20->setEditable (false, false, false);
    juce__label20->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label20->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label20->setBounds (48, 720, 150, 24);

    juce__slider16.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider16.get());
    juce__slider16->setRange (0, 10, 0);
    juce__slider16->setSliderStyle (juce::Slider::LinearHorizontal);
    juce__slider16->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider16->addListener (this);

    juce__slider16->setBounds (216, 720, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PartialPanel::~PartialPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__groupComponent = nullptr;
    juce__label = nullptr;
    juce__slider = nullptr;
    juce__label2 = nullptr;
    juce__slider2 = nullptr;
    juce__label3 = nullptr;
    juce__comboBox = nullptr;
    juce__label4 = nullptr;
    juce__toggleButton = nullptr;
    juce__label5 = nullptr;
    juce__comboBox2 = nullptr;
    juce__label6 = nullptr;
    juce__comboBox3 = nullptr;
    juce__label7 = nullptr;
    juce__slider3 = nullptr;
    juce__label8 = nullptr;
    juce__slider4 = nullptr;
    juce__groupComponent2 = nullptr;
    juce__label9 = nullptr;
    juce__slider5 = nullptr;
    juce__label10 = nullptr;
    juce__slider6 = nullptr;
    juce__label11 = nullptr;
    juce__slider7 = nullptr;
    juce__label12 = nullptr;
    juce__slider8 = nullptr;
    juce__label13 = nullptr;
    juce__slider9 = nullptr;
    juce__label14 = nullptr;
    juce__slider10 = nullptr;
    juce__label15 = nullptr;
    juce__slider11 = nullptr;
    juce__label16 = nullptr;
    juce__slider12 = nullptr;
    juce__label17 = nullptr;
    juce__slider13 = nullptr;
    juce__label18 = nullptr;
    juce__slider14 = nullptr;
    juce__label19 = nullptr;
    juce__slider15 = nullptr;
    juce__label20 = nullptr;
    juce__slider16 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PartialPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PartialPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PartialPanel::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == juce__slider.get())
    {
        //[UserSliderCode_juce__slider] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider]
    }
    else if (sliderThatWasMoved == juce__slider2.get())
    {
        //[UserSliderCode_juce__slider2] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider2]
    }
    else if (sliderThatWasMoved == juce__slider3.get())
    {
        //[UserSliderCode_juce__slider3] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider3]
    }
    else if (sliderThatWasMoved == juce__slider4.get())
    {
        //[UserSliderCode_juce__slider4] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider4]
    }
    else if (sliderThatWasMoved == juce__slider5.get())
    {
        //[UserSliderCode_juce__slider5] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider5]
    }
    else if (sliderThatWasMoved == juce__slider6.get())
    {
        //[UserSliderCode_juce__slider6] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider6]
    }
    else if (sliderThatWasMoved == juce__slider7.get())
    {
        //[UserSliderCode_juce__slider7] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider7]
    }
    else if (sliderThatWasMoved == juce__slider8.get())
    {
        //[UserSliderCode_juce__slider8] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider8]
    }
    else if (sliderThatWasMoved == juce__slider9.get())
    {
        //[UserSliderCode_juce__slider9] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider9]
    }
    else if (sliderThatWasMoved == juce__slider10.get())
    {
        //[UserSliderCode_juce__slider10] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider10]
    }
    else if (sliderThatWasMoved == juce__slider11.get())
    {
        //[UserSliderCode_juce__slider11] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider11]
    }
    else if (sliderThatWasMoved == juce__slider12.get())
    {
        //[UserSliderCode_juce__slider12] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider12]
    }
    else if (sliderThatWasMoved == juce__slider13.get())
    {
        //[UserSliderCode_juce__slider13] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider13]
    }
    else if (sliderThatWasMoved == juce__slider14.get())
    {
        //[UserSliderCode_juce__slider14] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider14]
    }
    else if (sliderThatWasMoved == juce__slider15.get())
    {
        //[UserSliderCode_juce__slider15] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider15]
    }
    else if (sliderThatWasMoved == juce__slider16.get())
    {
        //[UserSliderCode_juce__slider16] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider16]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PartialPanel::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == juce__comboBox.get())
    {
        //[UserComboBoxCode_juce__comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox]
    }
    else if (comboBoxThatHasChanged == juce__comboBox2.get())
    {
        //[UserComboBoxCode_juce__comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox2]
    }
    else if (comboBoxThatHasChanged == juce__comboBox3.get())
    {
        //[UserComboBoxCode_juce__comboBox3] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox3]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PartialPanel::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == juce__toggleButton.get())
    {
        //[UserButtonCode_juce__toggleButton] -- add your button handler code here..
        //[/UserButtonCode_juce__toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PartialPanel" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="new group" id="d59dfbf4b60da6c3" memberName="juce__groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="32 32 360 296" title="Wave Generator"/>
  <LABEL name="new label" id="462ab753863c1e73" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="48 56 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Coarse" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="c3c1e93565e0d2a8" memberName="juce__slider"
          virtualName="" explicitFocusOrder="0" pos="216 56 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="24a967b3b4f4001e" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="48 88 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Fine" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="ec55de27f2667cef" memberName="juce__slider2"
          virtualName="" explicitFocusOrder="0" pos="216 88 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="fe6517a95071b00b" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="48 120 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Keyfollow" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="fd9476e371a9ed47" memberName="juce__comboBox"
            virtualName="" explicitFocusOrder="0" pos="216 120 150 24" editable="0"
            layout="33" items="-1&#10;-1/2&#10;-1/4&#10;0&#10;1/8&#10;1/4&#10;3/8&#10;1/2&#10;5/8&#10;3/4&#10;7/8&#10;1&#10;5/4&#10;3/2&#10;2&#10;s1&#10;s2"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="488b94030df24f10" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="48 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Bend" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f70745598216f676" memberName="juce__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="216 152 150 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="e1cd169426b2bae8" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="48 184 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Waveform" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="a5260898d939c693" memberName="juce__comboBox2"
            virtualName="" explicitFocusOrder="0" pos="216 184 150 24" editable="0"
            layout="33" items="SQU&#10;SAW" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="e637e4bc42d5c638" memberName="juce__label6"
         virtualName="" explicitFocusOrder="0" pos="48 280 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PCM Wave" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="df88f4a4f812ad" memberName="juce__comboBox3"
            virtualName="" explicitFocusOrder="0" pos="216 280 150 24" editable="0"
            layout="33" items="Are the waveforms in the D50 manual correct?"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f60f59da99f7be2c" memberName="juce__label7"
         virtualName="" explicitFocusOrder="0" pos="48 216 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pulse Width" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="d10d1b73ee731244" memberName="juce__slider3"
          virtualName="" explicitFocusOrder="0" pos="216 216 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="d0799237d3504e6f" memberName="juce__label8"
         virtualName="" explicitFocusOrder="0" pos="48 248 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Velocity Sensitivity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="ca0a5a81a6017fe3" memberName="juce__slider4"
          virtualName="" explicitFocusOrder="0" pos="216 248 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <GROUPCOMPONENT name="new group" id="60eec9af17cd7feb" memberName="juce__groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="32 344 360 424" title="Pitch Envelope"/>
  <LABEL name="new label" id="35827b7196cc0f10" memberName="juce__label9"
         virtualName="" explicitFocusOrder="0" pos="48 368 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Depth" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="37e8521de83591de" memberName="juce__slider5"
          virtualName="" explicitFocusOrder="0" pos="216 368 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="29a249031f865169" memberName="juce__label10"
         virtualName="" explicitFocusOrder="0" pos="48 400 166 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Velocity Sensitivity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="148c33dd5f47e158" memberName="juce__slider6"
          virtualName="" explicitFocusOrder="0" pos="216 400 152 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="bfe4c0d00c51e7f2" memberName="juce__label11"
         virtualName="" explicitFocusOrder="0" pos="48 432 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time Keyfollow" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="1cdb14727f9b10d6" memberName="juce__slider7"
          virtualName="" explicitFocusOrder="0" pos="216 432 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="fd952a7a928b2afc" memberName="juce__label12"
         virtualName="" explicitFocusOrder="0" pos="48 464 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="e410047c63c1372b" memberName="juce__slider8"
          virtualName="" explicitFocusOrder="0" pos="216 464 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="36916f9ec02682a9" memberName="juce__label13"
         virtualName="" explicitFocusOrder="0" pos="48 496 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="e33392cbdee1ea53" memberName="juce__slider9"
          virtualName="" explicitFocusOrder="0" pos="216 496 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="6a8c4669d6c4f5db" memberName="juce__label14"
         virtualName="" explicitFocusOrder="0" pos="48 528 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="2e3ef704870f5241" memberName="juce__slider10"
          virtualName="" explicitFocusOrder="0" pos="216 528 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="b169fa05cf30de79" memberName="juce__label15"
         virtualName="" explicitFocusOrder="0" pos="48 560 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time 4" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="46aa9904bbd28896" memberName="juce__slider11"
          virtualName="" explicitFocusOrder="0" pos="216 560 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="63d87c3400fb67c" memberName="juce__label16"
         virtualName="" explicitFocusOrder="0" pos="48 592 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="a3e8eff384f14cc5" memberName="juce__slider12"
          virtualName="" explicitFocusOrder="0" pos="216 592 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="53297c9db18c535f" memberName="juce__label17"
         virtualName="" explicitFocusOrder="0" pos="48 624 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="4de73432e6b852e3" memberName="juce__slider13"
          virtualName="" explicitFocusOrder="0" pos="216 624 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="37266fffb200dc8a" memberName="juce__label18"
         virtualName="" explicitFocusOrder="0" pos="48 656 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="66d3103907b6c4d8" memberName="juce__slider14"
          virtualName="" explicitFocusOrder="0" pos="216 656 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="fccb3964718f054f" memberName="juce__label19"
         virtualName="" explicitFocusOrder="0" pos="48 688 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level Sustain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="a08a897354ca0ad8" memberName="juce__slider15"
          virtualName="" explicitFocusOrder="0" pos="216 688 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="3f71cc7d6010e156" memberName="juce__label20"
         virtualName="" explicitFocusOrder="0" pos="48 720 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level End" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="7939cacf71d7e9ea" memberName="juce__slider16"
          virtualName="" explicitFocusOrder="0" pos="216 720 150 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

