#include "../include/Sender.h"
#include <gtest/gtest.h>

class SenderTest : public testing::Test {
protected:
  Sender *s;

  void SetUp() override {
    s = new Sender(); // create a new class before each test to start fresh
  }

  void TearDown() override {
    delete s;
    s = nullptr;
  }
};

TEST_F(SenderTest, send) {
  ASSERT_EQ(0, s->send());
  ASSERT_EQ(3, s->sendMulti(3));
  ASSERT_EQ(-1, s->send());
  ASSERT_EQ(-1, s->send());
}

TEST_F(SenderTest, receiveAck) {
  ASSERT_EQ(s->receiveAck(0), 0);

  ASSERT_EQ(0, s->send());
  ASSERT_EQ(1, s->send());
  ASSERT_EQ(s->receiveAck(1), 2);

  ASSERT_EQ(5, s->sendMulti(4));
  ASSERT_EQ(s->receiveAck(5), 4);

  ASSERT_EQ(1, s->sendMulti(4));
  ASSERT_EQ(s->receiveAck(1), 4);
}