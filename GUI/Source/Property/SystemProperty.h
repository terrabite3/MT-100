/*
  ==============================================================================

    SystemProperty.h
    Created: 1 Aug 2020 1:35:32pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "IntProperty.h"
#include "FloatProperty.h"
#include "ChoiceProperty.h"

class SystemProperty : public GroupProperty
{
public:
    explicit SystemProperty(int address)
    : GroupProperty("system", address)
    , masterTune(FloatProperty("master_tune", address + 0x00, 0, 127, 432.1, 457.6))
    , reverbMode("reverb_mode", address + 0x01, {"Room", "Hall", "Plate", "Tap delay"})
    , masterVolume(IntProperty("master_volume", address + 0x16, 100))
    {}
    
    FloatProperty masterTune;
    ChoiceProperty reverbMode;
    // reverb_time
    // reverb_level
    // partial_reserve
    // midi_channel
    IntProperty masterVolume;
    
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &masterTune, &reverbMode, &masterVolume };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &masterTune, &reverbMode, &masterVolume };
    }
};