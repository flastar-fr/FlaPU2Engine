#include <instructions/XORInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(XorInstructionTest, DefaultConstructorNoOperands) {
    const auto xorInstruction = XORInstruction();

    EXPECT_EQ(false, xorInstruction.isCorrect());
    EXPECT_EQ("XOR", xorInstruction.getName());
}

TEST(XorInstructionTest, DefaultConstructorOperandsTokens) {
    const auto xorInstruction = XORInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(true, xorInstruction.isCorrect());
    EXPECT_EQ("XOR", xorInstruction.getName());
}

TEST(XorInstructionTest, ExecuteValidState) {
    const auto xorInstruction = XORInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    xorInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE ^ ALTERNATIVE_TEST_VALUE);
}

TEST(XorInstructionTest, ExecuteValidState0RegisterResult) {
    const auto xorInstruction = XORInstruction(VALID_OPERANDS_3_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    xorInstruction.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(XorInstructionTest, ExecuteValidState0RegisterOperandRight) {
    const auto xorInstruction = XORInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_RIGHT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    xorInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE);
}

TEST(XorInstructionTest, ExecuteValidState0RegisterOperandLeft) {
    const auto xorInstruction = XORInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_LEFT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    xorInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE);
}