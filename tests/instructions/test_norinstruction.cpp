#include <instructions/NORInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(NorInstructionTest, DefaultConstructorNoOperands) {
    const auto nor = NORInstruction();

    EXPECT_EQ(false, nor.isCorrect());
    EXPECT_EQ("NOR", nor.getName());
}

TEST(NorInstructionTest, DefaultConstructorOperandsTokens) {
    const auto nor = NORInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(true, nor.isCorrect());
    EXPECT_EQ("NOR", nor.getName());
}

TEST(NorInstructionTest, ExecuteValidState) {
    const auto nor = NORInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    nor.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ~(ALTERNATIVE_TEST_VALUE | ALTERNATIVE_TEST_VALUE));
}

TEST(NorInstructionTest, ExecuteValidState0RegisterResult) {
    const auto nor = NORInstruction(VALID_OPERANDS_3_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    nor.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(NorInstructionTest, ExecuteValidState0RegisterOperandRight) {
    const auto nor = NORInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_RIGHT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    nor.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ~ALTERNATIVE_TEST_VALUE);
}

TEST(NorInstructionTest, ExecuteValidState0RegisterOperandLeft) {
    const auto nor = NORInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_LEFT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    nor.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ~ALTERNATIVE_TEST_VALUE);
}
