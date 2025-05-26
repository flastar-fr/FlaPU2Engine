#include <code_hardware/MemoryCellNull.hpp>
#include <gtest/gtest.h>

#include "../common.hpp"
#include "code_hardware/MemoryCell.hpp"


TEST(MemoryCellNullTest, Constructor) {
    const auto cell_default_contructor = MemoryCellNull();

    EXPECT_EQ(cell_default_contructor, NULL_VALUE);

    const auto cell_value_constructor = MemoryCellNull(MemoryCell(ALTERNATIVE_TEST_VALUE));
    EXPECT_EQ(cell_value_constructor, NULL_VALUE);
}

TEST(MemoryCellNullTest, Assign) {
    auto cell_uint = MemoryCellNull();

    cell_uint = ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_uint, NULL_VALUE);

    auto cell_memory_cell = MemoryCellNull();

    cell_memory_cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_memory_cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, Increments) {
    auto cell = MemoryCellNull();

    cell++;

    EXPECT_EQ(cell, NULL_VALUE);

    ++cell;

    EXPECT_EQ(cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, Decrements) {
    auto cell = MemoryCellNull();

    cell--;

    EXPECT_EQ(cell, NULL_VALUE);

    --cell;

    EXPECT_EQ(cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, SelfAddition) {
    auto cell_int = MemoryCellNull();

    cell_int += ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, NULL_VALUE);

    auto cell_other_memory = MemoryCellNull();

    cell_other_memory += MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_memory, NULL_VALUE);
}

TEST(MemoryCellNullTest, SelfSubstraction) {
    auto cell_int = MemoryCellNull();

    cell_int -= ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, NULL_VALUE);

    auto cell_other_cell = MemoryCellNull();

    cell_other_cell -= MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, OtherAddition) {
    auto cell_int = MemoryCellNull();

    cell_int = cell_int + ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, NULL_VALUE);

    auto cell_other_cell = MemoryCellNull();

    cell_other_cell = cell_other_cell + MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, OtherSubstraction) {
    auto cell_int = MemoryCellNull();

    cell_int = cell_int - ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, NULL_VALUE);

    auto cell_other_cell = MemoryCellNull();

    cell_other_cell = cell_other_cell - MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, NULL_VALUE);
}

TEST(MemoryCellNullTest, StreamOutput) {
    const auto cell = MemoryCellNull();

    std::ostringstream stream_default;
    stream_default << cell;

    EXPECT_EQ(stream_default.str(), std::to_string(NULL_VALUE));
}

TEST(MemoryCellNullTest, IsNull) {
    const auto cell = MemoryCellNull();

    EXPECT_TRUE(cell.isNull());
}

TEST(MemoryCellNullTest, OperationWithCellNull) {
    const MemoryCell cell = MemoryCellNull() + MemoryCell(ALTERNATIVE_TEST_VALUE);
    EXPECT_EQ(cell, ALTERNATIVE_TEST_VALUE);
}
