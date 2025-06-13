#include <code_hardware/Engine.hpp>
#include <gtest/gtest.h>

#include "../common.hpp"

TEST(EngineTest, DefaultConstructor) {
    auto engine = Engine();

    EXPECT_EQ(engine.getRegisters().size(), DEFAULT_SIZE_REGISTERS);
    EXPECT_EQ(engine.getMemory().size(), DEFAULT_SIZE_MEMORY);
}

TEST(EngineTest, CustomSizeConstructor) {
    auto engine = Engine(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(engine.getRegisters().size(), DEFAULT_SIZE_REGISTERS);
    EXPECT_EQ(engine.getMemory().size(), ALTERNATIVE_TEST_VALUE);
}

TEST(EngineTest, MemoryManipulation) {
    auto engine = Engine();
    auto memory = engine.getMemory();

    memory[0] = ALTERNATIVE_TEST_VALUE;
    memory[1] = memory[0] + ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(memory[1], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);
}

TEST(EngineTest, RegistersManipulation) {
    auto engine = Engine();
    auto registers = engine.getRegisters();

    registers[0] = ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(registers[0], NULL_VALUE);

    registers[1] = registers[0] + ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);
}

TEST(EngineTest, ProgramCounterManipulation) {
    auto engine = Engine();

    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
    engine.incrementProgramCounter();
    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE + 1);
    engine.jump(ALTERNATIVE_TEST_VALUE);
    EXPECT_EQ(engine.getProgramCounter(), ALTERNATIVE_TEST_VALUE);
    engine.jump(MAX_AMOUNT_INSTRUCTIONS - 1);
    EXPECT_EQ(engine.getProgramCounter(), MAX_AMOUNT_INSTRUCTIONS - 1);
    engine.incrementProgramCounter();
    EXPECT_EQ(engine.getProgramCounter(), NULL_VALUE);
}
