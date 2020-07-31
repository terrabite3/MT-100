#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Property/IntProperty.h"
#include "Memory_mock.h"

using namespace testing;

TEST(IntProperty_test, simple)
{
    IntProperty dut("dut", 123);

    EXPECT_EQ(dut.name(), "dut");
    EXPECT_EQ(dut.address(), 123);

    EXPECT_EQ(dut.getMin(), 0);
    EXPECT_EQ(dut.getMax(), 127);

    EXPECT_FALSE(dut.isSet());

    dut.setValue(1);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);

    dut.setValue(127);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 127);

    EXPECT_ANY_THROW(dut.setValue(128));
    EXPECT_ANY_THROW(dut.setValue(-1));

    dut.reset();
    EXPECT_FALSE(dut.isSet());
}

TEST(IntProperty_test, simple_json)
{
    IntProperty dut("dut", 123);

    nlohmann::json json;
    json["dut"] = 3;

    dut.readJson(json);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 3);

    nlohmann::json jOut;

    dut.writeJson(jOut);
    EXPECT_EQ(jOut, json);
}

TEST(IntProperty_test, simple_memory)
{
    IntProperty dut("dut", 123);

    Memory_mock mem;
    EXPECT_CALL(mem, set(123))
        .WillOnce(Return(true));
    EXPECT_CALL(mem, at(123))
        .WillOnce(Return(3));
    EXPECT_CALL(mem, write(123, 3));
    
    dut.readMemory(mem);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 3);

    dut.writeMemory(mem);
}

TEST(IntProperty_test, max)
{
    IntProperty dut("dut", 123, 10);

    EXPECT_EQ(dut.getMin(), 0);
    EXPECT_EQ(dut.getMax(), 10);

    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.setValue(11));
    EXPECT_ANY_THROW(dut.setValue(-1));

    EXPECT_FALSE(dut.isSet());

    dut.setValue(1);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);

    EXPECT_ANY_THROW(dut.setValue(11));

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);
}

TEST(IntProperty_test, max_json)
{
    IntProperty dut("dut", 123, 10);

    nlohmann::json json;
    json["dut"] = 11;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());

    json["dut"] = -1;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());
}

TEST(IntProperty_test, max_memory)
{
    IntProperty dut("dut", 123, 10);

    Memory_mock mem;
    EXPECT_CALL(mem, set(123))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mem, at(123))
        .WillOnce(Return(11))
        .WillOnce(Return(-1));

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());
}


TEST(IntProperty_test, offset)
{
    // Offset of 1 means it counts from 1 to 128
    IntProperty dut("dut", 123, 127, 1);

    EXPECT_EQ(dut.getMin(), 1);
    EXPECT_EQ(dut.getMax(), 128);

    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.setValue(129));
    EXPECT_ANY_THROW(dut.setValue(0));

    EXPECT_FALSE(dut.isSet());

    dut.setValue(1);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);

    EXPECT_EQ(dut.getRawValue(), 0);

    dut.setRawValue(2);

    EXPECT_EQ(dut.value(), 3);
}

TEST(IntProperty_test, offset_json)
{
    // Offset of 1 means it counts from 1 to 128
    IntProperty dut("dut", 123, 127, 1);

    nlohmann::json json;
    json["dut"] = 3;

    dut.readJson(json);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 3);
    EXPECT_EQ(dut.getRawValue(), 2);

    json["dut"] = 128;

    dut.readJson(json);

    EXPECT_EQ(dut.value(), 128);

    dut.reset();

    json["dut"] = 129;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());

    json["dut"] = 0;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());

    nlohmann::json jOut;
    dut.setValue(5);

    dut.writeJson(jOut);
    EXPECT_EQ(jOut["dut"].get<int>(), 5);
}

TEST(IntProperty_test, offset_memory)
{
    IntProperty dut("dut", 123, 127, 1);

    Memory_mock mem;
    EXPECT_CALL(mem, set(123))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mem, at(123))
        .WillOnce(Return(0))
        .WillOnce(Return(127))
        .WillOnce(Return(128))
        .WillOnce(Return(-1));

    dut.readMemory(mem);
    EXPECT_EQ(dut.value(), 1);

    dut.readMemory(mem);
    EXPECT_EQ(dut.value(), 128);

    dut.reset();

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());
}

TEST(IntProperty_test, max_offset)
{
    // Offset of 1 means it counts from 1 to 128
    IntProperty dut("dut", 123, 10, 1);

    EXPECT_EQ(dut.getMin(), 1);
    EXPECT_EQ(dut.getMax(), 11);

    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.setValue(12));
    EXPECT_ANY_THROW(dut.setValue(0));

    EXPECT_FALSE(dut.isSet());

    dut.setValue(1);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 1);

    EXPECT_EQ(dut.getRawValue(), 0);

    dut.setRawValue(2);

    EXPECT_EQ(dut.value(), 3);
}

TEST(IntProperty_test, max_offset_json)
{
    // Offset of 1 means it counts from 1 to 11
    IntProperty dut("dut", 123, 10, 1);

    nlohmann::json json;
    json["dut"] = 11;

    dut.readJson(json);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), 11);
    EXPECT_EQ(dut.getRawValue(), 10);

    dut.reset();

    json["dut"] = 12;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());

    json["dut"] = 0;

    EXPECT_ANY_THROW(dut.readJson(json));
    EXPECT_FALSE(dut.isSet());

    nlohmann::json jOut;
    dut.setValue(5);

    dut.writeJson(jOut);
    EXPECT_EQ(jOut["dut"].get<int>(), 5);
}

TEST(IntProperty_test, max_offset_memory)
{
    IntProperty dut("dut", 123, 10, 1);

    Memory_mock mem;
    EXPECT_CALL(mem, set(123))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mem, at(123))
        .WillOnce(Return(0))
        .WillOnce(Return(10))
        .WillOnce(Return(11))
        .WillOnce(Return(-1));

    dut.readMemory(mem);
    EXPECT_EQ(dut.value(), 1);

    dut.readMemory(mem);
    EXPECT_EQ(dut.value(), 11);

    dut.reset();

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());

    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_FALSE(dut.isSet());
}