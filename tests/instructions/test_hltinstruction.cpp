#include <instructions/HLTInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(HltInstructionTest, DefaultConstructorNoOperands) {
    const auto hlt = HLTInstruction();

    EXPECT_EQ(true, hlt.isCorrect());
    EXPECT_EQ("HLT", hlt.getName());
}

TEST(HltInstructionTest, DefaultConstructorOperandsTokens) {
    const auto hlt = HLTInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(false, hlt.isCorrect());
    EXPECT_EQ("HLT", hlt.getName());
}
