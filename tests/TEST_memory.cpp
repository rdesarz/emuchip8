#include "gtest/gtest.h"
#include "emulator/memory.h"

using namespace chip8::memory;

TEST(Memory, Initialization) {
    RAM memory;
 
    EXPECT_EQ(0, memory[8]);
}

