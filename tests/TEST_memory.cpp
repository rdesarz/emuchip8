#include "gtest/gtest.h"
#include "emulator/memory.h"

using namespace chip8::memory;

TEST(Memory, Initialization) {
    MemoryChip8 memory_chip8;
 
    EXPECT_EQ(0, memory_chip8[8]);
}

