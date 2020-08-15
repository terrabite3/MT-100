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
    
}

void Keyfollow::resized()
{
    
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
    
    
    float s1 = 1.1;
    float s2 = 1.2;
    std::vector<float> slopes
    {
        -1, -0.5, -0.25, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1, 1.5, 2, s1, s2
    };
    std::vector<String> slopeNames
    {
        CharPointer_UTF8("-1"),
        CharPointer_UTF8("-½"),
        CharPointer_UTF8("-¼"),
        CharPointer_UTF8("0"),
        CharPointer_UTF8("⅛"),
        CharPointer_UTF8("¼"),
        CharPointer_UTF8("⅜"),
        CharPointer_UTF8("½"),
        CharPointer_UTF8("⅝"),
        CharPointer_UTF8("¾"),
        CharPointer_UTF8("⅞"),
        CharPointer_UTF8("1"),
        CharPointer_UTF8("1½"),
        CharPointer_UTF8("2"),
        CharPointer_UTF8("s¹"),
        CharPointer_UTF8("s²")
    };
    
    
    float selectedSlope = slopes[mSelectedSlopeIndex];
    
    
    for (int i = 0; i < slopes.size(); ++i)
    {
        float slope = slopes[i];
        String name = slopeNames[i];
        
        
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
        
        
        if (slope == selectedSlope)
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
            
            if (slope == s1)
            {
                x1 += 4;
            }
            
            g.drawText(name, x1 - 10, y1 - margin, 20, margin, Justification::centredBottom);
        }
        
    }
    
    
    // Draw selected slope again so it's on top
    {
        float slope = selectedSlope;
        
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
        if (mSelectedSlopeIndex < mNumSlopes - 1)
            mSelectedSlopeIndex++;

    }
    else if (wheel.deltaY < 0)
    {
        if (mSelectedSlopeIndex > 0)
            mSelectedSlopeIndex--;
    }
    
    repaint();
}
