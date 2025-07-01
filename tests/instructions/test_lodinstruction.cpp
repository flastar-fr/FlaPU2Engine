#include <instructions/LODInstruction.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(LodInstructionTest, DefaultConstructorNoOperands) {
    const auto lod = LODInstruction();

    EXPECT_EQ(false, lod.isCorrect());
    EXPECT_EQ("LOD", lod.getName());
}

TEST(LodInstructionTest, DefaultConstructorOperandsTokensRegisters) {
    const auto lod = LODInstruction(VALID_OPERANDS_2_REGISTER_REGISTER_VALUE_CLASSIC);

    EXPECT_EQ(true, lod.isCorrect());
    EXPECT_EQ("LOD", lod.getName());
}

TEST(LodInstructionTest, DefaultConstructorOperandsTokensRegistersOffset) {
    const auto lod = LODInstruction(VALID_OPERANDS_3_REGISTER_REGISTER_VALUE_IMM_CLASSIC);

    EXPECT_EQ(true, lod.isCorrect());
    EXPECT_EQ("LOD", lod.getName());
}

TEST(LodInstructionTest, DefaultConstructorOperandsTokensImmediate) {
    const auto lod = LODInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);

    EXPECT_EQ(true, lod.isCorrect());
    EXPECT_EQ("LOD", lod.getName());
}

TEST(LodInstructionTest, DefaultConstructorOperandsTokensRegistersValuesHighLow) {
    const auto lod = LODInstruction(VALID_OPERANDS_3_REGISTER_1_REGISTER_REGISTER_VALUES_CLASSIC);

    EXPECT_EQ(true, lod.isCorrect());
    EXPECT_EQ("LOD", lod.getName());
}

TEST(LodInstructionTest, ExecuteValidStateRegister) {
    const auto lod = LODInstruction(VALID_OPERANDS_2_REGISTER_REGISTER_VALUE_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    memory[ALTERNATIVE_TEST_VALUE] = ALTERNATIVE_TEST_VALUE;

    lod.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}

TEST(LodInstructionTest, ExecuteValidStateRegisterOffset) {
    const auto lod = LODInstruction(VALID_OPERANDS_3_REGISTER_REGISTER_VALUE_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    const uint8_t offset = VALID_OPERANDS_3_REGISTER_REGISTER_VALUE_IMM_CLASSIC[2].value;
    memory[ALTERNATIVE_TEST_VALUE + offset] = ALTERNATIVE_TEST_VALUE;

    lod.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}

TEST(LodInstructionTest, ExecuteValidStateImmediate) {
    const auto lod = LODInstruction(VALID_OPERANDS_2_REGISTER_IMM_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    memory[ALTERNATIVE_TEST_VALUE] = ALTERNATIVE_TEST_VALUE;

    lod.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}

TEST(LodInstructionTest, ExecuteValidStateRegisterValuesHighLow) {
    const auto lod = LODInstruction(VALID_OPERANDS_3_REGISTER_1_REGISTER_REGISTER_VALUES_CLASSIC);
    auto engine = Engine();
    auto& registers = engine.getRegisters();
    auto& memory = engine.getMemory();

    registers[FIRST_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    registers[SECOND_REGISTER_TO_USE] = ALTERNATIVE_TEST_VALUE;
    memory[(ALTERNATIVE_TEST_VALUE << AMOUNT_BITS_PER_CELL) + ALTERNATIVE_TEST_VALUE] = ALTERNATIVE_TEST_VALUE;

    lod.execute(engine);

    EXPECT_EQ(registers[FIRST_REGISTER_TO_USE], ALTERNATIVE_TEST_VALUE);
}