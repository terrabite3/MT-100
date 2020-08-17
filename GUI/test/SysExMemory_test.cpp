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
    // Space out the addresses so the gaps aren't filled in

    SysExMemory other;

    // Neither is set at address 0
    // This is set at address 100, other is not
    mDut.write(100, 1);
    // This is not set at address 200, other is
    other.write(200, 2);
    // This is set at address 300, other has same value
    mDut.write(300, 3);
    other.write(300, 3);
    // This is set at address 400, other has different value
    mDut.write(400, 4);
    other.write(400, 0);

    SysExMemory diff = mDut.diff(other);

    // Diff is not set at address 0
    EXPECT_FALSE(diff.isSet(0));
    // Diff has value at address 100
    EXPECT_TRUE(diff.isSet(100));
    EXPECT_EQ(diff.read(100), 1);
    // Diff is not set at address 200
    EXPECT_FALSE(diff.isSet(200));
    // Diff is not set at address 300
    EXPECT_FALSE(diff.isSet(300));
    // Diff has our value at address 400
    EXPECT_TRUE(diff.isSet(400));
    EXPECT_EQ(diff.read(400), 4);

    // Apply the update message to other
    std::vector<int8_t> diffMessage = diff.writeSyx();
    EXPECT_FALSE(diffMessage.empty());

    other.readSyx(diffMessage);

    // We don't expect other to be equal to this because unset values in this don't clear other.

    // Still not set at address 0
    EXPECT_FALSE(other.isSet(0));
    // Now set at address 100
    EXPECT_TRUE(other.isSet(100));
    EXPECT_EQ(other.read(100), 1);
    // Still have original value at address 200
    EXPECT_TRUE(other.isSet(200));
    EXPECT_EQ(other.read(200), 2);
    // Still have original value at address 300
    EXPECT_TRUE(other.isSet(300));
    EXPECT_EQ(other.read(300), 3);
    // Now have new value at address 400
    EXPECT_TRUE(other.isSet(400));
    EXPECT_EQ(other.read(400), 4);

    // But we do expect the diff to be empty.
    SysExMemory diffAfter = mDut.diff(other);
    EXPECT_FALSE(diffAfter.isSet(0));
    EXPECT_FALSE(diffAfter.isSet(100));
    EXPECT_FALSE(diffAfter.isSet(200));
    EXPECT_FALSE(diffAfter.isSet(300));
    EXPECT_FALSE(diffAfter.isSet(400));

    EXPECT_TRUE(diffAfter.writeSyx().empty());
}

// A same value between two differing values is included in the diff
TEST_F(SysExMemory_tf, fillGapSame)
{
    // Set three contiguous values
    mDut.write(0, 0);
    mDut.write(1, 0);
    mDut.write(2, 0);

    // Copy
    SysExMemory other = mDut;

    // Change the first and third
    other.write(0, 1);
    other.write(2, 1);

    SysExMemory diff = mDut.diff(other);

    EXPECT_TRUE(diff.isSet(0));
    // The value in between is set in the diff even though it wasn't different
    EXPECT_TRUE(diff.isSet(1));
    EXPECT_EQ(diff.read(1), 0);
    EXPECT_TRUE(diff.isSet(2));
}

// A gap between two differing values where the source is unset but the destination is set
// is included in the diff
TEST_F(SysExMemory_tf, fillGapDontCare)
{
    // Set two values with a gap
    mDut.write(0, 0);
    // mDut.write(1, 0);
    mDut.write(2, 0);

    // Copy
    SysExMemory other = mDut;

    // Change the first and third
    other.write(0, 1);
    // The destination has a value for the gap
    other.write(1, 1);
    other.write(2, 1);

    SysExMemory diff = mDut.diff(other);

    EXPECT_TRUE(diff.isSet(0));
    // The value in between is set in the diff even though it wasn't set in the source
    EXPECT_TRUE(diff.isSet(1));
    EXPECT_EQ(diff.read(1), 1);
    EXPECT_TRUE(diff.isSet(2));
}

TEST_F(SysExMemory_tf, fillGap_noUnset)
{
    // Set two values with a gap in between
    mDut.write(0, 0);
    // mDut.write(1, 0);
    mDut.write(2, 0);

    // Copy
    SysExMemory other = mDut;

    // Change the first and third
    other.write(0, 1);
    other.write(2, 1);

    SysExMemory diff = mDut.diff(other);

    EXPECT_TRUE(diff.isSet(0));
    // The value in between is not set because neither have it set
    EXPECT_FALSE(diff.isSet(1));
    EXPECT_TRUE(diff.isSet(2));
}

