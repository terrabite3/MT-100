#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Property/FloatProperty.h"
#include "Memory_mock.h"

using namespace testing;

TEST(FloatProperty_test, simple)
{
    FloatProperty dut("dut", 123, 0, 127, 0, 1);

    EXPECT_EQ(dut.name(), "dut");
    EXPECT_EQ(dut.address(), 123);

    EXPECT_EQ(dut.getMin(), 0);
    EXPECT_EQ(dut.getMax(), 1);

    EXPECT_FALSE(dut.isSet());

    dut.setValue(0);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 0);

    dut.setValue(1);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);

    EXPECT_ANY_THROW(dut.setValue(2));
    EXPECT_ANY_THROW(dut.setValue(-1));

    dut.reset();
    EXPECT_FALSE(dut.isSet());
}

TEST(FloatProperty_test, simple_json)
{
    FloatProperty dut("dut", 123, 0, 127, 0, 1);

    nlohmann::json json;
    json["dut"] = 0.5;

    dut.readJson(json);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 0.5);

    nlohmann::json jOut;

    dut.writeJson(jOut);
    EXPECT_EQ(jOut, json);
}

TEST(FloatProperty_test, simple_memory)
{
    FloatProperty dut("dut", 123, 0, 127, 0, 1);

    Memory_mock mem;
    EXPECT_CALL(mem, isSet(123))
        .WillOnce(Return(true));
    EXPECT_CALL(mem, read(123))
        .WillOnce(Return(63));
    EXPECT_CALL(mem, write(123, 63));
    
    dut.readMemory(mem);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 63.0f / 127);

    dut.writeMemory(mem);
}
