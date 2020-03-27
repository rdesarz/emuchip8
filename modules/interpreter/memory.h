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
#ifndef CHIP_MEMORY_H
#define CHIP_MEMORY_H
#include <array>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

#include "boost/serialization/strong_typedef.hpp"

namespace chip8 {

extern const std::size_t SPRITE_OFFSET;

extern const std::size_t ZERO_SPRITE_OFFSET;
extern const std::size_t ONE_SPRITE_OFFSET;
extern const std::size_t TWO_SPRITE_OFFSET;
extern const std::size_t THREE_SPRITE_OFFSET;
extern const std::size_t FOUR_SPRITE_OFFSET;
extern const std::size_t FIVE_SPRITE_OFFSET;
extern const std::size_t SIX_SPRITE_OFFSET;
extern const std::size_t SEVEN_SPRITE_OFFSET;
extern const std::size_t EIGHT_SPRITE_OFFSET;
extern const std::size_t NINE_SPRITE_OFFSET;
extern const std::size_t A_SPRITE_OFFSET;
extern const std::size_t B_SPRITE_OFFSET;
extern const std::size_t C_SPRITE_OFFSET;
extern const std::size_t D_SPRITE_OFFSET;
extern const std::size_t E_SPRITE_OFFSET;
extern const std::size_t F_SPRITE_OFFSET;

template <typename MemoryUnit, std::size_t MemorySize>
class GenericMemory {
 public:
  GenericMemory() : m_container(MemorySize, 0) {}
  virtual ~GenericMemory() = default;

  typedef typename std::vector<MemoryUnit>::iterator iterator;
  typedef typename std::vector<MemoryUnit>::const_iterator const_iterator;
  iterator begin() { return m_container.begin(); }
  [[nodiscard]] const_iterator begin() const { return m_container.begin(); }
  iterator end() { return m_container.end(); }
  [[nodiscard]] const_iterator end() const { return m_container.end(); }

  MemoryUnit& operator[](size_t index) { return m_container[index]; }

 private:
  std::vector<MemoryUnit> m_container;
};

using RAM = GenericMemory<uint8_t, 4096>;
using Stack = GenericMemory<uint16_t, 16>;

std::ostream& operator<<(std::ostream& os, const RAM& ram);

template <typename MemoryType>
class Register {
 public:
  Register() : m_value(MemoryType()) {}
  explicit Register(MemoryType value) : m_value(value) {}
  Register(const Register& register_) : m_value(register_.m_value) {}
  Register& operator=(const Register& rhs) {
    m_value = rhs.m_value;
    return *this;
  }
  Register& operator=(const MemoryType& rhs) {
    m_value = rhs;
    return *this;
  }
  operator const MemoryType&() const { return m_value; }
  operator MemoryType&() { return m_value; }
  bool operator==(const Register& rhs) const { return m_value == rhs.m_value; }
  bool operator<(const Register& rhs) const { return m_value < rhs.m_value; }

 private:
  MemoryType m_value;
};

using GeneralRegister = Register<uint8_t>;
using IndexRegister = Register<uint16_t>;
using ProgramCounter = Register<uint16_t>;
using StackPointer = Register<uint8_t>;
using DelayTimerRegister = Register<uint8_t>;
using SoundTimerRegister = Register<uint8_t>;

}  // namespace chip8
#endif  // MODULES_INTERPRETER_MEMORY_H_
