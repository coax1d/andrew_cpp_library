#include <iostream>
#include "gtest/gtest.h"
#include "Watchdog.hpp"

//TODO: Finish testing currently does not compile with this test

static int worker1(Watchdog &dog) {

    // pets the dog 6 times before finishing
    std::thread::id worker_id = std::this_thread::get_id();
    int pet_counter = 0;
    int i = 6;
    while(1) {

        if (--i > 0) {
            if (dog.pet(worker_id)) {
                pet_counter++;
            }
        }
        else {
            dog.complete(worker_id);
        }
    }
    return pet_counter;
}

class WatchdogTest : public ::testing::Test {
    protected:

        // void Setup() override {


        // }

        // void TearDown() override {

        // }

        Watchdog dog1_;
        Watchdog dog2_;
        int pet_counter_ = 0;

};

TEST_F(WatchdogTest, TestPetDogSixTimes) {
    pet_counter_ = worker1(dog1_);
    EXPECT_EQ(pet_counter_, 6);
}

int main(void) {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}