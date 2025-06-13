#include <instructions/ROLInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RolInstructionTest, DefaultConstructorNoOperands) {
    const auto rol = ROLInstruction();

    EXPECT_EQ(false, rol.isCorrect());
    EXPECT_EQ("ROL", rol.getName());
}

TEST(RolInstructionTest, DefaultConstructorOperandsTokens) {
    const auto rsh = ROLInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);

    EXPECT_EQ(true, rsh.isCorrect());
    EXPECT_EQ("ROL", rsh.getName());
}

TEST(RolInstructionTest, ExecuteValidState) {
    const auto rol = ROLInstruction(VALID_OPERANDS_2_REGISTERS_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_3_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rol.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], ROL(ALTERNATIVE_TEST_VALUE, 1));
}

TEST(RolInstructionTest, ExecuteValidState0RegisterResult) {
    const auto rol = ROLInstruction(VALID_OPERANDS_2_REGISTERS_0_RESULT);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rol.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(RolInstructionTest, ExecuteValidState0RegisterOperand) {
    const auto rol = ROLInstruction(VALID_OPERANDS_2_REGISTERS_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[0].value] = ALTERNATIVE_TEST_VALUE;
    registers[VALID_OPERANDS_2_REGISTERS_0_RESULT[1].value] = ALTERNATIVE_TEST_VALUE;

    rol.execute(engine);

    EXPECT_EQ(registers[REGISTER_RESULT], NULL_VALUE);
}
