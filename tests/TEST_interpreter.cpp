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

    EXPECT_EQ(stack_ptr, 0x0);
    EXPECT_EQ(pc, 0x4);
}

TEST(InterpreterTest, jumpToLocation) {
    ProgramCounter pc(0x0);

    jumpToLocation(0x12, pc);

    EXPECT_EQ(pc, 0x12);
}

TEST(InterpreterTest, callSubroutineAt) {
    ProgramCounter pc(0x4);
    Stack stack;
    StackPointer stack_ptr(0x0);

    callSubroutineAt(0x12, pc, stack_ptr, stack);

    EXPECT_EQ(pc, 0x12);
    EXPECT_EQ(stack_ptr, 0x1);
    EXPECT_EQ(stack[stack_ptr], 0x4);
}


TEST(InterpreterTest, jumpBecauseValueAndRegisterAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    skipNextInstructionIfEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc, 0x6);
}

TEST(InterpreterTest, jumpBecauseValueAndRegisterAreNotEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;

    skipNextInstructionIfEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc, 0x4);
}

TEST(InterpreterTest, DontJumpBecauseValueAndRegisterAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    skipNextInstructionIfNotEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc, 0x4);
}

TEST(InterpreterTest, DontJumpBecauseValueAndRegisterAreNotEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;

    skipNextInstructionIfNotEqual(0x2, 1, registers, pc);

    EXPECT_EQ(pc, 0x6);
}

TEST(InterpreterTest, JumpBecauseTwoRegistersAreEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x1;
    registers[0] = 0x1;

    skipNextInstructionIfRegistersEqual(0, 1, registers, pc);

    EXPECT_EQ(pc, 0x6);
}

TEST(InterpreterTest, StoreInRegister) {
    std::vector<GeneralRegister> registers(16);

    storeInRegister(0x2, 1, registers);

    EXPECT_EQ(registers[1], 0x2);
}


TEST(InterpreterTest, AddToRegister) {
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x2;

    addToRegister(0x2, 1, registers);

    EXPECT_EQ(registers[1], 0x4);
}

TEST(InterpreterTest, storeRegisterInRegister) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0x6;
    registers[1] = 0x2;

    storeRegisterInRegister(1, 0, registers);

    EXPECT_EQ(registers[0], 0x6);
    EXPECT_EQ(registers[1], 0x6);
}

TEST(InterpreterTest, bitwiseOR) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b11001111;
    registers[1] = 0b00001111;

    bitwiseOr(1, 0, registers);
    
    EXPECT_EQ(registers[1], 0b11001111);
}

TEST(InterpreterTest, bitwiseAnd) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b11001111;
    registers[1] = 0b00001111;

    bitwiseAnd(1, 0, registers);
    
    EXPECT_EQ(registers[1], 0b00001111);
}

TEST(InterpreterTest, bitwiseXor) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b11001111;
    registers[1] = 0b00001111;

    bitwiseXor(1, 0, registers);
    
    EXPECT_EQ(registers[1], 0b11000000);
}

TEST(InterpreterTest, addRegisterToRegisterBelowLimit) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0x2;
    registers[1] = 0x2;

    addRegisterToRegister(1, 0, registers);
    
    EXPECT_EQ(registers[1], 0x4);
    EXPECT_EQ(registers[0xF], 0x0);
}

TEST(InterpreterTest, addRegisterToRegisterAboveLimit) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 245;
    registers[1] = 20;

    addRegisterToRegister(1, 0, registers);
    
    EXPECT_EQ(registers[1], static_cast<std::uint8_t>(245+20));
    EXPECT_EQ(registers[0xF], 0x1);
}

TEST(InterpreterTest, subtractRegisterToRegisterNominal) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 20;
    registers[1] = 245;

    subtractRegisterToRegister(1, 0, registers);
    
    EXPECT_EQ(registers[1], 225);
    EXPECT_EQ(registers[0xF], 0x0);
}

TEST(InterpreterTest, subtractRegisterToRegisterBelowZero) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 245;
    registers[1] = 20;

    subtractRegisterToRegister(1, 0, registers);
    
    EXPECT_EQ(registers[1], static_cast<uint8_t>(20-245));
    EXPECT_EQ(registers[0xF], 0x1);
}

TEST(InterpreterTest, shiftRightLSBZero) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b00000010;

    shiftRight(0, registers);
    
    EXPECT_EQ(registers[0], 0b00000001);
    EXPECT_EQ(registers[0xF], 0x0);
}

TEST(InterpreterTest, shiftRightLSBOne) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b00000011;

    shiftRight(0, registers);
    
    EXPECT_EQ(registers[0], 0b00000001);
    EXPECT_EQ(registers[0xF], 0x1);
}

TEST(InterpreterTest, shiftLeftMSBZero) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b00000010;

    shiftLeft(0, registers);
    
    EXPECT_EQ(registers[0], 0b00000100);
    EXPECT_EQ(registers[0xF], 0x0);
}

TEST(InterpreterTest, shiftLeftMSBOne) {
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0b10000001;

    shiftLeft(0, registers);
    
    EXPECT_EQ(registers[0], 0b00000010);
    EXPECT_EQ(registers[0xF], 0x1);
}


TEST(InterpreterTest, JumpBecauseTwoRegistersAreNotEqual) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[1] = 0x3;
    registers[0] = 0x1;

    skipNextInstructionIfRegistersNotEqual(0, 1, registers, pc);

    EXPECT_EQ(pc, 0x6);
}

TEST(InterpreterTest, StoreInMemoryAddressRegister) {
    MemoryAddressRegister mem_add_reg(0x14);

    storeInMemoryAddressRegister(0x2, mem_add_reg);

    EXPECT_EQ(mem_add_reg, 0x2);
}

TEST(InterpreterTest, SetPCToValuePlusV0) {
    ProgramCounter pc(0x4);
    std::vector<GeneralRegister> registers(16);
    registers[0] = 0x1;

    setPCToV0PlusValue(0x2, registers, pc);

    EXPECT_EQ(pc, 0x3);
}
