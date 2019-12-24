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
#include <algorithm>

#include "interpreter/memory.h"

namespace chip8 {

static const std::size_t SPRITE_SIZE = 5;

using sprite_t = std::array<uint8_t, SPRITE_SIZE>;

static const sprite_t ZERO_SPRITE = {0xF0, 0x90, 0x90, 0x90, 0xF0};

static const sprite_t ONE_SPRITE = {0x20, 0x60, 0x20, 0x20, 0x70};

static const sprite_t TWO_SPRITE = {0xF0, 0x10, 0xF0, 0x80, 0xF0};

static const sprite_t THREE_SPRITE = {0xF0, 0x10, 0xF0, 0x10, 0xF0};

static const sprite_t FOUR_SPRITE = {0x90, 0x90, 0xF0, 0x10, 0x10};

static const sprite_t FIVE_SPRITE = {0xF0, 0x80, 0xF0, 0x10, 0xF0};

static const sprite_t SIX_SPRITE = {0xF0, 0x80, 0xF0, 0x90, 0xF0};

static const sprite_t SEVEN_SPRITE = {0xF0, 0x10, 0x20, 0x40, 0x40};

static const sprite_t EIGHT_SPRITE = {0xF0, 0x90, 0xF0, 0x90, 0xF0};

static const sprite_t NINE_SPRITE = {0xF0, 0x90, 0xF0, 0x10, 0xF0};

static const sprite_t A_SPRITE = {0xF0, 0x90, 0xF0, 0x90, 0x90};

static const sprite_t B_SPRITE = {0xE0, 0x90, 0xE0, 0x90, 0xE0};

static const sprite_t C_SPRITE = {0xF0, 0x80, 0x80, 0x80, 0xF0};

static const sprite_t D_SPRITE = {0xE0, 0x90, 0x90, 0x90, 0xE0};

static const sprite_t E_SPRITE = {0xF0, 0x80, 0xF0, 0x80, 0xF0};

static const sprite_t F_SPRITE = {0xF0, 0x80, 0xF0, 0x80, 0x80};

void storeSpriteInMemory(RAM& ram) {
  std::copy(ZERO_SPRITE.begin(), ZERO_SPRITE.end(), ram.begin());
  std::copy(ONE_SPRITE.begin(), ONE_SPRITE.end(), ram.begin() + 5);
  std::copy(TWO_SPRITE.begin(), TWO_SPRITE.end(), ram.begin() + 10);
  std::copy(THREE_SPRITE.begin(), THREE_SPRITE.end(), ram.begin() + 15);
  std::copy(FOUR_SPRITE.begin(), FOUR_SPRITE.end(), ram.begin() + 20);
  std::copy(FIVE_SPRITE.begin(), FIVE_SPRITE.end(), ram.begin() + 25);
  std::copy(SIX_SPRITE.begin(), SIX_SPRITE.end(), ram.begin() + 30);
  std::copy(SEVEN_SPRITE.begin(), SEVEN_SPRITE.end(), ram.begin() + 35);
  std::copy(EIGHT_SPRITE.begin(), EIGHT_SPRITE.end(), ram.begin() + 40);
  std::copy(NINE_SPRITE.begin(), NINE_SPRITE.end(), ram.begin() + 45);
  std::copy(A_SPRITE.begin(), A_SPRITE.end(), ram.begin() + 50);
  std::copy(B_SPRITE.begin(), B_SPRITE.end(), ram.begin() + 55);
  std::copy(C_SPRITE.begin(), C_SPRITE.end(), ram.begin() + 60);
  std::copy(D_SPRITE.begin(), D_SPRITE.end(), ram.begin() + 65);
  std::copy(E_SPRITE.begin(), E_SPRITE.end(), ram.begin() + 70);
  std::copy(F_SPRITE.begin(), F_SPRITE.end(), ram.begin() + 75);
}

}  // namespace chip8
