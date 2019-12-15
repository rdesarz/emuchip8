#ifndef CHIP_MEMORY_H
#define CHIP_MEMORY_H
#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include "boost/serialization/strong_typedef.hpp"

namespace chip8 {

template <typename MemoryUnit, std::size_t MemorySize>
class GenericMemory {
 public:
  GenericMemory() : m_container(MemorySize, 0) {}
  virtual ~GenericMemory() = default;

  typedef typename std::vector<MemoryUnit>::iterator iterator;
  typedef typename std::vector<MemoryUnit>::const_iterator const_iterator;
  iterator begin() { return m_container.begin(); }
  const_iterator begin() const { return m_container.begin(); }
  iterator end() { return m_container.end(); }
  const_iterator end() const { return m_container.end(); }

  MemoryUnit& operator[](size_t index) { return m_container[index]; }

 private:
  std::vector<MemoryUnit> m_container;
};

using RAM = GenericMemory<uint8_t, 4096>;
using Stack = GenericMemory<uint16_t, 16>;

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
#endif
