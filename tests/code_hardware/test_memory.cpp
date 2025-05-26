#include <code_hardware/Memory.hpp>
#include <gtest/gtest.h>

#include "../common.hpp"

TEST(MemoryTest, DefaultConstructor) {
    const auto memory = Memory();

    EXPECT_EQ(memory.size(), DEFAULT_SIZE_MEMORY);
}

TEST(MemoryTest, CustomSizeConstructor) {
    const auto memory = Memory(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(memory.size(), ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryTest, OperationSelfAssigns) {
    auto memory = Memory();

    memory[1] = ALTERNATIVE_TEST_VALUE;
    memory[2] = ALTERNATIVE_TEST_VALUE;
    memory[1] += memory[2];

    EXPECT_EQ(memory[1], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);

    memory[1] = memory[1] - memory[2];
    EXPECT_EQ(memory[1], ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryTest, AccessOutOfRange) {
    auto memory = Memory();

    EXPECT_THROW(memory[-1], std::out_of_range);
    EXPECT_THROW(memory[DEFAULT_SIZE_MEMORY], std::out_of_range);
}

TEST(MemoryTest, CellsAssignations) {
    auto memory = Memory();

    memory[1] = ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(memory[1], ALTERNATIVE_TEST_VALUE);

    memory[2] = ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(memory[2], ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryTest, OperationsWithMemoryCells) {
    auto memory = Memory();

    memory[1] = ALTERNATIVE_TEST_VALUE;
    memory[2] = ALTERNATIVE_TEST_VALUE;

    memory[3] = memory[1] + memory[2];
    EXPECT_EQ(memory[3], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);

    memory[3] = memory[1] - memory[2];
    EXPECT_EQ(memory[3], ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);
}
