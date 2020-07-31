/*
  ==============================================================================

    SourceCode.h
    Created: 28 Jul 2020 7:25:23pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "json.hpp"
#include "Memory/SysExMemory.h"

#include <string>

template <typename ValueType>
class IProperty
{
public:
    IProperty(std::string name, int address)
    : mName(name)
    , mAddress(address)
    , mSet(false)
    {}
    
    virtual ~IProperty() = default;
    
    std::string name() const
    { return mName; }
    int address() const
    { return mAddress; }
    
    virtual ValueType value() const
    { return mValue; }
    virtual void setValue(ValueType val)
    {
        mValue = val;
        mSet = true;
    }
    bool isSet() const
    {
        return mSet;
    }
    
    void reset()
    {
        mValue = ValueType();
        mSet = false;
    }
    
    virtual void readJson(nlohmann::json jParent)
    {
        if (jParent.count(mName))
        {
            setValue(jParent[mName].template get<ValueType>());
        }
    }
    
    virtual void writeJson(nlohmann::json& jParent) const
    {
        if (mSet)
        {
            jParent[mName] = mValue;
        }
    }
    
    virtual void readMemory(const IMemory& memory)
    {
        if (memory.set(mAddress))
        {
            setRawValue(memory.at(mAddress));
            mSet = true;
        }
    }
    
    virtual void writeMemory(IMemory& memory) const
    {
        if (mSet)
        {
            memory.write(mAddress, getRawValue());
        }
    }
    
    virtual int8_t getRawValue() const = 0;
    virtual void setRawValue(int8_t val) = 0;
    
private:
    std::string mName;
    int mAddress;
    bool mSet;
    ValueType mValue;
};