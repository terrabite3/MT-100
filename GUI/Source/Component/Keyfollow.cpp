/*
  ==============================================================================

    Keyfollow.cpp
    Created: 14 Aug 2020 8:29:06pm
    Author:  Stefan Titus

  ==============================================================================
*/

#include "Keyfollow.h"

using namespace juce;

Keyfollow::Keyfollow()
{
    mTunings = {
        {0,  -1,     CharPointer_UTF8("-1")},
        {1,  -0.5,   CharPointer_UTF8("-½")},
        {2,  -0.25,  CharPointer_UTF8("-¼")},
        {3,  0,      CharPointer_UTF8("0")},
        {4,  0.125,  CharPointer_UTF8("⅛")},
        {5,  0.25,   CharPointer_UTF8("¼")},
        {6,  0.375,  CharPointer_UTF8("⅜")},
        {7,  0.5,    CharPointer_UTF8("½")},
        {8,  0.625,  CharPointer_UTF8("⅝")},
        {9,  0.75,   CharPointer_UTF8("¾")},
        {10, 0.875,  CharPointer_UTF8("⅞")},
        {11, 1,      CharPointer_UTF8("1")},
        // The stretch tunings come after 2 in the raw values, but after 1 in sound.
        // The slope is chosen for esthetics, not accuracy.
        {15, 1.07,   CharPointer_UTF8("s¹")},
        {16, 1.14,   CharPointer_UTF8("s²")},
        {12, 1.25,   CharPointer_UTF8("1¼")},
        {13, 1.5,    CharPointer_UTF8("1½")},
        {14, 2,      CharPointer_UTF8("2")},
    };

    mSelectedTuning = 11; // 1
}


void Keyfollow::refreshFromProperty()
{
    if (mProp)
    {
        auto rawIndex = mProp->getRawValue();
        for (int i = 0; i < mTunings.size(); ++i)
        {
            if (mTunings[i].rawValue == rawIndex)
            {
                mSelectedTuning = i;
            }
        }
        
        repaint();
    }
}

void Keyfollow::bindProperty(ChoiceProperty* prop)
{
    mProp = prop;
}

void Keyfollow::paint(Graphics& g)
{
    float margin = 20;
    
    float left = 0;
    float right = getWidth() - margin;
    float top = margin;
    float bottom = getHeight();
    
    float width = right - left;
    float height = bottom - top;
    
    float centerX = (right + left) / 2;
    float centerY = (top + bottom) / 2;
    
    
    
    
    for (int i = 0; i < mTunings.size(); ++i)
    {
        float slope = mTunings[i].slope;
        String name = mTunings[i].label;
        
        
        float rise = slope * centerX;
        
        float x0 = left;
        float x1 = right;
        float y0 = centerY + rise;
        float y1 = centerY - rise;
        
        if (slope > 1)
        {
            y1 = centerY - height / 2;
            x1 = centerX + height / 2 / slope;
        }
        
        g.setColour(Colours::lightgrey);
        g.drawLine(x0, y0, x1, y1);
        
        
        if (i == mSelectedTuning)
        {
            g.setColour(Colours::cornflowerblue);
        }
        
        if (slope <= 1)
        {
            x1 += 3;
            y1 -= slope * 2;
            
            if (slope == -1)
            {
                y1 -= 8;
            }
            
            g.drawText(name, x1, y1 - 10, margin - 2, 20, Justification::centredLeft);
        }
        else
        {
            x1 += 2 / slope;
            y1 -= 2;
            
            g.drawText(name, x1 - 10, y1 - margin, 20, margin, Justification::centredBottom);
        }
        
    }
    
    
    // Draw selected slope again so it's on top
    {
        float slope = mTunings[mSelectedTuning].slope;
        
        float rise = slope * centerX;
        
        float x0 = left;
        float x1 = right;
        float y0 = centerY + rise;
        float y1 = centerY - rise;
        
        if (slope > 1)
        {
            y1 = centerY - height / 2;
            x1 = centerX + height / 2 / slope;
        }
        
        g.setColour(Colours::cornflowerblue);
        float thickness = 2;
        
        g.drawLine(x0, y0, x1, y1, thickness);
    }
    
    
    // Border
    g.setColour(Colours::lightgrey);
    g.drawRect(left, top, right - left, bottom - top, 2.f);
    
    
}

void Keyfollow::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if (wheel.deltaY > 0)
    {
        if (mSelectedTuning < mTunings.size() - 1)
            mSelectedTuning++;

    }
    else if (wheel.deltaY < 0)
    {
        if (mSelectedTuning > 0)
            mSelectedTuning--;
    }
    
    if (mProp)
    {
        mProp->setRawValue(mTunings[mSelectedTuning].rawValue);
    }
    
    repaint();
}
