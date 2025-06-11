#include <instructions/ANDInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(AndInstructionTest, DefaultConstructorNoOperands) {
    const auto andInstruction = ANDInstruction();

    EXPECT_EQ(false, andInstruction.isCorrect());
    EXPECT_EQ("AND", andInstruction.getName());
}

TEST(AndInstructionTest, DefaultConstructorOperandsTokens) {
    const auto andInstruction = ANDInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(true, andInstruction.isCorrect());
    EXPECT_EQ("AND", andInstruction.getName());
}

TEST(AndInstructionTest, ExecuteValidState) {
    const auto andInstruction = ANDInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    andInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE & ALTERNATIVE_TEST_VALUE);
}

TEST(AndInstructionTest, ExecuteValidState0RegisterResult) {
    const auto andInstruction = ANDInstruction(VALID_OPERANDS_3_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    andInstruction.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(AndInstructionTest, ExecuteValidState0RegisterOperandRight) {
    const auto andInstruction = ANDInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_RIGHT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    andInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}

TEST(AndInstructionTest, ExecuteValidState0RegisterOperandLeft) {
    const auto andInstruction = ANDInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_LEFT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    andInstruction.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}