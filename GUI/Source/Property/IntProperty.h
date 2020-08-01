/*
  ==============================================================================

    IntProperty.h
    Created: 30 Jul 2020 7:04:48pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "IProperty.h"

#include <stdexcept>
#include <string>

class IntProperty : public IProperty
{
public:
    IntProperty(std::string name, int address, int8_t maxRaw = 127, int offset = 0)
    : IProperty(name, address)
    , mMaxRaw(maxRaw)
    , mOffset(offset)
    {}
    
    int getMax() const
    {
        return mMaxRaw + mOffset;
    }
    int getMin() const
    {
        return mOffset;
    }
    
    int value() const
    {
        if (mSet)
            return mValue;
        return 0;
    }
    
    void setValue(int val)
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
            setValue(jParent[mName].get<int>());
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
        return value() - mOffset;
    }
    
    void setRawValue(int8_t val) override
    {
        if (val > mMaxRaw)
            throw std::runtime_error("Value out of range: " + std::to_string(val));
        setValue(val + mOffset);
    }
    
private:
    int mValue;
    int8_t mMaxRaw;
    int mOffset;
};