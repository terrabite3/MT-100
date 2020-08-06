/*
  ==============================================================================

    ChoiceProperty.h
    Created: 5 Aug 2020 6:52:40pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "IProperty.h"

#include <stdexcept>
#include <string>
#include <vector>

class ChoiceProperty : public IProperty
{
public:
    ChoiceProperty(std::string name, int address, std::vector<std::string> choices)
    : IProperty(name, address)
    , mChoices(choices)
    {}
    
    std::vector<std::string> getChoices() const
    {
        return mChoices;
    }
    
    std::string value() const
    {
        if (mSet)
            return mValue;
        return "";
    }
    
    void setValue(std::string val)
    {
        for (int i = 0; i < mChoices.size(); ++i)
        {
            if (val == mChoices[i])
            {
                mValue = val;
                mSet = true;
                return;
            }
        }
        
        throw std::runtime_error("Value not a valid choice: " + val);
    }
    
    virtual void readJson(nlohmann::json jParent) override
    {
        if (jParent.count(mName))
        {
            setValue(jParent[mName].get<std::string>());
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
        for (int8_t i = 0; i < mChoices.size(); ++i)
        {
            if (mChoices[i] == mValue)
                return i;
        }
        
        throw std::runtime_error("Value not a valid choice: " + mValue);
    }
    
    void setRawValue(int8_t val) override
    {
        if (val >= mChoices.size() || val < 0)
            throw std::runtime_error("Value out of range: " + std::to_string(val));
        setValue(mChoices[val]);
    }
    
private:
    std::string mValue;
    std::vector<std::string> mChoices;
};