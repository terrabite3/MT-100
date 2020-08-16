/*
  ==============================================================================

    WaveGeneratorProperty.h
    Created: 15 Aug 2020 3:47:20pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "ChoiceProperty.h"

class WaveGeneratorProperty : public GroupProperty
{
public:
    explicit WaveGeneratorProperty(int address)
    : GroupProperty("wave_generator", address)
    , pitchKeyfollow("pitch_keyfollow", address + 0x02, {
        "-1", "-1/2", "-1/4", "0", "1/8", "1/4", "3/8", "1/2", "5/8", "3/4", "7/8", "1", "5/4", "3/2", "2", "s1", "s2"
    })
    {
        registerWithChildren();
    }
    
    // pitch coarse
    // pitch fine
    ChoiceProperty pitchKeyfollow;
    // pitch bender sw
    // waveform
    // pcm wave number
    // pulse width
    // pulse width velocity sensitivity
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &pitchKeyfollow };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &pitchKeyfollow };
    }
};