// Don't include values adjacent to set values
TEST_F(SysExMemory_tf, fillGapSame_noBookend)
{
    // Set five contiguous values
    mDut.write(0, 0);
    mDut.write(1, 0);
    mDut.write(2, 0);
    mDut.write(3, 0);
    mDut.write(4, 0);

    // Copy
    SysExMemory other = mDut;

    // Change the second and fourth
    other.write(1, 1);
    other.write(3, 1);

    SysExMemory diff = mDut.diff(other);

    // The bookend is not included
    EXPECT_FALSE(diff.isSet(0));
    EXPECT_TRUE(diff.isSet(1));
    // The value in between is set in the diff even though it wasn't different
    EXPECT_TRUE(diff.isSet(2));
    EXPECT_EQ(diff.read(2), 0);
    EXPECT_TRUE(diff.isSet(3));
    // The bookend is not included
    EXPECT_FALSE(diff.isSet(4));
}

// Don't include values adjacent to set values
TEST_F(SysExMemory_tf, fillGapDontCare_bookend)
{
    // Set two values with a gap between
    // mDut.write(0, 0);
    mDut.write(1, 0);
    // mDut.write(2, 0);
    mDut.write(3, 0);
    // mDut.write(4, 0);

    // Copy
    SysExMemory other = mDut;

    // The destination has values for the bookends and gap
    other.write(0, 1);
    // Change the second and fourth
    other.write(1, 1);
    other.write(2, 2);
    other.write(3, 3);
    other.write(4, 4);

    SysExMemory diff = mDut.diff(other);

    // The bookend is not included
    EXPECT_FALSE(diff.isSet(0));
    EXPECT_TRUE(diff.isSet(1));
    // The value in between is set in the diff even though it wasn't different
    EXPECT_TRUE(diff.isSet(2));
    EXPECT_EQ(diff.read(2), 2);
    EXPECT_TRUE(diff.isSet(3));
    // The bookend is not included
    EXPECT_FALSE(diff.isSet(4));
}

TEST_F(SysExMemory_tf, fillGapSame_iterate)
{
    const int maxGap = 10;

    for (int gapSize = 0; gapSize < maxGap + 5; ++gapSize)
    {
        std::cout << "gapSize:\t" << gapSize << "\n";

        SysExMemory left;
        // Fill the gap and the bookends with a value
        for (int i = 0; i < gapSize + 2; ++i)
        {
            left.write(i, 0);
        }

        // Copy the current state
        SysExMemory right = left;

        // Change the value at the bookends
        left.write(0, 1);
        left.write(gapSize + 1, 1);

        SysExMemory diff = left.diff(right);
        // The bookends are in the diff
        EXPECT_TRUE(diff.isSet(0));
        EXPECT_TRUE(diff.isSet(gapSize+1));

        for (int i = 1; i < gapSize + 1; ++i)
        {
            // Whether the items in between are set depends on the size of the gap
            if (gapSize <= maxGap)
                EXPECT_TRUE(diff.isSet(i)) << i;
            else
                EXPECT_FALSE(diff.isSet(i)) << i;
        }
    }
}

TEST_F(SysExMemory_tf, fillGapDontCare_iterate)
{
    const int maxGap = 10;

    for (int gapSize = 0; gapSize < maxGap + 5; ++gapSize)
    {
        SysExMemory left;
        // Fill the bookends with a value
        left.write(0, 0);
        left.write(gapSize + 1, 0);

        // Copy the current state
        SysExMemory right = left;

        // Change the value at the bookends
        left.write(0, 1);
        left.write(gapSize + 1, 1);

        // Set everything in the destination
        for (int i = 0; i < gapSize + 2; ++i)
        {
            right.write(i, 0);
        }

        SysExMemory diff = left.diff(right);
        // The bookends are in the diff
        EXPECT_TRUE(diff.isSet(0));
        EXPECT_TRUE(diff.isSet(gapSize+1));

        for (int i = 1; i < gapSize + 1; ++i)
        {
            // Whether the items in between are set depends on the size of the gap
            if (gapSize <= maxGap)
                EXPECT_TRUE(diff.isSet(i)) << i;
            else
                EXPECT_FALSE(diff.isSet(i)) << i;
        }
    }
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