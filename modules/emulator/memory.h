#ifndef CHIP_MEMORY_H
#define CHIP_MEMORY_H
#include <array>
#include <vector>
#include <string>
#include <type_traits>

#include "boost/serialization/strong_typedef.hpp"
 
namespace chip8
{
namespace memory
{

template<typename MemoryUnit, std::size_t MemorySize>
class GenericMemory
{
public:
    GenericMemory() = default;
    ~GenericMemory() { }; 
    MemoryUnit& operator[](size_t index) { return m_container[index]; }
private: 
    std::array<MemoryUnit, MemorySize> m_container;
};

using RAM = GenericMemory<uint8_t, 4096>;
using Stack = GenericMemory<uint16_t, 16>;

template<typename MemoryType>
class Register
{
public:
    Register() { };
    explicit Register(MemoryType value) : m_value(value) { };
    Register(const Register & register_) : m_value(register_.m_value) {}   
    Register & operator=(const Register & rhs) { m_value = rhs.m_value; return *this;}    
    Register & operator=(const MemoryType & rhs) { m_value = rhs; return *this;}      
    operator const MemoryType & () const { return m_value; }                    
    operator MemoryType & () { return m_value; }
    bool operator==(const Register & rhs) const { return m_value == rhs.m_value; } 
    bool operator<(const Register & rhs) const { return m_value < rhs.m_value; }   

private:
    MemoryType m_value;
};

using GeneralRegister = Register<uint8_t>;
using MemoryAddressRegister = Register<uint16_t>;
using ProgramCounter = Register<uint16_t>;
using StackPointer = Register<uint8_t>;


} /// memory
} /// chip8
#endif
