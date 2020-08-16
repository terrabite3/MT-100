/*
  ==============================================================================

    FilterProperty.h
    Created: 16 Aug 2020 12:27:26pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "FilterEnvelopeProperty.h"

class FilterProperty : public GroupProperty
{
public:
    explicit FilterProperty(int address)
    : GroupProperty("time_variant_filter", address)
    , envelope(address + 0x5)
    {
        registerWithChildren();
    }
    
    // cutoff freq
    // resonance
    // keyfollow
    // bias
    FilterEnvelopeProperty envelope;
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &envelope };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &envelope };
    }
};