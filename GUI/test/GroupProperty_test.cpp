#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Property/IntProperty.h"
#include "Property/GroupProperty.h"
#include "Memory_mock.h"

using namespace testing;

class SampleGroupProperty : public GroupProperty
{
public:
    SampleGroupProperty(int address)
    : GroupProperty("sample", address)
    , child1("child1", address + 0)
    , child2("child2", address + 1)
    {}

    std::vector<const IProperty*> getChildren() const override
    {
        return { &child1, &child2 };
    }

    std::vector<IProperty*> getChildren() override
    {
        return { &child1, &child2 };
    }

    IntProperty child1;
    IntProperty child2;
};

TEST(GroupProperty_test, simple)
{
    SampleGroupProperty dut(10);

    EXPECT_EQ(dut.name(), "sample");
    EXPECT_EQ(dut.address(), 10);

    EXPECT_FALSE(dut.isSet());

    dut.child1.setValue(1);

    EXPECT_TRUE(dut.isSet());
    
    dut.reset();

    EXPECT_FALSE(dut.isSet());
}

TEST(GroupProperty_test, json)
{
    SampleGroupProperty dut(10);

    nlohmann::json jsonIn = R"(
        {
            "sample": {
                "child1": 5,
                "child2": 7
            }
        }
    )"_json;

    dut.readJson(jsonIn);

    EXPECT_TRUE(dut.isSet());
    EXPECT_TRUE(dut.child1.isSet());
    EXPECT_EQ(dut.child1.value(), 5);
    EXPECT_TRUE(dut.child2.isSet());
    EXPECT_EQ(dut.child2.value(), 7);

    nlohmann::json jsonOut;

    dut.writeJson(jsonOut);

    EXPECT_EQ(jsonIn, jsonOut);
}

TEST(GroupProperty_test, jsonPartial)
{
    SampleGroupProperty dut(10);

    nlohmann::json jsonIn = R"(
        {
            "sample": {
                "child2": 7
            }
        }
    )"_json;

    dut.readJson(jsonIn);

    EXPECT_TRUE(dut.isSet());
    EXPECT_FALSE(dut.child1.isSet());
    EXPECT_TRUE(dut.child2.isSet());
    EXPECT_EQ(dut.child2.value(), 7);

    nlohmann::json jsonOut;

    dut.writeJson(jsonOut);

    EXPECT_EQ(jsonIn, jsonOut);
}

TEST(GroupProperty_test, readMemory)
{
    SampleGroupProperty dut(10);

    Memory_mock mem;
    EXPECT_CALL(mem, set(10))
        .WillOnce(Return(true));
    EXPECT_CALL(mem, at(10))
        .WillOnce(Return(5));
    EXPECT_CALL(mem, set(11))
        .WillOnce(Return(true));
    EXPECT_CALL(mem, at(11))
        .WillOnce(Return(7));

    dut.readMemory(mem);

    EXPECT_TRUE(dut.isSet());
    EXPECT_TRUE(dut.child1.isSet());
    EXPECT_EQ(dut.child1.value(), 5);
    EXPECT_TRUE(dut.child2.isSet());
    EXPECT_EQ(dut.child2.value(), 7);
}

TEST(GroupProperty_test, writeMemory)
{
    SampleGroupProperty dut(10);

    dut.child1.setValue(5);
    dut.child2.setValue(7);

    Memory_mock mem;
    EXPECT_CALL(mem, write(10, 5));
    EXPECT_CALL(mem, write(11, 7));

    dut.writeMemory(mem);
}
