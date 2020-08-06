/*
  ==============================================================================

    IPropertyListener.h
    Created: 5 Aug 2020 9:03:58pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include <string>

class IPropertyListener
{
public:
    virtual ~IPropertyListener() = default;
    
    virtual void notify(std::string name) = 0;
};