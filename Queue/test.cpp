#include <iostream>
#include <string>
#include "Queue.hpp"
#include "gtest/gtest.h"

class QueueTest : public ::testing::Test {
    protected:

    void SetUp() override {
        // int queue setup
        q_int_.put_queue(1);
        q_int_.put_queue(2);

        // std::string queue setup
        q_string_.put_queue("Andrew");
        q_string_.put_queue("Michael");

        // size_t queue setup
        q_size_t_.put_queue((size_t)10);
        q_size_t_.put_queue((size_t)11);

        // double queue setup
        q_double_t_.put_queue(4.3);
        q_double_t_.put_queue(4.8);

        // void ptr queue setup
        *b = 2;
        q_int_ptr_.put_queue(&a);
        q_int_ptr_.put_queue(b);

    }

    void TearDown() override {
        delete b;
    }

    Queue<int> q_int_;
    Queue<int> q_int_2_;
    Queue<std::string> q_string_;
    Queue<size_t> q_size_t_;
    Queue<double> q_double_t_;
    Queue<int*> q_int_ptr_;

    // ptr variables
    int a = 1;
    int *b = new int;
};

TEST_F(QueueTest, QueueIntWorks) {
    EXPECT_EQ(q_int_.get_len(), 2);
    auto a = q_int_.get_queue();
    EXPECT_EQ(a, 1);
}

TEST_F(QueueTest, QueueStringWorks) {
    std::string andrew("Andrew");
    auto a = q_string_.get_queue();
    EXPECT_EQ(andrew, a);
    EXPECT_EQ(q_string_.get_len(), 1);
}

TEST_F(QueueTest, QueueSizetWorks) {
    auto a = q_size_t_.get_queue();
    EXPECT_EQ(a, 10);
    EXPECT_EQ(q_size_t_.get_len(), 1);
}

TEST_F(QueueTest, QueueDoubleWorks) {
    double a = q_double_t_.get_queue();
    EXPECT_EQ(a, 4.3);
    EXPECT_EQ(q_double_t_.get_len(), 1);
}

TEST_F(QueueTest, QueuePtrWorks) {
    auto test_ptr = q_int_ptr_.get_queue();
    EXPECT_EQ(*test_ptr, 1);
    EXPECT_EQ(q_int_ptr_.get_len(), 1);
}

int main(void) {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();;
}