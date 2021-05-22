#include <iostream>
#include <fstream>
#include "Foo.hpp"
#include "gtest/gtest.h"

class FooSerializerTest : public ::testing::Test {
    protected:

        void SetUp() override {

            output1.open("serialized_object1.bin", std::ios::binary);
            output2.open("serialized_object2.bin", std::ios::binary);
            output3.open("serialized_object3.bin", std::ios::binary);

            f1.serialize(output1);
            f2.serialize(output2);
            f3.serialize(output3);

            output1.close();
            output2.close();
            output3.close();

            input1.open("serialized_object1.bin", std::ios::binary);
            input2.open("serialized_object2.bin", std::ios::binary);
            input3.open("serialized_object3.bin", std::ios::binary);
        }

        void TearDown() override {

            input1.close();
            input2.close();
            input3.close();
        }

        Foo f1;
        Foo f2{99.7,42, {3,2,1}};
        Foo f3{-99.7, -42, {-3,-2,-1}};

        std::ofstream output1;
        std::ifstream input1;

        std::ofstream output2;
        std::ifstream input2;

        std::ofstream output3;
        std::ifstream input3;
};

TEST_F(FooSerializerTest, DefaultInitialization) {

    EXPECT_EQ(f1.get_x(), 1.0);
    EXPECT_EQ(f1.get_y(), 3);

    auto vec = f1.get_z();
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
}

TEST_F(FooSerializerTest, SerializeDefaultNums) {

    Foo tester(input1);
    EXPECT_EQ(tester.get_x(), f1.get_x());
    EXPECT_EQ(tester.get_y(), f1.get_y());
    EXPECT_EQ(tester.get_z(), f1.get_z());
}

TEST_F(FooSerializerTest, SerializePositiveNums) {

    Foo tester(input2);
    EXPECT_EQ(tester.get_x(), f2.get_x());
    EXPECT_EQ(tester.get_y(), f2.get_y());
    EXPECT_EQ(tester.get_z(), f2.get_z());
}

TEST_F(FooSerializerTest, SerializeNegativeNums) {

    Foo tester(input3);
    EXPECT_EQ(tester.get_x(), f3.get_x());
    EXPECT_EQ(tester.get_y(), f3.get_y());
    EXPECT_EQ(tester.get_z(), f3.get_z());
}

TEST_F(FooSerializerTest, Deserialize) {

    Foo tester;
    tester.deserialize(input2);
    EXPECT_EQ(tester.get_x(), f2.get_x());
    EXPECT_EQ(tester.get_y(), f2.get_y());
    EXPECT_EQ(tester.get_z(), f2.get_z());
}

int main(void) {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
