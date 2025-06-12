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

TEST(LdiInstructionTest, ExecuteValidState) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidState0Register) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_REGISTER);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(LdiInstructionTest, ExecuteValidState0Imm) {
    const auto ldi = LDIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    ldi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], NULL_VALUE);
}
