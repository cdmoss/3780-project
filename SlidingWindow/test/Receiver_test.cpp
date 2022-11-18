#include "../include/Receiver.h"
#include <gtest/gtest.h>

class ReceiverTest : public testing::Test {
protected:
  Receiver *r;

  void SetUp() override {
    r = new Receiver(); // create a new class before each test to start fresh
  }

  void TearDown() override {
    delete r;
    r = nullptr;
  }
};

TEST_F(ReceiverTest, receive) {}