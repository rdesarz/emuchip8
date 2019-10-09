#include "gtest/gtest.h"

#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_view.h"
#include "fixtures.h"

using namespace chip8;

TEST_F(TestDisplayFixture, SetPixelValue) {
  display.setPixel(1, 1, 1);

  EXPECT_EQ(model.getPixelValue(1, 1), 1);
}

TEST_F(TestDisplayFixture, SetSpriteValue) {
  display.setPixel(1, 1, 1);

  EXPECT_EQ(model.getPixelValue(1, 1), 1);
}

TEST_F(TestDisplayFixture, TestModifiedPixelFlag) {
  auto modified = display.setPixel(1, 1, 1);

  EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedPixelFlag) {
  display.setPixel(1, 1, 1);

  auto modified = display.setPixel(1, 1, 0);

  EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestModifiedSpriteFlag) {
  auto modified = display.setSprite(1, 1, makeSprite<uint8_t>(0b11111111));

  EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedSpriteFlag) {
  auto modified = display.setSprite(1, 1, makeSprite<uint8_t>(0b000000000));

  EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestSpriteOutsideOfScreen) {
  display.setSprite(63, 1, makeSprite<uint8_t>(0b11111111));

  EXPECT_EQ(model.getPixelValue(0, 1), 1);
  EXPECT_EQ(model.getPixelValue(6, 1), 1);
  EXPECT_EQ(model.getPixelValue(7, 1), 0);
}
