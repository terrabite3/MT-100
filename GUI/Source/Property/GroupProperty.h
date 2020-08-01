/*
  ==============================================================================

    GroupProperty.h
    Created: 31 Jul 2020 7:30:28pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "IProperty.h"

class GroupProperty : public IProperty
{
public:
    GroupProperty(std::string name, int address)
    : IProperty(name, address)
    {}
    
    bool isSet() const override
    {
        for (auto child : getChildren())
        {
            if (child->isSet())
                return true;
        }
        return false;
    }
    
    void reset() override
    {
        for (auto child : getChildren())
        {
            child->reset();
        }
    }
    
    void readJson(nlohmann::json jParent) override
    {
        if (jParent.count(name()))
        {
            auto& jSelf = jParent[name()];
            for (auto child : getChildren())
            {
                child->readJson(jSelf);
            }
        }
    }
    
    void writeJson(nlohmann::json& jParent) const override
    {
        if (isSet())
        {
            if (! jParent.count(name()))
                jParent[name()] = nlohmann::json::object();
            
            auto& jSelf = jParent[name()];
            for (auto child : getChildren())
            {
                child->writeJson(jSelf);
            }
        }
    }
    
    void readMemory(const IMemory& memory) override
    {
        for (auto child : getChildren())
        {
            child->readMemory(memory);
        }
    }
    
    void writeMemory(IMemory& memory) const override
    {
        for (auto child : getChildren())
        {
            child->writeMemory(memory);
        }
    }
    
    
    virtual std::vector<const IProperty*> getChildren() const = 0;
    virtual std::vector<IProperty*> getChildren() = 0;
    
    
private:
    
    int8_t getRawValue() const override
    {
        return 0;
    }
    
    void setRawValue(int8_t) override
    {}
};