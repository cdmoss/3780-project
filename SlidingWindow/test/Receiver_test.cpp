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

TEST_F(ReceiverTest, receive_ack_value) {
  Receiver *r = new Receiver();
  std::pair<unsigned int, std::set<unsigned int>*> p;

  p = r->receive(0);
  ASSERT_EQ(p.first, 0);

  p = r->receive(2);
  ASSERT_EQ(p.first, 0);

  p = r->receive(1);
  ASSERT_EQ(p.first, 2);
}

TEST_F(ReceiverTest, receive_wrap_around) {

  std::pair<unsigned int, std::set<unsigned int>*> p;

  p = r->receive(0);
  ASSERT_EQ(p.first, 0);

  p = r->receive(1);
  ASSERT_EQ(p.first, 1);

  p = r->receive(2);
  ASSERT_EQ(p.first, 2);

  p = r->receive(3);
  ASSERT_EQ(p.first, 3);

  p = r->receive(4);
  ASSERT_EQ(p.first, 4);

  p = r->receive(5);
  ASSERT_EQ(p.first, 5);

  p = r->receive(6);
  ASSERT_EQ(p.first, 6);

  p = r->receive(0);
  ASSERT_EQ(p.first, 0);

}
