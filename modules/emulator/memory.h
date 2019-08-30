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
    Register() : m_value(MemoryType()) { };
    
    Register(MemoryType value) : m_value(value) { };
    
    void operator=(const Register<MemoryType>& to_assign)
    {
        m_value = to_assign.m_value;
    }

    void set(MemoryType value)
    {
        m_value = value;
    } 
    
    const MemoryType& get() const
    {
        return m_value;
    }

    Register<MemoryType>& operator--()
    {
        --m_value;
        return *this; 
    } 

    Register<MemoryType>& operator++()
    {
        ++m_value;
        return *this; 
    }

    Register<MemoryType>& operator+(MemoryType value)
    {
        m_value += value;
        return *this; 
    }
     
    Register<MemoryType>& operator-(MemoryType value)
    {
        m_value -= value;
        return *this; 
    }

    Register<MemoryType>& operator+=(MemoryType value)
    {
        m_value += value;
        return *this; 
    }

    Register<MemoryType>& operator-=(MemoryType value)
    {
        m_value -= value;
        return *this; 
    }

    Register<MemoryType>& operator|(const Register<MemoryType>& rh_register)
    {
        m_value = m_value | rh_register.m_value;
        return *this; 
    }

    Register<MemoryType>& operator&(const Register<MemoryType>& rh_register)
    {
        m_value = m_value & rh_register.m_value;
        return *this; 
    }
    
    Register<MemoryType>& operator^(const Register<MemoryType>& rh_register)
    {
        m_value = m_value ^ rh_register.m_value;
        return *this; 
    }

    bool operator==(const Register<MemoryType>& rh_register) const
    {
        return m_value == rh_register.m_value;
    }
    
    bool operator!=(const Register<MemoryType>& rh_register) const
    {
        return !(*this == rh_register);
    }
    
    bool operator==(MemoryType value) const
    {
        return m_value == value;
    }
    
    bool operator!=(MemoryType value) const
    {
        return !(m_value == value);
    }
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
