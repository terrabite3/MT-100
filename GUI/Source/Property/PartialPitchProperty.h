/*
  ==============================================================================

    PartialPitch.h
    Created: 15 Aug 2020 6:23:11pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "IntProperty.h"

class PitchLfoProperty : public GroupProperty
{
public:
    explicit PitchLfoProperty(int address)
    : GroupProperty("lfo", address)
    , rate("rate", address + 0x0, 100)
    , depth("depth", address + 0x1, 100)
    , modSensitivity("mod_sens", address + 0x2, 100)
    {
        registerWithChildren();
    }
    
    IntProperty rate;
    IntProperty depth;
    IntProperty modSensitivity;
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &rate, &depth, &modSensitivity };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &rate, &depth, &modSensitivity };
    }
};

class PartialPitchProperty : public GroupProperty
{
public:
    explicit PartialPitchProperty(int address)
    : GroupProperty("pitch", address)
    , lfo(address + 0xC)
    {
        registerWithChildren();
    }
    
    PitchLfoProperty lfo;
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &lfo };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &lfo };
    }
};