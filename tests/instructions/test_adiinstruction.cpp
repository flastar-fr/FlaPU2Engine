#include <instructions/ADIInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(AdiInstructionTest, DefaultConstructorNoOperands) {
    const auto adi = ADIInstruction();

    EXPECT_EQ(false, adi.isCorrect());
    EXPECT_EQ("ADI", adi.getName());
}

TEST(AdiInstructionTest, DefaultConstructorOperandsTokens) {
    const auto ldi = ADIInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);

    EXPECT_EQ(true, ldi.isCorrect());
    EXPECT_EQ("ADI", ldi.getName());
}

TEST(AdiInstructionTest, ExecuteValidState) {
    const auto adi = ADIInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTER_IMM_CLASSIC[0].value] = ALTERNATIVE_TEST_VALUE;

    adi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);
}

TEST(AdiInstructionTest, ExecuteValidState0Register) {
    const auto adi = ADIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_REGISTER);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    adi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER], NULL_VALUE);
}

TEST(AdiInstructionTest, ExecuteValidState0Imm) {
    const auto adi = ADIInstruction(VALID_OPERANDS_2_REGISTER_IMM_0_OPERAND);
    auto engine = Engine();
    auto& registers = engine.getRegisters();

    registers[VALID_OPERANDS_2_REGISTER_IMM_CLASSIC[0].value] = ALTERNATIVE_TEST_VALUE;

    adi.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}
