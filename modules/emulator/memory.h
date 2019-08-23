#ifndef CHIP_MEMORY_H
#define CHIP_MEMORY_H
#include <array>
#include <string>


namespace chip8
{
namespace memory
{

template<typename MemoryType, std::size_t MemorySize>
class Memory
{
public:
    Memory() = default;
    ~Memory() { }; 
    const MemoryType& operator[](size_t index) { return memory[index]; }
private:
    std::array<MemoryType, MemorySize> memory;
};

using MemoryChip8 = Memory<uint8_t, 4096>;

loadChip8Program(const MemoryChip8& memory, const std::string program )
{

}

} /// memory
} /// chip8
#endif
