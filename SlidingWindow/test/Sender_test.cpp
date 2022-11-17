#include <gtest/gtest.h>
#include "../include/Sender.h"

class SenderTest : public testing::Test {
protected:
    Sender *r;

    void SetUp() override {
        r = new Sender();  // create a new class before each test to start fresh
    }

    void TearDown() override {
        delete r;
        r = nullptr;
    }
};

TEST_F(SenderTest, Sender) {
}