/*
  ==============================================================================

    IMemory.h
    Created: 30 Jul 2020 7:30:19pm
    Author:  Stefan Titus

  ==============================================================================
*/

#pragma once

#include <stdint.h>
#include <stdexcept>
#include <string>

// A 7-bit byte. -1 represents undefined.
// Any negative number is interpreted as undefined, but -1 is canonical.
using Byt = int8_t;

using NativeAddr = int;

struct SevenAddr
{
    Byt high;
    Byt mid;
    Byt low;
    
    SevenAddr(Byt high, Byt mid, Byt low)
    : high(high), mid(mid), low(low)
    {
        if (high < 0 || mid < 0 || low < 0)
            throw std::runtime_error("Address component invalid: " + std::to_string(high) + " " + std::to_string(mid) + " " + std::to_string(low));
    }
    
    SevenAddr(NativeAddr addr)
    : high((addr >> 14) & 0x7f), mid((addr >> 7) & 0x7f), low(addr & 0x7f)
    {
        if (addr >= 1 << 21) throw std::runtime_error("Address too large: " + std::to_string(addr));
    }
    
    NativeAddr toNative() const
    {
        return (high * 128 + mid) * 128 + low;
    }
};

class IMemory
{
public:
    virtual ~IMemory() = default;
    
    virtual Byt read(NativeAddr addr) const = 0;
    virtual void write(NativeAddr addr, Byt val) = 0;
    virtual bool isSet(NativeAddr addr) const = 0;
};