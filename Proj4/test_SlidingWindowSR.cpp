#include <gtest/gtest.h>  // google test framework
#include "include/SlidingWindowSR.h"

using namespace std;

typedef SlidingWindowSR sr;

class SlidingWindowSRTest : public testing::Test {};

TEST_F(SlidingWindowSRTest, baseCons) {
    sr s;
    ASSERT_EQ(s.getWinSize(), 3);
    ASSERT_EQ(s.getMaxSeqNum(), 7);
}

TEST_F(SlidingWindowSRTest, setWinSize) {
    sr s;
    s.setWinSize(4);
    ASSERT_EQ(s.getWinSize(), 4);
    ASSERT_EQ(s.getMaxSeqNum(), 7);
}

TEST_F(SlidingWindowSRTest, setmaxSeqNum) {
    sr s;
    s.setMaxSeqNum(4);
    ASSERT_EQ(s.getMaxSeqNum(), 4);
    ASSERT_EQ(s.getWinSize(), 3);
}

TEST_F(SlidingWindowSRTest, send_0window) {
    sr s(0, 7);
    ASSERT_EQ(s.send(), -1);
}

TEST_F(SlidingWindowSRTest, send_1seq) {
    sr s;
    ASSERT_EQ(s.send(), 0);
}

TEST_F(SlidingWindowSRTest, send_2seq) {
    sr s;
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
}

TEST_F(SlidingWindowSRTest, send_max) {
    sr s;
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    ASSERT_EQ(s.send(), 2);
    ASSERT_EQ(s.send(), -1);
}

TEST_F(SlidingWindowSRTest, receiveAck1) {
    sr s;
    s.send();
    ASSERT_EQ(s.getNrUnacked(), 1);
    s.receiveAck(0);
    ASSERT_EQ(s.getNrUnacked(), 0);
    
}

TEST_F(SlidingWindowSRTest, receiveAck2) {
    sr s;
    s.send();
    s.send();
    s.send();
    ASSERT_EQ(s.getNrUnacked(), 3);
    s.receiveAck(2);
    ASSERT_EQ(s.getNrUnacked(), 0);
}

TEST_F(SlidingWindowSRTest, receiveAck_loop) {
    sr s(2,3);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.receiveAck(0);
    s.receiveAck(1);
    ASSERT_EQ(s.send(), 2);
    ASSERT_EQ(s.send(), 3);
    s.receiveAck(2);
    ASSERT_EQ(s.send(), 0);
}

TEST_F(SlidingWindowSRTest, receiveAck_loop_multireceiveAck) {
    sr s(2, 3);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.receiveAck(1);
    ASSERT_EQ(s.getNrUnacked(), 0);
    ASSERT_EQ(s.send(), 2);
    s.receiveAck(2);
    ASSERT_EQ(s.send(), 3);
    ASSERT_EQ(s.send(), 0);
    s.receiveAck(0);
    ASSERT_EQ(s.getNrUnacked(), 0);
}

TEST_F(SlidingWindowSRTest, comprehensivetest) {
    sr s(4, 7);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    ASSERT_EQ(s.send(), 2);
    ASSERT_EQ(s.send(), 3);
    s.receiveAck(2);
    ASSERT_EQ(s.getNrUnacked(), 1);
    s.receiveAck(1);
    ASSERT_EQ(s.getNrUnacked(), 1);
    s.receiveAck(5);
    ASSERT_EQ(s.getNrUnacked(), 1);
    ASSERT_EQ(s.send(), 4);
    s.receiveAck(3);
    ASSERT_EQ(s.getNrUnacked(), 1);
    ASSERT_EQ(s.send(), 5);
    ASSERT_EQ(s.send(), 6);
    ASSERT_EQ(s.send(), 7);
    ASSERT_EQ(s.send(), -1);
    ASSERT_EQ(s.getNrUnacked(), 4);
    s.receiveAck(4);
    ASSERT_EQ(s.getNrUnacked(), 3);
    s.receiveAck(6);
    ASSERT_EQ(s.getNrUnacked(), 1);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.receiveAck(1);
    ASSERT_EQ(s.getNrUnacked(), 0);
    ASSERT_EQ(s.send(), 2);
    ASSERT_EQ(s.send(), 3);
    s.receiveAck(2);
    ASSERT_EQ(s.getNrUnacked(), 1);
    ASSERT_EQ(s.send(), 4);
    ASSERT_EQ(s.send(), 5);
    ASSERT_EQ(s.send(), 6);
    s.receiveAck(6);
    ASSERT_EQ(s.getNrUnacked(), 0);
}