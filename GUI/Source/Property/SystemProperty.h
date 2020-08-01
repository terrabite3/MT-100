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

class SystemProperty : public GroupProperty
{
public:
    explicit SystemProperty(int address)
    : GroupProperty("system", address)
    , masterVolume(IntProperty("master_volume", address + 0x16, 100))
    {}
    
    // master_tune
    // reverb_mode
    // reverb_time
    // reverb_level
    // partial_reserve
    // midi_channel
    IntProperty masterVolume;
    
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &masterVolume };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &masterVolume };
    }
};