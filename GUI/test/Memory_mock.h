#pragma once

#include "Memory/IMemory.h"

#include <gmock/gmock.h>

class Memory_mock : public IMemory
{
public:
    MOCK_METHOD(Byt, at, (NativeAddr addr), (const, override));
    MOCK_METHOD(void, write, (NativeAddr addr, Byt val), (override));
    MOCK_METHOD(bool, set, (NativeAddr addr), (const, override));
};