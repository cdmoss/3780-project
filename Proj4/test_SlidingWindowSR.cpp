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

TEST_F(SlidingWindowSRTest, ack1) {
    sr s;
    s.send();
    ASSERT_EQ(s.getNrUnacked(), 1);
    s.ack(0);
    ASSERT_EQ(s.getNrUnacked(), 0);
    
}

TEST_F(SlidingWindowSRTest, ack2) {
    sr s;
    s.send();
    s.send();
    s.send();
    ASSERT_EQ(s.getNrUnacked(), 3);
    s.ack(2);
    ASSERT_EQ(s.getNrUnacked(), 0);
}

TEST_F(SlidingWindowSRTest, ack_loop) {
    sr s(2,3);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.ack(0);
    s.ack(1);
    ASSERT_EQ(s.send(), 2);
    ASSERT_EQ(s.send(), 3);
    s.ack(2);
    ASSERT_EQ(s.send(), 0);
}

TEST_F(SlidingWindowSRTest, ack_loop_multiack) {
    sr s(2, 3);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.ack(1);
    ASSERT_EQ(s.getNrUnacked(), 0);
    ASSERT_EQ(s.send(), 2);
    s.ack(2);
    ASSERT_EQ(s.send(), 3);
    ASSERT_EQ(s.send(), 0);
    s.ack(0);
    ASSERT_EQ(s.getNrUnacked(), 0);
}

TEST_F(SlidingWindowSRTest, ack_resend) {
    sr s(2, 3);
    ASSERT_EQ(s.send(), 0);
    ASSERT_EQ(s.send(), 1);
    s.ack(1);
    s.ack(1);
}

// TEST_F(SlidingWindowSRTest, send_loop) {
//     sr s(4,3);
//     ASSERT_EQ(s.send(), 0);
//     ASSERT_EQ(s.send(), 1);
//     ASSERT_EQ(s.send(), 2);
// }
// // RECEIVER
// // TEST_F(SlidingWindowSRTest, receive_init) {
// //     SRReceiver s(2);
// //     ASSERT_TRUE(s.receive(0) == 0);
// // }

// TEST_F(SlidingWindowSRTest, receive_inorder) {
//     SRReceiver s(4);
//     s.receive(0);
//     s.receive(1);
//     s.receive(2);
//     ASSERT_TRUE(s.receive(3) == 3 && s.getOutOfOrderSeqs().size() == 0);
// }

// TEST_F(SlidingWindowSRTest, receive_outorder_notalreadybuffered_single) {
//     SRReceiver s(4, 0);
//     unsigned int lastAck = s.receive(3);
//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(s.receive(3) == 0 && outOfOrderSeqs.size() == 1 && outOfOrderSeqs[0] == 3);
// }

// TEST_F(SlidingWindowSRTest, receive_outorder_alreadybuffered_single) {
//     SRReceiver s(4, 0);
//     s.receive(3);
//     s.receive(3);
//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(s.receive(3) == 0 && outOfOrderSeqs.size() == 1 && outOfOrderSeqs[0] == 3);
// }

// TEST_F(SlidingWindowSRTest, receive_outorder_notalreadybuffered_multiple) {
//     SRReceiver s(4, 0);
//     s.receive(3);
//     unsigned int lastAck = s.receive(4);
//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(
//         lastAck == 0 && 
//         outOfOrderSeqs.size() == 2 && 
//         outOfOrderSeqs[0] == 3 &&
//         outOfOrderSeqs[1] == 4
//     );
// }

// TEST_F(SlidingWindowSRTest, receive_outorder_alreadybuffered_multiple) {
//     SRReceiver s(4, 0);
//     s.receive(3);
//     s.receive(4);
//     s.receive(3);
//     unsigned int lastAck = s.receive(4);
//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(
//         lastAck == 0 && 
//         outOfOrderSeqs.size() == 2 && 
//         outOfOrderSeqs[0] == 3 &&
//         outOfOrderSeqs[1] == 4
//     );
// }

// TEST_F(SlidingWindowSRTest, receive_inorder_lookback) {
//     SRReceiver s(7);
//     // rec 2 in order
//     s.receive(0);
//     s.receive(1);

//     // rec 3 out of order
//     s.receive(3);
//     s.receive(4);
//     s.receive(5);

//     // rec missing in order
//     unsigned int lastAck = s.receive(2);

//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(lastAck == 5 && outOfOrderSeqs.size() == 0);
// }

