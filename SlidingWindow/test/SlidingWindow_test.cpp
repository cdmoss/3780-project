//
// Created by mbroughton on 11/11/22.
//

#include <gtest/gtest.h>
#include "../include/SlidingWindow.h"
#include <deque>

class SlidingWindowTest : public testing::Test {
protected:
    SlidingWindow * sw;

    void SetUp() override {
        sw = new SlidingWindow();  // create a new class before each test to start fresh
    }

    void TearDown() override {
        delete sw;
        sw = nullptr;
    }
};

TEST_F(SlidingWindowTest, move) {
    std::deque<unsigned int> d = {2, 3, 4, 5};
    sw -> move(1);
    ASSERT_EQ(*(sw -> getSlidingWindow()), d);

    d = {6, 7, 0, 1};
    sw -> move(5);
    ASSERT_EQ(*(sw -> getSlidingWindow()), d);
}