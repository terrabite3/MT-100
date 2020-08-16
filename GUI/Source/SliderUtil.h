/*
  ==============================================================================

    SliderUtil.h
    Created: 15 Aug 2020 8:54:59pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Property/IntProperty.h"

void setupKnob(juce::Slider* knob, IntProperty* prop)
{
    knob->setRange(prop->getMin(), prop->getMax(), 1);
}