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
