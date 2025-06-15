#include <instructions/STRInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(StrInstructionTest, DefaultConstructorNoOperands) {
    const auto str = STRInstruction();

    EXPECT_EQ(false, str.isCorrect());
    EXPECT_EQ("STR", str.getName());
}

TEST(StrInstructionTest, DefaultConstructorOperandsTokensRegisters) {
    const auto str = STRInstruction(VALID_OPERANDS_2_REGISTER_VALUES_CLASSIC);

    EXPECT_EQ(true, str.isCorrect());
    EXPECT_EQ("STR", str.getName());
}

TEST(StrInstructionTest, DefaultConstructorOperandsTokensRegistersOffset) {
    const auto str = STRInstruction(VALID_OPERANDS_3_REGISTER_VALUES_IMM_CLASSIC);

    EXPECT_EQ(true, str.isCorrect());
    EXPECT_EQ("STR", str.getName());
}

TEST(StrInstructionTest, DefaultConstructorOperandsTokensImmediate) {
    const auto str = STRInstruction(VALID_OPERANDS_2_IMM_REGISTER_VALUE_CLASSIC);

    EXPECT_EQ(true, str.isCorrect());
    EXPECT_EQ("STR", str.getName());
}

TEST(StrInstructionTest, ExecuteValidStateRegister) {
    const auto str = STRInstruction(VALID_OPERANDS_2_REGISTER_VALUES_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    const uint8_t address_memory = registers[FIRST_REGISTER_TO_USE].getValue();

    str.execute(engine);

    EXPECT_EQ(memory[address_memory], ALTERNATIVE_TEST_VALUE);
}

TEST(StrInstructionTest, ExecuteValidStateRegisterOffset) {
    const auto str = STRInstruction(VALID_OPERANDS_3_REGISTER_VALUES_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    const uint8_t address_memory = registers[FIRST_REGISTER_TO_USE].getValue();
    const uint8_t offset = VALID_OPERANDS_3_REGISTER_VALUES_IMM_CLASSIC[2].value;

    str.execute(engine);

    EXPECT_EQ(memory[address_memory + offset], ALTERNATIVE_TEST_VALUE);
}

TEST(StrInstructionTest, ExecuteValidStateImmediate) {
    const auto str = STRInstruction(VALID_OPERANDS_2_IMM_REGISTER_VALUE_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[FIRST_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;

    str.execute(engine);

    EXPECT_EQ(memory[ALTERNATIVE_TEST_VALUE], ALTERNATIVE_TEST_VALUE);
}
