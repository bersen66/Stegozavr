#include <iostream>
#include <gtest/gtest.h>

/**
 * Just checking that it works
 */
TEST(T1, 1) {
  ASSERT_EQ(1, 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}