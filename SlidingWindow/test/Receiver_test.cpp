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
    std::pair<unsigned int, std::vector<unsigned int>> p;
    p = r->receive(0);
    ASSERT_EQ(p.first, 0);

    p = r->receive(2);
    std::vector<unsigned int> s = {2};

    ASSERT_EQ(p.first, 0);
    ASSERT_EQ(p.second, s);

    p = r->receive(1);
    ASSERT_EQ(p.first, 2);
    s = {};
    ASSERT_EQ(p.second, s);

    p = r->receive(1);
    ASSERT_EQ(p.first, 2);
}

TEST_F(ReceiverTest, receiveWrapAround) {
    std::pair<unsigned int, std::vector<unsigned int>> p;

    for (int i = 0; i < 8; i++) {
        p = r->receive(i);
    }

    p = r->receive(0);
    ASSERT_EQ(p.first, 0);
}

TEST_F(ReceiverTest, getFirstFrameBufferElement) {
    r->receive(1);
    r->receive(3);

    ASSERT_EQ(r -> getFirstFrameBufferElement(), 1);

    r ->receive(0);
    ASSERT_EQ(r -> getFirstFrameBufferElement(), 3);

    r ->receive(2);
    ASSERT_EQ(r -> getFirstFrameBufferElement(), -1);
}