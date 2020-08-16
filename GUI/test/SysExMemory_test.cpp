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

TEST_F(SysExMemory_tf, diff)
{
    SysExMemory other;

    // Neither is set at address 0
    // This is set at address 1, other is not
    mDut.write(1, 1);
    // This is not set at address 2, other is
    other.write(2, 2);
    // This is set at address 3, other has same value
    mDut.write(3, 3);
    other.write(3, 3);
    // This is set at address 4, other has different value
    mDut.write(4, 4);
    other.write(4, 0);

    SysExMemory diff = mDut.diff(other);

    // Diff is not set at address 0
    EXPECT_FALSE(diff.isSet(0));
    // Diff has value at address 1
    EXPECT_TRUE(diff.isSet(1));
    EXPECT_EQ(diff.read(1), 1);
    // Diff is not set at address 2
    EXPECT_FALSE(diff.isSet(2));
    // Diff is not set at address 3
    EXPECT_FALSE(diff.isSet(3));
    // Diff has our value at address 4
    EXPECT_TRUE(diff.isSet(4));
    EXPECT_EQ(diff.read(4), 4);

    // Apply the update message to other
    std::vector<int8_t> diffMessage = diff.writeSyx();
    EXPECT_FALSE(diffMessage.empty());

    other.readSyx(diffMessage);

    // We don't expect other to be equal to this because unset values in this don't clear other.

    // Still not set at address 0
    EXPECT_FALSE(other.isSet(0));
    // Now set at address 1
    EXPECT_TRUE(other.isSet(1));
    EXPECT_EQ(other.read(1), 1);
    // Still have original value at address 2
    EXPECT_TRUE(other.isSet(2));
    EXPECT_EQ(other.read(2), 2);
    // Still have original value at address 3
    EXPECT_TRUE(other.isSet(3));
    EXPECT_EQ(other.read(3), 3);
    // Now have new value at address 4
    EXPECT_TRUE(other.isSet(4));
    EXPECT_EQ(other.read(4), 4);

    // But we do expect the diff to be empty.
    SysExMemory diffAfter = mDut.diff(other);
    EXPECT_FALSE(diffAfter.isSet(0));
    EXPECT_FALSE(diffAfter.isSet(1));
    EXPECT_FALSE(diffAfter.isSet(2));
    EXPECT_FALSE(diffAfter.isSet(3));
    EXPECT_FALSE(diffAfter.isSet(4));

    EXPECT_TRUE(diffAfter.writeSyx().empty());
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