/**
 * Copyright (c) Romain Desarzens
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>

#include "gtest/gtest.h"

#include <boost/numeric/ublas/matrix.hpp>

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_view.h"
#include "fixtures.h"

using namespace chip8;

TEST_F(TestDisplayFixture, SetPixelValue) {
  display.setPixel(column_t(1), row_t(1), 1);

  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(1)), 1);
}

TEST_F(TestDisplayFixture, SetSpriteValue) {
  display.setPixel(column_t(1), row_t(1), 1);

  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(1)), 1);
}

TEST_F(TestDisplayFixture, TestModifiedPixelFlag) {
  auto modified = display.setPixel(column_t(1), row_t(1), 1);

  EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedPixelFlag) {
  display.setPixel(column_t(1), row_t(1), 1);

  auto modified = display.setPixel(column_t(1), row_t(1), 0);

  EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestModifiedSpriteFlag) {
  auto modified = display.setSprite(column_t(1), row_t(1), byteToSprite(0b11111111));

  EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedSpriteFlag) {
  auto modified = display.setSprite(column_t(1), row_t(1), byteToSprite(0b000000000));

  EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestSpriteOutsideOfScreen) {
  display.setSprite(column_t(63), row_t(1), byteToSprite(0b11111111));

  EXPECT_EQ(model.getPixelValue(column_t(0), row_t(1)), 1);
  EXPECT_EQ(model.getPixelValue(column_t(6), row_t(1)), 1);
  EXPECT_EQ(model.getPixelValue(column_t(7), row_t(1)), 0);
}

TEST_F(TestDisplayFixture, TestClearDisplay) {
  display.setPixel(column_t(1), row_t(1), 1);

  display.clear();

  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(1)), 0);
}

TEST_F(TestDisplayFixture, TestMakeSprite) {
  uint8_t byte = 0b11111111;

  auto result = byteToSprite(byte);

  EXPECT_EQ(result[7], 1);
  EXPECT_EQ(result[0], 1);
}