#include <gtest/gtest.h>
#include "../include/Sender.h"
#include "../include/Receiver.h"

class SenderTest : public testing::Test {
protected:
    Sender *s;

    void SetUp() override {
        s = new Sender();  // create a new class before each test to start fresh
    }

    void TearDown() override {
        delete s;
        s = nullptr;
    }
};

TEST_F(SenderTest, send) {
    Receiver *r = new Receiver();
    std::set<unsigned int> *set;
    auto ack = s -> send(r, 0);
    auto ackMap = ack.begin();
    set = new std::set<unsigned int> {};

    ASSERT_EQ(0, ackMap -> first);
    ASSERT_EQ(*set, *(ackMap -> second));

    s -> send(r, 2);
    s -> send(r, 3);
    ack = s -> send(r, 3);
    ackMap = ack.begin();

    *set = {2, 3};

    ASSERT_EQ(0, ackMap -> first);
    ASSERT_EQ(*set, *(ackMap -> second));

    ack = s -> send(r, 1);
    ackMap = ack.begin();
    *set = {};

    ASSERT_EQ(3, ackMap -> first);
    ASSERT_EQ(*set, *(ackMap -> second));

    delete set;
    delete r;
    r = nullptr;
    set = nullptr;
}

TEST_F(SenderTest, receiveAck) {
    Receiver *r = new Receiver();
    std::deque<unsigned int> d = {1, 2, 3, 4};
    s ->receiveAck(s -> send(r, 0));

    ASSERT_EQ(s -> getNumOfFrames(), 254);
    ASSERT_EQ(*(s -> getSlidingWindow() -> getSlidingWindow()), d);

    s ->receiveAck(s -> send(r, 2));
    s ->receiveAck(s -> send(r, 3));

    ASSERT_EQ(s -> getNumOfFrames(), 254);
    ASSERT_EQ(*(s -> getSlidingWindow() -> getSlidingWindow()), d);

    s ->receiveAck(s -> send(r, 1));

    d = {4, 5, 6, 7};

    ASSERT_EQ(s -> getNumOfFrames(), 251);
    ASSERT_EQ(*(s -> getSlidingWindow() -> getSlidingWindow()), d);

    delete r;
    r = nullptr;
}