#include "gtest/gtest.h"
#include "emulator/interpreter.h"

using namespace chip8::memory;
using namespace chip8::interpreter;

TEST(InterpreterTest, returnFromSubroutine) {
    ProgramCounter pc(0x1);
    Stack stack;
    stack[0x1] = 0x4;
    StackPointer stack_ptr(0x1);

    returnFromSubroutine(pc, stack_ptr, stack);

    EXPECT_EQ(stack_ptr.get(), 0x0);
    EXPECT_EQ(pc.get(), 0x4);
}

TEST(InterpreterTest, jumpToLocation) {
    ProgramCounter pc(0x0);

    jumpToLocation(0x12, pc);

    EXPECT_EQ(pc.get(), 0x12);
}

TEST(InterpreterTest, callSubroutineAt) {
    ProgramCounter pc(0x4);
    Stack stack;
    StackPointer stack_ptr(0x0);

    callSubroutineAt(0x12, pc, stack_ptr, stack);

    EXPECT_EQ(pc.get(), 0x12);
    EXPECT_EQ(stack_ptr.get(), 0x1);
    EXPECT_EQ(stack[stack_ptr.get()], 0x4);
}


TEST(InterpreterTest, jumpBecauseValueAndRegisterAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    skipNextInstructionIfEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc.get(), 0x6);
}

TEST(InterpreterTest, jumpBecauseValueAndRegisterAreNotEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;

    skipNextInstructionIfEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc.get(), 0x4);
}

