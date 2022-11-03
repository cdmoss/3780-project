#include "GoBackN.h"
#include <gtest/gtest.h>  // google test framework

class GoBackNTest : public testing::Test {
// protected:
//   GoBackN * h_;

//   void SetUp() override {
//     g_ = new GoBackN;  // create a new class before each test to start fresh
//   }

//   void TearDown() override {
//     delete g_;
//   }
};

TEST_F(GoBackNTest, ZeroWindow) {
  GoBackNSender g(10, 0);
  ASSERT_TRUE(g.sendSeq() == -1);
}

TEST_F(GoBackNTest, ValidWindow) {
  GoBackNSender g(10, 3);
  g.sendSeq();
  g.sendSeq();
  ASSERT_TRUE(g.sendSeq() == 2);
}

TEST_F(GoBackNTest, TooManySends) {
  GoBackNSender g(10, 3);
  g.sendSeq();
  g.sendSeq();
  g.sendSeq();
  ASSERT_TRUE(g.sendSeq() == -1);
}