// TEST_F(SlidingWindowSRTest, receive_inorder_lookback_withleftovers) {
//     SRReceiver s(8);
//     // rec 2 in order
//     s.receive(0);
//     s.receive(1);

//     // rec 3 out of order
//     s.receive(3);
//     s.receive(4);
//     s.receive(5);

//     // rec 2 out of order ahead
//     s.receive(7);
//     s.receive(8);

//     // rec missing in order
//     unsigned int lastAck = s.receive(2);

//     uintvec outOfOrderSeqs = s.getOutOfOrderSeqs();
//     ASSERT_TRUE(
//         lastAck == 5 && 
//         outOfOrderSeqs.size() == 2 &&
//         outOfOrderSeqs[0] == 7 &&
//         outOfOrderSeqs[1] == 8
//     );
// }

// // SENDER
// TEST_F(SlidingWindowSRTest, sender_init) {
//     SRSender s(2, 7);
//     ASSERT_TRUE(s.send() == 0);
// }

// TEST_F(SlidingWindowSRTest, sender_0window) {
//     SRSender s(0, 7);
//     ASSERT_TRUE(s.send() == -1);
// }

// TEST_F(SlidingWindowSRTest, sender_inorder_multi1) {
//     SRSender s(4, 7);

//     ASSERT_TRUE(
//         s.send() == 0 &&
//         s.send() == 1 &&
//         s.send() == 2 &&
//         s.send() == 3 &&
//         s.send() == -1 &&
//         s.getUnackedSeqs().size() == 4
//     );
// }

// TEST_F(SlidingWindowSRTest, sender_inorder_multi2) {
//     SRSender s(4, 7);

//     s.send();
//     s.send();
//     s.send();
//     s.send();
//     s.receiveAck(2);


//     ASSERT_TRUE(s.send() == 4);

// }


// TEST_F(SlidingWindowSRTest, sender_inorder_wrap1) {
//     SRSender s(2, 3);

//     s.send(); // 0
//     s.send(); // 1
//     s.receiveAck(0);
//     s.receiveAck(1);
//     s.send(); // 2

//     ASSERT_EQ(s.send(), 0);
// }

// TEST_F(SlidingWindowSRTest, sender_inorder_wrap2) {
//     SRSender s(3, 3);

//     s.send(); // 0
//     s.receiveAck(0);
//     s.receiveAck(1);
//     s.send(); // 1
//     s.send(); // 2
//     s.send(); // 0

//     ASSERT_EQ(s.getUnackedSeqs().size(), 0);
// }


// TEST_F(SlidingWindowSRTest, sender_outorder_1) {
//     SRSender s(4, 7);

//     s.send(); // 0
//     s.send(); // 1
//     s.send(); // 2
//     s.send(); // 3
//     s.receiveAck(0);
//     s.send(); // 4
//     s.receiveAck(0);

//     uintvec unacked = s.getUnackedSeqs();

//     ASSERT_TRUE(
//         unacked.size() == 4 &&
//         unacked[0] == 1 &&
//         unacked[1] == 2 &&
//         unacked[2] == 3 &&
//         unacked[3] == 4
//     );
// }

// TEST_F(SlidingWindowSRTest, sender_outorder_2) {
//     SRSender s(4, 7);

//     s.send(); // 0
//     s.send(); // 1
//     s.send(); // 2
//     s.send(); // 3
//     s.receiveAck(0);
//     s.receiveAck(1);
//     s.receiveAck(2);
//     s.send(); // 4
//     s.send(); // 5

//     uintvec unacked = s.getUnackedSeqs();

//     ASSERT_TRUE(s.send() == 6);
// }

// TEST_F(SlidingWindowSRTest, sender_outorder_3) {
//     SRSender s(4, 7);

//     s.send(); // 0
//     s.send(); // 1
//     s.send(); // 2
//     s.send(); // 3
//     s.receiveAck(0);
//     s.receiveAck(1);
//     s.receiveAck(2);
//     s.send(); // 4
//     s.send(); // 5

//     ASSERT_TRUE(s.send() == 6);
// }

// TEST_F(SlidingWindowSRTest, sender_outorder_4) {
//     SRSender s(4, 7);

//     s.send(); // 0
//     s.send(); // 1
//     s.send(); // 2
//     s.send(); // 3
//     s.receiveAck(0);
//     s.receiveAck(1);
//     s.receiveAck(2);
//     s.send(); // 4
//     s.send(); // 5
//     s.send(); // 6
//     s.receiveAck(2);    

//     ASSERT_TRUE(s.send() == -1);
// }
