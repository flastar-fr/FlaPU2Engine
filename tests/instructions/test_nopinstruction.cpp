#include <instructions/NOPInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(NopInstructionTest, DefaultConstructorNoOperands) {
    const auto nop = NOPInstruction();

    EXPECT_EQ(true, nop.isCorrect());
    EXPECT_EQ("NOP", nop.getName());
}

TEST(NopInstructionTest, DefaultConstructorOperandsTokens) {
    const auto nop = NOPInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(false, nop.isCorrect());
    EXPECT_EQ("NOP", nop.getName());
}
