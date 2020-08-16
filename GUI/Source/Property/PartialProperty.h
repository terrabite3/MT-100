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

class PartialProperty : public GroupProperty
{
public:
    explicit PartialProperty(std::string name, int address)
    : GroupProperty(name, address)
    , waveGenerator(address + 0x0)
    {
        registerWithChildren();
    }
    
    WaveGeneratorProperty waveGenerator;
    // pitch
    // tvf
    // tva
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &waveGenerator };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &waveGenerator };
    }
};