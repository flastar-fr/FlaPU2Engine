#include <gtest/gtest.h>

#include "common.hpp"
#include "MemoryCell.hpp"

uint8_t DEFAULT_VALUE = 0;

TEST(MemoryCellTest, Constructor) {
    const auto cell_default_contructor = MemoryCell();

    EXPECT_EQ(cell_default_contructor, DEFAULT_VALUE);

    const auto cell_value_constructor = MemoryCell(ALTERNATIVE_TEST_VALUE);
    EXPECT_EQ(cell_value_constructor, ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, Assign) {
    auto cell = MemoryCell();

    cell = ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell, ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, Increments) {
    auto cell = MemoryCell();

    cell++;

    EXPECT_EQ(cell, DEFAULT_VALUE + 1);

    ++cell;

    EXPECT_EQ(cell, DEFAULT_VALUE + 2);
}

TEST(MemoryCellTest, Decrements) {
    auto cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    cell--;

    EXPECT_EQ(cell, ALTERNATIVE_TEST_VALUE - 1);

    --cell;

    EXPECT_EQ(cell, ALTERNATIVE_TEST_VALUE - 2);
}

TEST(MemoryCellTest, SelfAddition) {
    auto cell_int = MemoryCell();

    cell_int += ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, DEFAULT_VALUE + ALTERNATIVE_TEST_VALUE);

    auto cell_other_memory = MemoryCell();

    cell_other_memory += MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_memory, DEFAULT_VALUE + ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, SelfSubstraction) {
    auto cell_int = MemoryCell(ALTERNATIVE_TEST_VALUE);

    cell_int -= ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);

    auto cell_other_cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    cell_other_cell -= MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, OtherAddition) {
    auto cell_int = MemoryCell();

    cell_int = cell_int + ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, DEFAULT_VALUE + ALTERNATIVE_TEST_VALUE);

    auto cell_other_cell = MemoryCell();

    cell_other_cell = cell_other_cell + MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, DEFAULT_VALUE + ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, OtherSubstraction) {
    auto cell_int = MemoryCell(ALTERNATIVE_TEST_VALUE);

    cell_int = cell_int - ALTERNATIVE_TEST_VALUE;

    EXPECT_EQ(cell_int, ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);

    auto cell_other_cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    cell_other_cell = cell_other_cell - MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell_other_cell, ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, StreamOutput) {
    const auto cell_default = MemoryCell();

    std::ostringstream stream_default;
    stream_default << cell_default;

    EXPECT_EQ(stream_default.str(), std::to_string(DEFAULT_VALUE));

    const auto cell_alternative = MemoryCell(ALTERNATIVE_TEST_VALUE);

    std::ostringstream stream_alternative;
    stream_alternative << cell_alternative;

    EXPECT_EQ(stream_alternative.str(), std::to_string(ALTERNATIVE_TEST_VALUE));
}


TEST(MemoryCellTest, IsNull) {
    const auto cell = MemoryCell();

    EXPECT_FALSE(cell.isNull());
}

TEST(MemoryCellTest, Equalities) {
    const auto cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(cell, MemoryCell(ALTERNATIVE_TEST_VALUE));
    EXPECT_EQ(cell, ALTERNATIVE_TEST_VALUE);
}

TEST(MemoryCellTest, UnitarySubstraction) {
    const auto cell = MemoryCell(ALTERNATIVE_TEST_VALUE);

    EXPECT_EQ(-cell, -ALTERNATIVE_TEST_VALUE);
}
