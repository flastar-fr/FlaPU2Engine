#include <instructions/RSHInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RshInstructionTest, DefaultConstructorNoOperands) {
    const auto add = RSHInstruction();

    EXPECT_EQ(false, add.isCorrect());
    EXPECT_EQ("RSH", add.getName());
}

TEST(RshInstructionTest, DefaultConstructorOperandsTokens) {
    const auto add = RSHInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);

    EXPECT_EQ(true, add.isCorrect());
    EXPECT_EQ("RSH", add.getName());
}

TEST(RshInstructionTest, ExecuteValidState) {
    const auto add = RSHInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE >> 1);
}

TEST(RshInstructionTest, ExecuteValidState0RegisterResult) {
    const auto add = RSHInstruction(VALID_OPERANDS_2_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(RshInstructionTest, ExecuteValidState0RegisterOperand) {
    const auto add = RSHInstruction(VALID_OPERANDS_2_REGISTERS_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}
