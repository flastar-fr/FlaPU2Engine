#include <instructions/RORInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RorInstructionTest, DefaultConstructorNoOperands) {
    const auto ror = RORInstruction();

    EXPECT_EQ(false, ror.isCorrect());
    EXPECT_EQ("ROR", ror.getName());
}

TEST(RorInstructionTest, DefaultConstructorOperandsTokens) {
    const auto rsh = RORInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);

    EXPECT_EQ(true, rsh.isCorrect());
    EXPECT_EQ("ROR", rsh.getName());
}

TEST(RorInstructionTest, ExecuteValidState) {
    const auto ror = RORInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    ror.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ROR(ALTERNATIVE_TEST_VALUE, 1));
}

TEST(RorInstructionTest, ExecuteValidState0RegisterResult) {
    const auto ror = RORInstruction(VALID_OPERANDS_2_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    ror.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(RorInstructionTest, ExecuteValidState0RegisterOperand) {
    const auto ror = RORInstruction(VALID_OPERANDS_2_REGISTERS_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    ror.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}
