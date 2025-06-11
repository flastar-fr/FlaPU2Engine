#include <instructions/RSHInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RshInstructionTest, DefaultConstructorNoOperands) {
    const auto rsh = RSHInstruction();

    EXPECT_EQ(false, rsh.isCorrect());
    EXPECT_EQ("RSH", rsh.getName());
}

TEST(RshInstructionTest, DefaultConstructorOperandsTokens) {
    const auto rsh = RSHInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);

    EXPECT_EQ(true, rsh.isCorrect());
    EXPECT_EQ("RSH", rsh.getName());
}

TEST(RshInstructionTest, ExecuteValidState) {
    const auto rsh = RSHInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rsh.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE / 2);
}

TEST(RshInstructionTest, ExecuteValidState0RegisterResult) {
    const auto rsh = RSHInstruction(VALID_OPERANDS_2_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rsh.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(RshInstructionTest, ExecuteValidState0RegisterOperand) {
    const auto rsh = RSHInstruction(VALID_OPERANDS_2_REGISTERS_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rsh.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}
