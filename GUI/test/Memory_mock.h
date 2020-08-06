#pragma once

#include "Memory/IMemory.h"

#include <gmock/gmock.h>

class Memory_mock : public IMemory
{
public:
    MOCK_METHOD(Byt, read, (NativeAddr addr), (const, override));
    MOCK_METHOD(void, write, (NativeAddr addr, Byt val), (override));
    MOCK_METHOD(bool, isSet, (NativeAddr addr), (const, override));
};