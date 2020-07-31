/*
  ==============================================================================

    SysExMemory.cpp
    Created: 28 Jul 2020 6:04:01pm
    Author:  Stefan Titus

  ==============================================================================
*/

#include "SysExMemory.h"

#include <memory>

const static int8_t START_SYSEX = 0xf0;
const static int8_t END_SYSEX = 0xf7;
const static int8_t ROLAND_ID = 0x41;
const static int8_t MT100_DEV_ID = 0x10;
const static int8_t MT100_MODEL_ID = 0x16;
const static int8_t CMD_DATA_SET = 0x12;

void SysExMemory::readSyx(std::vector<int8_t> syxContents)
{
    enum State
    {
        INIT,
        MFG_ID,
        DEV_ID,
        MODEL_ID,
        COMMAND,
        ADDR_MSB,
        ADDR_MB,
        ADDR_LSB,
        DATA,
        UNRECOGNIZED
    };
    
    std::map<NativeAddr, Byt> memory;
    
    State state = INIT;
    NativeAddr address = 0;
    NativeAddr pendingAddress = -1;
    Byt pendingData = -1;
    int sum = 0;
    
    
    for (auto b : syxContents)
    {
        switch(state)
        {
            case INIT:
                if (b == START_SYSEX)
                {
                    state = MFG_ID;
                }
                continue;
            case MFG_ID:
                if (b == ROLAND_ID)
                {
                    state = DEV_ID;
                }
                else
                {
                    state = INIT;
                }
                continue;
            case DEV_ID:
                if (b == MT100_DEV_ID)
                {
                    state = MODEL_ID;
                }
                else
                {
                    state = INIT;
                }
                continue;
            case MODEL_ID:
                if (b == MT100_MODEL_ID)
                {
                    state = COMMAND;
                }
                else
                {
                    state = INIT;
                }
                continue;
            case COMMAND:
                if (b == CMD_DATA_SET)
                {
                    state = ADDR_MSB;
                }
                else
                {
                    // TODO: warn
                    state = UNRECOGNIZED;
                }
                continue;
            case ADDR_MSB:
                state = ADDR_MB;
                address = (int)b * 128 * 128;
                sum += b;
                continue;
            case ADDR_MB:
                state = ADDR_LSB;
                address += (int)b * 128;
                sum += b;
                continue;
            case ADDR_LSB:
                state = DATA;
                address += b;
                sum += b;
                continue;
            case DATA:
                
                if (b == END_SYSEX)
                {
                    state = INIT;
                    
                    pendingAddress = -1;
                    pendingData = -1;
                    
                    if (sum & 0x7f)
                    {
                        // TODO: warn
                    }
                }
                else
                {
                    if (pendingAddress != -1)
                    {
                        memory[pendingAddress] = pendingData;
                        pendingAddress = -1;
                        pendingData = -1;
                    }
                    
                    if (memory.count(address))
                    {
                        // TODO: warn
                    }
                    
                    pendingAddress = address;
                    pendingData = b;
                    
                    address++;
                    sum += b;
                }
                
                continue;
            case UNRECOGNIZED:
            default:
                if (b == END_SYSEX)
                {
                    state = INIT;
                }
                continue;
        }
    }
    
    for (auto pair : memory)
    {
        NativeAddr addr = pair.first;
        Byt data = pair.second;
        
        mData[addr] = data;
    }
}


std::vector<int8_t> SysExMemory::writeSyx() const
{
    std::vector<int8_t> result;
    
    using WriteData = std::vector<int8_t>;
    using Write = std::pair<SevenAddr, WriteData>;
    using WriteList = std::vector<Write>;
    
    WriteList writes;
    
    std::unique_ptr<Write> pendingWrite = nullptr;
    
    const SevenAddr maxAddr{0x20, 0x01, 0x00};
    
    for (NativeAddr i = 0; i < maxAddr.toNative(); ++i)
    {
        // If an address is skipped, that's the end of the write
        if (mData.count(i) == 0)
        {
            if (pendingWrite)
            {
                writes.emplace_back(*pendingWrite);
                pendingWrite = nullptr;
            }
            continue;
        }
        
        if (!pendingWrite)
        {
            pendingWrite = std::unique_ptr<Write>(new Write(SevenAddr(i), {}));
        }
        
        pendingWrite->second.emplace_back(mData.at(i));
        
        if (pendingWrite->second.size() == 256)
        {
            writes.emplace_back(*pendingWrite);
            pendingWrite = nullptr;
        }
    }
    
    int sum = 0;
    
    for (auto write : writes)
    {
        SevenAddr address = write.first;
        WriteData data = write.second;
        
        // Header
        result.emplace_back(START_SYSEX);
        result.emplace_back(ROLAND_ID);
        result.emplace_back(MT100_DEV_ID);
        result.emplace_back(MT100_MODEL_ID);
        result.emplace_back(CMD_DATA_SET);
        
        // Address
        result.emplace_back(address.high);
        result.emplace_back(address.mid);
        result.emplace_back(address.low);
        sum = address.high;
        sum += address.mid;
        sum += address.low;
        
        // Data
        for (auto byte : data)
        {
            result.emplace_back(byte);
            sum += byte;
        }
        
        // Checksum
        result.emplace_back(0x80 - (sum & 0x7f));
        
        // End SYSEX
        result.emplace_back(END_SYSEX);
    }
    
    return result;
}

Byt SysExMemory::at(NativeAddr addr) const
{
    if (mData.count(addr))
        return mData.at(addr);
    return -1;
}

void SysExMemory::write(NativeAddr addr, Byt val)
{
    mData[addr] = val;
}

bool SysExMemory::set(NativeAddr addr) const
{
    return mData.count(addr);
}
