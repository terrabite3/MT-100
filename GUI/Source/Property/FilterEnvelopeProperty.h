/*
  ==============================================================================

    FilterEnvelopeProperty.h
    Created: 16 Aug 2020 12:27:06pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "IntProperty.h"

class FilterEnvelopeProperty : public GroupProperty
{
public:
    explicit FilterEnvelopeProperty(int address)
    : GroupProperty("envelope", address)
    , depth("depth", address + 0x0, 100)
    , veloSens("velo_sens", address + 0x1, 100)
    , depthKeyfollow("depth_keyfollow", address + 0x2, 4)
    , timeKeyfollow("time_keyfollow", address + 0x3, 4)
    , time1("time_1", address + 0x4, 100)
    , time2("time_2", address + 0x5, 100)
    , time3("time_3", address + 0x6, 100)
    , time4("time_4", address + 0x7, 100)
    , time5("time_5", address + 0x8, 100)
    , level1("level_1", address + 0x9, 100)
    , level2("level_2", address + 0xA, 100)
    , level3("level_3", address + 0xB, 100)
    , levelSustain("level_sustain", address + 0xC, 100)
    {
        registerWithChildren();
    }
    
    IntProperty depth;
    IntProperty veloSens;
    IntProperty depthKeyfollow;
    IntProperty timeKeyfollow;
    IntProperty time1;
    IntProperty time2;
    IntProperty time3;
    IntProperty time4;
    IntProperty time5;
    IntProperty level1;
    IntProperty level2;
    IntProperty level3;
    IntProperty levelSustain;
    
    std::vector<const IProperty*> getChildren() const override
    {
        return 
        {
            &depth, &veloSens, &depthKeyfollow, &timeKeyfollow, 
            &time1, &time2, &time3, &time4, &time5, 
            &level1, &level2, &level3, &levelSustain
        };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return 
        {
            &depth, &veloSens, &depthKeyfollow, &timeKeyfollow, 
            &time1, &time2, &time3, &time4, &time5, 
            &level1, &level2, &level3, &levelSustain
        };
    }
};