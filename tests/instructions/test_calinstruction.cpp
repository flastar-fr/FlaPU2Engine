#include <instructions/CALInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(CalInstructionTest, DefaultConstructorNoOperands) {
    const auto cal = CALInstruction();

    EXPECT_EQ(false, cal.isCorrect());
    EXPECT_EQ("CAL", cal.getName());
}

TEST(CalInstructionTest, DefaultConstructorOperandsTokens) {
    const auto cal = CALInstruction(VALID_OPERANDS_1_IMM_CLASSIC);

    EXPECT_EQ(true, cal.isCorrect());
    EXPECT_EQ("CAL", cal.getName());
}

TEST(CalInstructionTest, ExecuteValidState) {
    const auto cal = CALInstruction(VALID_OPERANDS_1_IMM_CLASSIC);
    auto engine = Engine();

    cal.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
    engine.pop_stack();
    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}
