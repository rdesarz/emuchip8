#include "gtest/gtest.h"
#include "emulator/interpreter.h"

using namespace chip8::memory;
using namespace chip8::interpreter;

TEST(InterpreterTest, Initialization) {
    ProgramCounter pc(0x1);
    Stack stack;
    stack[0x1] = 0x4;
    StackPointer stack_ptr(0x1);

    returnFromSubroutine(pc, stack_ptr, stack);

    EXPECT_EQ(stack_ptr.get(), 0x0);
    EXPECT_EQ(pc.get(), 0x4);
}

