/*
  ==============================================================================

    TopProperty.h
    Created: 15 Aug 2020 4:13:12pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"
#include "TimbreProperty.h"
#include "SystemProperty.h"
#include "ListProperty.h"

#include "Memory/IMemory.h"

class TopProperty : public GroupProperty
{
public:
    TopProperty() : GroupProperty("", 0)
    , timbreTemp("timbre_temp", SevenAddr(0x04, 0, 0).toNative(), 8, SevenAddr(0, 0x02, 0).toNative())
    , system(SevenAddr(0x10, 0, 0).toNative())
    {
        registerWithChildren();
    }
    
    ListProperty<TimbreProperty> timbreTemp;
    SystemProperty system;
    
    std::vector<const IProperty*> getChildren() const override
    {
        return { &timbreTemp, &system };
    }
    
    std::vector<IProperty*> getChildren() override
    {
        return { &timbreTemp, &system };
    }
    
    void readJson(nlohmann::json jParent) override
    {
        for (auto child : getChildren())
        {
            child->readJson(jParent);
        }
    }
    
    void writeJson(nlohmann::json& jParent) const override
    {
        if (isSet())
        {
            for (auto child : getChildren())
            {
                child->writeJson(jParent);
            }
        }
    }
};
