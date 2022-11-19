#include <gtest/gtest.h>
#include "../include/Sender.h"

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

    // send returns ack
    r->receive(0);
    set = new std::set<unsigned int>{};

    ASSERT_EQ(0, r->getSlidingWindow()->getFirstSeqNum());
    ASSERT_EQ(*(set), *(r->getFrameBuffer()));

    r->receive(2);
    r->receive(3);

    *set = {2, 3};

    ASSERT_EQ(0, r->getSlidingWindow()->getFirstSeqNum());
    ASSERT_EQ(*(set), *(r->getFrameBuffer()));

    r->receive(1);
    *set = {};

    ASSERT_EQ(3, r->getSlidingWindow()->getFirstSeqNum());
    ASSERT_EQ(*(set), *(r->getFrameBuffer()));

    delete set;
    delete r;
    r = nullptr;
    set = nullptr;
}

TEST_F(SenderTest, receiveAck) {
    Receiver *r = new Receiver();
    std::deque<unsigned int> d = {1, 2, 3, 4};
    s->receiveAck(s->send(r));

    ASSERT_EQ(s->getNumOfFrames(), 254);
    ASSERT_EQ(*(s->getSlidingWindow()->getSlidingWindow()), d);

    s->receiveAck(s->send(r));
    s->receiveAck(s->send(r));

    ASSERT_EQ(s->getNumOfFrames(), 254);
    ASSERT_EQ(*(s->getSlidingWindow()->getSlidingWindow()), d);

    s->receiveAck(s->send(r));

    d = {4, 5, 6, 7};

    ASSERT_EQ(s->getNumOfFrames(), 251);
    ASSERT_EQ(*(s->getSlidingWindow()->getSlidingWindow()), d);

    delete r;
    r = nullptr;
}