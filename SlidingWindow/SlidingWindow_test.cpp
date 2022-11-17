//
// Created by mbroughton on 11/11/22.
//

#include <gtest/gtest.h>
#include "include/SlidingWindow.h"
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
    auto *d = new std::deque<unsigned int> {1, 2, 3, 4};
    //sw -> move(0);
    //sw -> getSlidingWindow();
    //ASSERT_TRUE(sw -> getSlidingWindow() == d);
    delete d;
    d = nullptr;
}