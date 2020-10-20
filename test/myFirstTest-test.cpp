#include "gtest/gtest.h"

TEST(addition, additionCorrect) {
  int result = 2 + 2;
  ASSERT_EQ(result, 4);
}

TEST(addition, additionInCorrect) {
  int result = 2 + 2;
  ASSERT_NEQ(result, 5);
}



