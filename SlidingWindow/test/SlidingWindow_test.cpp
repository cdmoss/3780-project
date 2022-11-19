//
// Created by mbroughton on 11/11/22.
//

#include <gtest/gtest.h>
#include "../include/SlidingWindow.h"
#include <deque>
#include <vector>

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
    sw -> move(1);
    sw->printSlidingWindow();
    std::vector<unsigned> shouldBe = {2, 3, 4, 5};
    ASSERT_TRUE(sw->windowMatchesSet(shouldBe));

    shouldBe.clear();
    shouldBe = {6, 7, 0, 1};
    sw->move(5);   
    ASSERT_TRUE(sw->windowMatchesSet(shouldBe));


}