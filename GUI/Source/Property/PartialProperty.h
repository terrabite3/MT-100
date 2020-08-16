/*
  ==============================================================================

    PartialProperty.h
    Created: 15 Aug 2020 3:46:57pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "WaveGeneratorProperty.h"
#include "PartialPitchProperty.h"
#include "FilterProperty.h"

class PartialProperty : public GroupProperty
{
public:
    explicit PartialProperty(std::string name, int address)
    : GroupProperty(name, address)
    , waveGenerator(address + 0x0)
    , pitch(address + 0x8)
    , filter(address + 0x17)
    {
        registerWithChildren();
    }
    
    WaveGeneratorProperty waveGenerator;
    PartialPitchProperty pitch;
    FilterProperty filter;
    // tva
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &waveGenerator, &pitch, &filter };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &waveGenerator, &pitch, &filter };
    }
};