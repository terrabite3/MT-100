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
    , masterTune("master_tune", address + 0x00, 0, 127, 432.1, 457.6)
    , reverbMode("reverb_mode", address + 0x01, {"Room", "Hall", "Plate", "Tap delay"})
    , reverbTime("reverb_time", address + 0x02, 7, 1)
    , reverbLevel("reverb_level", address + 0x03, 7)
    , masterVolume("master_volume", address + 0x16, 100)
    {}
    
    FloatProperty masterTune;
    ChoiceProperty reverbMode;
    IntProperty reverbTime;
    IntProperty reverbLevel;
    // partial_reserve
    // midi_channel
    IntProperty masterVolume;
    
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &masterTune, &reverbMode, &reverbTime, &reverbLevel, &masterVolume };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &masterTune, &reverbMode, &reverbTime, &reverbLevel, &masterVolume };
    }
};