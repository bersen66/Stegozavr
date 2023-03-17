#include <iostream>
#include <gtest/gtest.h>
#include <stegozavr/engine/engine.hpp>
#include <fstream>

#include <in_image_hider/hider_png.h>

/**
 * Just checking that it works
 */

namespace engine = ::stegozavr::engine::blocking;



TEST(TestEncode, 1) {
  std::fstream test_src("resources/test1_src.png", std::ios::binary | std::ios::in | std::ios::out);

  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(test_src, "Hello, world", output_image);
  ASSERT_EQ(::hider_png::custom::decode(output_image), "Hello, world");
}


TEST(TestEncode, 2) {
  std::fstream test_src("resources/test1_src.png", std::ios::binary | std::ios::in | std::ios::out);
  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(test_src, "", output_image);

  ASSERT_EQ(::hider_png::custom::decode(output_image), "");
}

TEST(TestEncode, 3) {
  std::fstream test_src("resources/test1_src.png", std::ios::binary | std::ios::in | std::ios::out);
  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(test_src, "abOOOOOOOOOOOOOOOOOOOOOOOOBA", output_image);

  ASSERT_EQ(::hider_png::custom::decode(output_image), "abOOOOOOOOOOOOOOOOOOOOOOOOBA");
}

TEST(TestEncode, 4) {
  std::fstream test_src("resources/test1_src.png", std::ios::binary | std::ios::in | std::ios::out);
  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(test_src, "Шлепа - большой русский кот", output_image);

  ASSERT_EQ(::hider_png::custom::decode(output_image), "Шлепа - большой русский кот");
}

TEST(TestEncode, 5) {
  std::fstream test_src("resources/test1_src.png", std::ios::binary | std::ios::in | std::ios::out);
  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(test_src, "Шлепа - большой русский кот", output_image);


  ASSERT_EQ(::hider_png::custom::decode(output_image), "Шлепа - большой русский кот");


  std::ofstream result("output.png", std::ios::binary);
  result << output_image.str();
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}