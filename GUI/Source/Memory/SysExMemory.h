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
    // Create a SysExMemory that only includes the values of this memory that differ from the other.
    // It may include memory locations that are set to the same value in both if they are between
    // differing values, to consolidate messages for more efficient transmission.3
    SysExMemory diff(const SysExMemory& other) const;
    
    void readMemory(std::string memContents);
    std::string writeMemory() const;
    
    Byt read(NativeAddr addr) const override;
    void write(NativeAddr addr, Byt val) override;
    bool isSet(NativeAddr addr) const override;
    
private:
    std::map<NativeAddr, Byt> mData;
};