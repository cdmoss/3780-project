#include "SimpleHeader.h"
#include "gtest/gtest.h"  // google test framework

// Test class
class HeaderTest : public testing::Test {
protected:
  SimpleHeader * h_;

  void SetUp() override {
    h_ = new SimpleHeader;  // create a new class before each test to start fresh
  }

  void TearDown() override {
    delete h_;
  }
};

// setLength test
TEST_F(HeaderTest, setLength) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[2] = 0x0;
  ptr->header[3] = 0x0;

  h_->setLength(0xffff);
  ASSERT_TRUE(ptr->header[2] == 0xff);
  ASSERT_TRUE(ptr->header[3] == 0xff);

  h_->setLength(0x0000);
  ASSERT_TRUE(ptr->header[2] == 0x0);
  ASSERT_TRUE(ptr->header[3] == 0x0);

  h_->setLength(0xffffff);
  ASSERT_TRUE(ptr->header[2] == 0xff);
  ASSERT_TRUE(ptr->header[3] == 0xff);
}

// getLength test
TEST_F(HeaderTest, getLength) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[2] = 0x0;
  ptr->header[3] = 0x0;

  h_->setLength(0xffff);
  ASSERT_TRUE(h_ -> getLength() == 0xffff);

  h_->setLength(0x0);
  ASSERT_TRUE(h_ -> getLength() == 0x0);

  h_->setLength(0xffffff);
  ASSERT_TRUE(h_ -> getLength() == 0xffff);
}

// setType test
TEST_F(HeaderTest, setType) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[0] = 0x0;

  h_->setType(1);
  ASSERT_TRUE(ptr->header[0] == 0x40);

  h_->setType(2);
  ASSERT_TRUE(ptr->header[0] == 0x80);

  h_->setType(4);
  ASSERT_TRUE(ptr->header[0] == 0x0);

  h_->setType(3);
  ASSERT_TRUE(ptr->header[0] == 0xc0);

  h_->setType(0);
  ASSERT_TRUE(ptr->header[0] == 0x0);
}

// getType test
TEST_F(HeaderTest, getType) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[0] = 0x0;

  h_->setType(1);
  ASSERT_TRUE(h_ -> getType() == 1);

  h_->setType(2);
  ASSERT_TRUE(h_ -> getType() == 2);

  h_->setType(4);
  ASSERT_TRUE(h_ -> getType() == 0);

  h_->setType(3);
  ASSERT_TRUE(h_ -> getType() == 3);

  h_->setType(0);
  ASSERT_TRUE(h_ -> getType() == 0);
}

// setTR test
TEST_F(HeaderTest, setTR) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[0] = 0x0;

  h_->setTR(1);
  ASSERT_TRUE(ptr->header[0] == 0x20);

  h_->setTR(0);
  ASSERT_TRUE(ptr->header[0] == 0x0);

  h_->setTR(1);
  h_->setTR(2);
  ASSERT_TRUE(ptr->header[0] == 0x0);
}

// getTR test
TEST_F(HeaderTest, getTR) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  // initialize the first byte to some value.
  ptr->header[0] = 0x0;

  h_->setTR(1);
  ASSERT_TRUE(h_ -> getTR() == 1);

  h_->setTR(0);
  ASSERT_TRUE(h_ -> getTR() == 0);

  h_->setTR(1);
  h_->setTR(2);
  ASSERT_TRUE(h_ -> getTR() == 0);
}

// setWindow test
TEST_F(HeaderTest, setWindow) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[0] = 0x0;

  h_->setWindow(31);
  ASSERT_TRUE(ptr->header[0] == 0x1f);

  h_->setWindow(32);
  ASSERT_TRUE(ptr->header[0] == 0x0);

  h_->setWindow(15);
  ASSERT_TRUE(ptr->header[0] == 0xf);

  h_->setWindow(0);
  ASSERT_TRUE(ptr->header[0] == 0x0);
}

// getWindow test
TEST_F(HeaderTest, getWindow) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[0] = 0x0;

  h_->setWindow(31);
  ASSERT_TRUE(h_ -> getWindow() == 31);

  h_->setWindow(0);
  ASSERT_TRUE(h_ -> getWindow() == 0);

  h_->setWindow(31);
  h_->setWindow(32);
  ASSERT_TRUE(h_ -> getWindow() == 0);
}

// setSeqNum test
TEST_F(HeaderTest, setSeqNum) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[1] = 0x0;

  h_->setSeqNum(255);
  ASSERT_TRUE(ptr->header[1] == 0xff);

  h_->setSeqNum(256);
  ASSERT_TRUE(ptr->header[1] == 0x0);

  h_->setSeqNum(255);
  h_->setSeqNum(0);
  ASSERT_TRUE(ptr->header[1] == 0x0);
}

// getSeqNum test
TEST_F(HeaderTest, getSeqNum) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[1] = 0x0;

  h_->setSeqNum(255);
  ASSERT_TRUE(h_ -> getSeqNum() == 255);

  h_->setSeqNum(256);
  ASSERT_TRUE(h_ -> getSeqNum() == 0);

  h_->setSeqNum(0);
  ASSERT_TRUE(h_ -> getSeqNum() == 0);
}
