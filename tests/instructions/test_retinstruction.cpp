#include <instructions/RETInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RetInstructionTest, DefaultConstructorNoOperands) {
    const auto ret = RETInstruction();

    EXPECT_EQ(true, ret.isCorrect());
    EXPECT_EQ("RET", ret.getName());
}

TEST(RetInstructionTest, DefaultConstructorOperandsTokens) {
    const auto ret = RETInstruction(VALID_OPERANDS_3_REGISTERS_CLASSIC);

    EXPECT_EQ(false, ret.isCorrect());
    EXPECT_EQ("RET", ret.getName());
}

TEST(RetInstructionTest, ExecuteValidState) {
    const auto ret = RETInstruction();
    auto engine = Engine();

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
    engine.pushStack(ALTERNATIVE_TEST_VALUE);
    ret.execute(engine);
    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE);
}
