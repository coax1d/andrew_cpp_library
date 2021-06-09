#include <iostream>
#include "UdpSocket.hpp"
#include "gtest/gtest.h"

class SocketTest : public ::testing::Test {
    protected:
        void SetUp() override {}
        void TearDown() override {}
};

int main(void) {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
