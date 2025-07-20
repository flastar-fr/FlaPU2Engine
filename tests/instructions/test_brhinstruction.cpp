#include <instructions/BRHInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(BrhInstructionTest, DefaultConstructorNoOperands) {
    const auto brh = BRHInstruction();

    EXPECT_EQ(false, brh.isCorrect());
    EXPECT_EQ("BRH", brh.getName());
}

TEST(BrhInstructionTest, DefaultConstructorOperandsTokens) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_EQUALS);

    EXPECT_EQ(true, brh.isCorrect());
    EXPECT_EQ("BRH", brh.getName());
}

TEST(BrhInstructionTest, ExecuteValidStateEqualsValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({true, false, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
}

TEST(BrhInstructionTest, ExecuteValidStateEqualsNotValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}

TEST(BrhInstructionTest, ExecuteValidStateNotEqualsValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_NOT_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({false, true, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
}

TEST(BrhInstructionTest, ExecuteValidStateNotEqualsNotValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_NOT_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}

TEST(BrhInstructionTest, ExecuteValidStateGreaterEqualsValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_GREATER_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, true, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
}

TEST(BrhInstructionTest, ExecuteValidStateGreaterEqualsNotValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_GREATER_EQUALS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}

TEST(BrhInstructionTest, ExecuteValidStateLessValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_LESS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, false, true});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE - 1);
}

TEST(BrhInstructionTest, ExecuteValidStateLessNotValid) {
    const auto brh = BRHInstruction(VALID_OPERANDS_2_FLAG_IMM_CLASSIC_LESS);
    auto engine = Engine();

    engine.setFlagsStates({false, false, false, false});
    brh.execute(engine);

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}
