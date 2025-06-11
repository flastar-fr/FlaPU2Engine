#include <instructions/SUBInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"


TEST(SubInstructionTest, DefaultConstructorNoOperands) {
    const auto sub = SUBInstruction();

    EXPECT_EQ(false, sub.isCorrect());
    EXPECT_EQ("SUB", sub.getName());
}

TEST(SubInstructionTest, DefaultConstructorOperandsTokens) {
    const auto sub = SUBInstruction(VALID_OPERANDS_CLASSIC);

    EXPECT_EQ(true, sub.isCorrect());
    EXPECT_EQ("SUB", sub.getName());
}

TEST(SubInstructionTest, ExecuteValidState) {
    const auto sub = SUBInstruction(VALID_OPERANDS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    sub.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}

TEST(SubInstructionTest, ExecuteValidState0RegisterResult) {
    const auto sub = SUBInstruction(VALID_OPERANDS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    sub.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(SubInstructionTest, ExecuteValidState0RegisterOperandLeft) {
    const auto sub = SUBInstruction(VALID_OPERANDS_0_OPERAND_LEFT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    sub.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], -ALTERNATIVE_TEST_VALUE);
}

TEST(SubInstructionTest, ExecuteValidState0RegisterOperandRight) {
    const auto sub = SUBInstruction(VALID_OPERANDS_0_OPERAND_RIGHT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    sub.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE);
}
