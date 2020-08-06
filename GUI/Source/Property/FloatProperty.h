/*
  ==============================================================================

    FloatProperty.h
    Created: 5 Aug 2020 6:05:51pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "IProperty.h"

#include <stdexcept>
#include <string>
#include <cmath>

class FloatProperty : public IProperty
{
public:
    FloatProperty(std::string name, int address, int8_t minRaw, int8_t maxRaw, float minFloat, float maxFloat)
    : IProperty(name, address)
    , mValue(minFloat)
    , mMinRaw(minRaw)
    , mMaxRaw(maxRaw)
    , mMinFloat(minFloat)
    , mMaxFloat(maxFloat)
    {}
    
    float getMax() const
    {
        return mMaxFloat;
    }
    float getMin() const
    {
        return mMinFloat;
    }
    float getStep() const
    {
        return (mMaxFloat - mMinFloat) / (mMaxRaw - mMinRaw);
    }
    
    float value() const
    {
        if (mSet)
            return mValue;
        return mMinFloat;
    }
    
    void setValue(float val)
    {
        if (val < getMin() || val > getMax())
            throw std::runtime_error("Value out of range: " + std::to_string(val));
        
        mValue = val;
        mSet = true;
    }
    
    virtual void readJson(nlohmann::json jParent) override
    {
        if (jParent.count(mName))
        {
            setValue(jParent[mName].get<float>());
        }
    }
    
    virtual void writeJson(nlohmann::json& jParent) const override
    {
        if (mSet)
        {
            jParent[mName] = mValue;
        }
    }
    
    
    int8_t getRawValue() const override
    {
        float rawFloat = (mValue - mMinFloat) / (mMaxFloat - mMinFloat) * (mMaxRaw - mMinRaw) + mMinRaw;
        return round(rawFloat);
    }
    
    void setRawValue(int8_t val) override
    {
        if (val > mMaxRaw || val < mMinRaw)
            throw std::runtime_error("Value out of range: " + std::to_string(val));

        setValue(mMinFloat + (mMaxFloat - mMinFloat) * (((float)val - mMinRaw) / (mMaxRaw - mMinRaw)));
    }
    
private:
    float mValue;
    int8_t mMinRaw;
    int8_t mMaxRaw;
    float mMinFloat;
    float mMaxFloat;
};