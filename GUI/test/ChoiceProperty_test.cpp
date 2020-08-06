#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Property/ChoiceProperty.h"
#include "Memory_mock.h"

using namespace testing;

TEST(ChoiceProperty_test, simple)
{
    ChoiceProperty dut("dut", 123, {"foo", "bar", "baz"});

    EXPECT_EQ(dut.name(), "dut");
    EXPECT_EQ(dut.address(), 123);

    std::vector<std::string> choices = {"foo", "bar", "baz"};
    EXPECT_EQ(dut.getChoices(), choices);
    EXPECT_EQ(dut.getChoices().size(), 3);

    EXPECT_FALSE(dut.isSet());
    EXPECT_EQ(dut.value(), "");

    dut.setValue("foo");

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), "foo");

    dut.setValue("bar");
    EXPECT_EQ(dut.value(), "bar");

    dut.setValue("baz");
    EXPECT_EQ(dut.value(), "baz");

    EXPECT_ANY_THROW(dut.setValue("fizz"));
    EXPECT_ANY_THROW(dut.setValue(""));

    dut.reset();
    EXPECT_FALSE(dut.isSet());
    EXPECT_EQ(dut.value(), "");
}

TEST(ChoiceProperty_test, json)
{
    ChoiceProperty dut("dut", 123, {"foo", "bar", "baz"});

    nlohmann::json json;
    json["dut"] = "bar";

    dut.readJson(json);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), "bar");

    nlohmann::json jOut;

    dut.writeJson(jOut);
    EXPECT_EQ(jOut, json);

    json["dut"] = "fizz";
    EXPECT_ANY_THROW(dut.readJson(json));
}

TEST(ChoiceProperty_test, json_throw)
{
    ChoiceProperty dut("dut", 123, {"foo", "bar", "baz"});

    nlohmann::json json;
    json["dut"] = "fizz";
    EXPECT_ANY_THROW(dut.readJson(json));

    EXPECT_FALSE(dut.isSet());
}

TEST(ChoiceProperty_test, memory)
{
    ChoiceProperty dut("dut", 123, {"foo", "bar", "baz"});

    Memory_mock mem;
    EXPECT_CALL(mem, isSet(123))
        .WillOnce(Return(true));
    EXPECT_CALL(mem, read(123))
        .WillOnce(Return(1));
    EXPECT_CALL(mem, write(123, 1));
    
    dut.readMemory(mem);

    EXPECT_TRUE(dut.isSet());
    EXPECT_EQ(dut.value(), "bar");

    dut.writeMemory(mem);
}

TEST(ChoiceProperty_test, memory_throw)
{
    ChoiceProperty dut("dut", 123, {"foo", "bar", "baz"});

    Memory_mock mem;
    EXPECT_CALL(mem, isSet(123))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mem, read(123))
        .WillOnce(Return(3))
        .WillOnce(Return(-1));
    
    EXPECT_ANY_THROW(dut.readMemory(mem));
    EXPECT_ANY_THROW(dut.readMemory(mem));

    EXPECT_FALSE(dut.isSet());
}
