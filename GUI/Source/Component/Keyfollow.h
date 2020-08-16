/*
  ==============================================================================

    Keyfollow.h
    Created: 14 Aug 2020 8:29:06pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Property/ChoiceProperty.h"

class Keyfollow : public juce::Component
{
public:
    Keyfollow();
    ~Keyfollow() = default;
    
    void refreshFromProperty();
    void bindProperty(ChoiceProperty* prop);
    
private:
    void paint(juce::Graphics& g) override;
    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
    
    struct Tuning
    {
        int8_t rawValue;
        float slope;
        juce::String label;
    };
    
    std::vector<Tuning> mTunings;
    int mSelectedTuning;
    
    ChoiceProperty* mProp = nullptr;
};