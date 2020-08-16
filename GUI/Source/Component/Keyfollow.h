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
    void resized() override;
    void paint(juce::Graphics& g) override;
    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
    
    int mSelectedSlopeIndex = 11;
    const static int mNumSlopes = 16;
    
    ChoiceProperty* mProp = nullptr;
};