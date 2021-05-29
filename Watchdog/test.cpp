#include <iostream>
#include "gtest/gtest.h"
#include "Watchdog.hpp"

using namespace std::chrono_literals;

class WatchdogTest : public ::testing::Test {
    protected:

        void dummy_worker1(Watchdog &dog) {

            std::thread::id worker_id = std::this_thread::get_id();

            int counter = 6;
            while(1) {

                if (counter-- > 0) {
                    if (dog.pet(worker_id)) {
                        pet_counter_++;
                    }
                }
                else {
                    dog.complete(worker_id);
                    break;
                }

                std::this_thread::sleep_for(10ms);
            }
        }

        void dummy_worker2(Watchdog &dog) {

            std::thread::id worker_id = std::this_thread::get_id();

            const size_t timeout = 7; // Seconds

            int counter_down = 1;
            size_t counter_up = 0;

            while(1) {

                if (counter_down-- > 0) {
                    if (dog.pet(worker_id)) {
                        pet_counter_++;
                    }
                }

                if (counter_up++ == timeout) {
                    break;
                }

                std::this_thread::sleep_for(1s);
            }
        }

        void dummy_worker3(Watchdog &dog) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::thread::id worker_id = std::this_thread::get_id();

            if (!dog.pet(worker_id)) {
                is_over_max_workers_ = true;
            }
        }

        std::mutex mutex_;
        bool is_over_max_workers_{false};

        Watchdog dog1_;
        Watchdog dog2_;

        std::thread w1_;
        std::thread w2_;
        std::vector<std::thread> threads_;

        int pet_counter_{0};
};

TEST_F(WatchdogTest, TestPetDogSixTimes) {
    w1_ = std::thread(
        [this](Watchdog &dog) { dummy_worker1(dog); },
        std::ref(dog1_));
    w1_.join();
    EXPECT_EQ(pet_counter_, 6);
}

TEST_F(WatchdogTest, WorkerTimeoutHasBarkedTrue) {
    w1_ = std::thread(
        [this](Watchdog &dog) { dummy_worker2(dog); },
        std::ref(dog1_));
    w1_.join();
    EXPECT_EQ(dog1_.get_has_barked(), true);
}

TEST_F(WatchdogTest, AddingWorkerWhenFull) {

    for (int i = 0; i < DEFAULT_MAX_WORKERS + 1; ++i) {
        threads_.push_back(
            std::thread(
            [this](Watchdog &dog) { dummy_worker3(dog); },
            std::ref(dog2_)));
    }

    std::for_each(threads_.begin(), threads_.end(),
        [](std::thread &t){ t.join(); });

    EXPECT_EQ(is_over_max_workers_, true);
}

int main(void) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}