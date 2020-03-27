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
#include <iomanip>

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

extern const std::size_t SPRITE_OFFSET = 5;
extern const std::size_t ZERO_SPRITE_OFFSET = 0;
extern const std::size_t ONE_SPRITE_OFFSET = 5;
extern const std::size_t TWO_SPRITE_OFFSET = 10;
extern const std::size_t THREE_SPRITE_OFFSET = 15;
extern const std::size_t FOUR_SPRITE_OFFSET = 20;
extern const std::size_t FIVE_SPRITE_OFFSET = 25;
extern const std::size_t SIX_SPRITE_OFFSET = 30;
extern const std::size_t SEVEN_SPRITE_OFFSET = 35;
extern const std::size_t EIGHT_SPRITE_OFFSET = 40;
extern const std::size_t NINE_SPRITE_OFFSET = 45;
extern const std::size_t A_SPRITE_OFFSET = 50;
extern const std::size_t B_SPRITE_OFFSET = 55;
extern const std::size_t C_SPRITE_OFFSET = 60;
extern const std::size_t D_SPRITE_OFFSET = 65;
extern const std::size_t E_SPRITE_OFFSET = 70;
extern const std::size_t F_SPRITE_OFFSET = 75;

void storeSpriteInMemory(RAM& ram) {
  std::copy(ZERO_SPRITE.begin(), ZERO_SPRITE.end(),
            ram.begin() + ZERO_SPRITE_OFFSET);
  std::copy(ONE_SPRITE.begin(), ONE_SPRITE.end(),
            ram.begin() + ONE_SPRITE_OFFSET);
  std::copy(TWO_SPRITE.begin(), TWO_SPRITE.end(),
            ram.begin() + TWO_SPRITE_OFFSET);
  std::copy(THREE_SPRITE.begin(), THREE_SPRITE.end(),
            ram.begin() + THREE_SPRITE_OFFSET);
  std::copy(FOUR_SPRITE.begin(), FOUR_SPRITE.end(),
            ram.begin() + FOUR_SPRITE_OFFSET);
  std::copy(FIVE_SPRITE.begin(), FIVE_SPRITE.end(),
            ram.begin() + FIVE_SPRITE_OFFSET);
  std::copy(SIX_SPRITE.begin(), SIX_SPRITE.end(),
            ram.begin() + SIX_SPRITE_OFFSET);
  std::copy(SEVEN_SPRITE.begin(), SEVEN_SPRITE.end(),
            ram.begin() + SEVEN_SPRITE_OFFSET);
  std::copy(EIGHT_SPRITE.begin(), EIGHT_SPRITE.end(),
            ram.begin() + EIGHT_SPRITE_OFFSET);
  std::copy(NINE_SPRITE.begin(), NINE_SPRITE.end(),
            ram.begin() + NINE_SPRITE_OFFSET);
  std::copy(A_SPRITE.begin(), A_SPRITE.end(), ram.begin() + A_SPRITE_OFFSET);
  std::copy(B_SPRITE.begin(), B_SPRITE.end(), ram.begin() + B_SPRITE_OFFSET);
  std::copy(C_SPRITE.begin(), C_SPRITE.end(), ram.begin() + C_SPRITE_OFFSET);
  std::copy(D_SPRITE.begin(), D_SPRITE.end(), ram.begin() + D_SPRITE_OFFSET);
  std::copy(E_SPRITE.begin(), E_SPRITE.end(), ram.begin() + E_SPRITE_OFFSET);
  std::copy(F_SPRITE.begin(), F_SPRITE.end(), ram.begin() + F_SPRITE_OFFSET);
}

std::ostream& operator<<(std::ostream& os, const RAM& ram) {
  for (auto byte = ram.begin(); byte != ram.end();
       byte += 2) {
    // Show instructions by group of eight on each line and show memory address
    if (std::distance(ram.begin(), byte) % 16 == 0) {
      os << "\n" << std::dec << std::setw(8) << std::distance(ram.begin(), byte) << "  ";
    }

    os << "0x" << std::setfill('0') << std::hex << std::setw(2)
       << static_cast<unsigned int>(*byte) << std::setfill('0')
       << std::hex << std::setw(2) << static_cast<unsigned int>(*(byte+1)) << " ";
  }

  return os;
}

}  // namespace chip8
