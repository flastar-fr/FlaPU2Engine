#include <instructions/JMPInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(JmpInstructionTest, DefaultConstructorNoOperands) {
    const auto jmp = JMPInstruction();

    EXPECT_EQ(false, jmp.isCorrect());
    EXPECT_EQ("JMP", jmp.getName());
}

TEST(JmpInstructionTest, DefaultConstructorOperandsTokens) {
    const auto jmp = JMPInstruction(VALID_OPERANDS_1_IMM_CLASSIC);

    EXPECT_EQ(true, jmp.isCorrect());
    EXPECT_EQ("JMP", jmp.getName());
}

TEST(JmpInstructionTest, ExecuteValidState) {
    const auto jmp = JMPInstruction(VALID_OPERANDS_1_IMM_CLASSIC);
    auto engine = Engine();

    jmp.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
}

TEST(JmpInstructionTest, ExecuteValidState1HigherThanMaxInstructions) {
    const auto jmp = JMPInstruction(VALID_OPERANDS_1_IMM_1_HIGHER_THAN_MAX_INSTRUCTIONS);
    auto engine = Engine();

    jmp.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), MAX_AMOUNT_INSTRUCTIONS - 1);
}

TEST(JmpInstructionTest, ExecuteValidState2HigherThanMaxInstructions) {
    const auto jmp = JMPInstruction(VALID_OPERANDS_1_IMM_2_HIGHER_THAN_MAX_INSTRUCTIONS);
    auto engine = Engine();

    jmp.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}