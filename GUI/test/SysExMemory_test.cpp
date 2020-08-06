#include <gtest/gtest.h>

#include "Memory/SysExMemory.h"

using namespace testing;

class SysExMemory_tf : public Test
{
public:
    SysExMemory mDut;
};

TEST_F(SysExMemory_tf, first)
{
    std::vector<int8_t> hello
    {
        (int8_t)0xf0, 0x41, 0x10, 0x16, 0x12, 0x10, 0x00, 0x16, 0x64, 0x76, (int8_t)0xf7
    };
    
    mDut.readSyx(hello);
    
    SevenAddr addr(0x10, 0x00, 0x16);
    
    EXPECT_TRUE(mDut.isSet(addr.toNative()));
    EXPECT_EQ(mDut.read(addr.toNative()), 100);
    
    auto output = mDut.writeSyx();
    EXPECT_EQ(hello, output);
}

TEST(SevenAddr, foo)
{
    using Sev = SevenAddr;
    
    EXPECT_EQ(Sev(0, 0, 0).toNative(), 0);
    EXPECT_EQ(Sev(0, 0, 1).toNative(), 1);
    EXPECT_EQ(Sev(0, 0, 0x7f).toNative(), 127);
    
    EXPECT_ANY_THROW(Sev(0, 0, (int8_t)0x80));
    EXPECT_ANY_THROW(Sev(0, 0, (int8_t)0xff));
    
    EXPECT_EQ(Sev(0, 1, 0).toNative(), 128);
    EXPECT_EQ(Sev(0, 1, 1).toNative(), 129);
    EXPECT_EQ(Sev(0, 1, 0x7f).toNative(), 255);
    EXPECT_EQ(Sev(0, 2, 0).toNative(), 256);
    EXPECT_EQ(Sev(0, 0x7f, 0x7f).toNative(), 16383);
    
    EXPECT_ANY_THROW(Sev(0, (int8_t)0x80, 0));
    EXPECT_ANY_THROW(Sev(0, (int8_t)0xff, 0));
    
    EXPECT_EQ(Sev(1, 0, 0).toNative(), 16384);
    EXPECT_EQ(Sev(0x7f, 0x7f, 0x7f).toNative(), 2097151);

    EXPECT_ANY_THROW(Sev((int8_t)0x80, 0, 0));
}