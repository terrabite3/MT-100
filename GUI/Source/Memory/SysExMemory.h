/*
  ==============================================================================

    SysExMemory.h
    Created: 28 Jul 2020 6:04:01pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include "IMemory.h"

#include <vector>
#include <map>
#include <stdexcept>
#include <string>



class SysExMemory : public IMemory
{
public:
    
    SysExMemory() = default;

    
    void readSyx(std::vector<int8_t> syxContents);
    std::vector<int8_t> writeSyx() const;
    
    void readMemory(std::string memContents);
    std::string writeMemory() const;
    
    Byt at(NativeAddr addr) const override;
    void write(NativeAddr addr, Byt val) override;
    bool set(NativeAddr addr) const override;
    
private:
    std::map<NativeAddr, Byt> mData;
};