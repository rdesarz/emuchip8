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

TEST(InterpreterTest, DontJumpBecauseValueAndRegisterAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    skipNextInstructionIfNotEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc.get(), 0x4);
}

TEST(InterpreterTest, DontJumpBecauseValueAndRegisterAreNotEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;

    skipNextInstructionIfNotEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc.get(), 0x6);
}

TEST(InterpreterTest, JumpBecauseTwoRegistersAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;
    registers[0] = 0x1;

    skipNextInstructionIfRegistersEqual(0, 1, registers, pc);

    EXPECT_EQ(pc.get(), 0x6);
}

TEST(InterpreterTest, StoreInRegister) {
    std::vector<GeneralRegister> registers(16);

    storeInRegister(0x2, 1, registers);

    EXPECT_EQ(registers[1].get(), 0x2);
}


TEST(InterpreterTest, AddToRegister) {
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    addToRegister(0x2, 1, registers);

    EXPECT_EQ(registers[1].get(), 0x4);
}
