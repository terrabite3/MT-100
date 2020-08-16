/*
  ==============================================================================

    TimbreProperty.h
    Created: 15 Aug 2020 3:46:27pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "PartialProperty.h"

class TimbreProperty : public GroupProperty
{
public:
    explicit TimbreProperty(std::string number, int address)
    : GroupProperty(number, address)
    , partial1("partial_parameter_1", address + 0x0E)
    {
        registerWithChildren();
    }
    
    // common
    PartialProperty partial1;
    // partial2
    // partial3
    // partial4
    // dummy
    
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &partial1 };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &partial1 };
    }
    
};