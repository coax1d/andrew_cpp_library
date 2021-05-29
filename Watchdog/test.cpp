#include <iostream>
#include "gtest/gtest.h"
#include "Watchdog.hpp"

//TODO: Add more testing
using namespace std::chrono_literals;

std::mutex m_mutex;
bool is_over_max_workers{false};

static void dummy_worker(Watchdog &dog) {

    std::lock_guard<std::mutex> lock(m_mutex);
    std::thread::id worker_id = std::this_thread::get_id();

    if (!dog.pet(worker_id)) {
        is_over_max_workers = true;
    }
}

static void worker1(Watchdog &dog, int &pet_counter) {

    // pets the dog 6 times before finishing
    std::thread::id worker_id = std::this_thread::get_id();
    int i = 6;
    while(1) {

        if (--i >= 0) {
            if (dog.pet(worker_id)) {
                pet_counter++;
            }
        }
        else {
            dog.complete(worker_id);
            break;
        }

        std::this_thread::sleep_for(10ms);
    }
}

class WatchdogTest : public ::testing::Test {
    protected:

        void SetUp() override {


        }

        Watchdog dog1_;
        Watchdog dog2_;
        std::thread w1_;
        std::thread w2_;
        int pet_counter_{0};
};

TEST_F(WatchdogTest, TestPetDogSixTimes) {
    w1_ = std::thread(worker1, std::ref(dog1_), std::ref(pet_counter_));
    w1_.join();
    EXPECT_EQ(pet_counter_, 6);
}

TEST_F(WatchdogTest, AddingWorkerWhenFull) {

    std::vector<std::thread> threads;

    for (int i = 0; i < DEFAULT_MAX_WORKERS + 1; ++i) {
        threads.push_back(std::thread(dummy_worker, std::ref(dog2_)));
        std::this_thread::sleep_for(50ms);
    }

    EXPECT_EQ(is_over_max_workers, true);
}

// TEST_F(WatchdogTest, WorkerTimeoutHasBarkedTrue)
// Test that dog barks when a worker goes over the deadline

int main(void) {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}