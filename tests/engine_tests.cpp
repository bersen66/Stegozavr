#include <iostream>
#include <gtest/gtest.h>
#include <stegozavr/engine/engine.hpp>

/**
 * Just checking that it works
 */
TEST(Encode, 1) {

  ASSERT_EQ(1, 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}