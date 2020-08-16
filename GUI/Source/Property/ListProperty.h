/*
  ==============================================================================

    ListProperty.h
    Created: 15 Aug 2020 4:20:27pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "GroupProperty.h"

#include <memory>

template<typename Child>
class ListProperty : public GroupProperty
{
public:
    ListProperty(std::string name, int address, int count, int stride, int startNumber = 1)
    : GroupProperty(name, address)
    {
        for (int i = 0; i < count; ++i)
        {
            std::string number = std::to_string(i + startNumber);
            int childAddr = address + i * stride;
            
            children.emplace_back(std::make_unique<Child>(number, childAddr));
        }
        
        registerWithChildren();
    }
    
    std::vector<std::unique_ptr<Child>> children;
    
    std::vector<const IProperty*> getChildren() const override
    {
        std::vector<const IProperty*> result;
        
        for (auto& child : children)
        {
            result.emplace_back(child.get());
        }
        
        return result;
    }
    
    std::vector<IProperty*> getChildren() override
    {
        std::vector<IProperty*> result;
        
        for (auto& child : children)
        {
            result.emplace_back(child.get());
        }
        
        return result;
    }
};