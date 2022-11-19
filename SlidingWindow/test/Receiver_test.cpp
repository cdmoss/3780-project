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
    std::pair<unsigned int, std::set<unsigned int> *> p;
    std::set<unsigned int> *s = new std::set<unsigned int>;

    p = r->receive(0);
    ASSERT_EQ(p.first, 0);

    p = r->receive(2);
    ASSERT_EQ(p.first, 0);
    *s = {2};
    ASSERT_EQ(*(p.second), *(s));

    p = r->receive(1);
    ASSERT_EQ(p.first, 2);
    *s = {};
    ASSERT_EQ(*(p.second), *(s));

    delete s;
    s = nullptr;
}

TEST_F(ReceiverTest, receive_wrap_around) {
    std::pair<unsigned int, std::set<unsigned int> *> p;

    for (int i = 0; i < 8; i++) {
        p = r->receive(i);
    }

    p = r->receive(0);
    ASSERT_EQ(p.first, 0);
}
