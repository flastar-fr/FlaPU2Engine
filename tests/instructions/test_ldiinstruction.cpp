#include <instructions/LDIInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(LdiInstructionTest, DefaultConstructorNoOperands) {
    const auto ldi = LDIInstruction();

    EXPECT_EQ(false, ldi.isCorrect());
    EXPECT_EQ("LDI", ldi.getName());
}

TEST(LdiInstructionTest, DefaultConstructorOperandsTokens) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);

    EXPECT_EQ(true, ldi.isCorrect());
    EXPECT_EQ("LDI", ldi.getName());
}

TEST(LdiInstructionTest, ExecuteValidStateRegister) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidStateRegisterValue) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_VALUE_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTER_VALUE_IMM_CLASSIC[0].value] = registers.size() - 1;

    ldi.execute(engine);

    EXPECT_EQ(registers[registers.size() - 1], ALTERNATIVE_TEST_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidStateRegister0Register) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_REGISTER);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidStateRegister0Imm) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], NULL_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidStateRegisterValue0RegisterValue) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_VALUE_IMM_0_REGISTER);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidStateRegisterValue0Imm) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_VALUE_IMM_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTER_VALUE_IMM_0_OPERAND[0].value] = registers.size() - 1;

    ldi.execute(engine);

    EXPECT_EQ(registers[registers.size() - 1], NULL_VALUE);
}