#include <instructions/ADDInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(AddInstructionTest, DefaultConstructorNoOperands) {
    const auto add = ADDInstruction();

    EXPECT_EQ(false, add.isCorrect());
    EXPECT_EQ("ADD", add.getName());
}

TEST(AddInstructionTest, DefaultConstructorOperandsTokens) {
    const auto add = ADDInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(true, add.isCorrect());
    EXPECT_EQ("ADD", add.getName());
}

TEST(AddInstructionTest, ExecuteValidState) {
    const auto add = ADDInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);
}

TEST(AddInstructionTest, ExecuteValidState0RegisterResult) {
    const auto add = ADDInstruction(VALID_OPERANDS_3_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(AddInstructionTest, ExecuteValidState0RegisterOperandRight) {
    const auto add = ADDInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_RIGHT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE);
}

TEST(AddInstructionTest, ExecuteValidState0RegisterOperandLeft) {
    const auto add = ADDInstruction(VALID_OPERANDS_3_REGISTERS_0_OPERAND_LEFT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    add.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ALTERNATIVE_TEST_VALUE);
}