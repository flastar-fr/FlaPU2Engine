#include <code_hardware/Registers.hpp>
#include <gtest/gtest.h>

#include "common.hpp"

TEST(RegistersTest, Constructor) {
    const auto registers = Registers();

    EXPECT_EQ(registers.size(), DEFAULT_SIZE_REGISTERS);

    EXPECT_TRUE(registers[0].isNull());

    for (int i = 1; i < 16; ++i) {
        EXPECT_FALSE(registers[i].isNull());
    }
}

TEST(RegistersTest, CellsAssignations) {
    auto registers = Registers();

    registers[1] = ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);

    registers[2] = ALTERNATIVE_TEST_VALUE;
    EXPECT_EQ(registers[2], ALTERNATIVE_TEST_VALUE);
}

TEST(RegistersTest, OperationsWithMemoryCells) {
    auto registers = Registers();

    registers[1] = ALTERNATIVE_TEST_VALUE;
    registers[2] = ALTERNATIVE_TEST_VALUE;

    registers[3] = registers[1] + registers[2];
    EXPECT_EQ(registers[3], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);

    registers[3] = registers[1] - registers[2];
    EXPECT_EQ(registers[3], ALTERNATIVE_TEST_VALUE - ALTERNATIVE_TEST_VALUE);
}

TEST(RegistersTest, OperationsOnMemoryCellsNull) {
    auto registers = Registers();

    registers[1] = ALTERNATIVE_TEST_VALUE;
    registers[2] = ALTERNATIVE_TEST_VALUE;

    registers[0] = registers[1] + registers[2];
    EXPECT_EQ(registers[3], NULL);

    ++registers[0];
    EXPECT_EQ(registers[0], NULL_VALUE);
}

TEST(RegistersTest, OperationsWithMemoryCellsNull) {
    auto registers = Registers();

    registers[1] = ALTERNATIVE_TEST_VALUE;

    registers[1] = registers[0] + registers[1];
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);

    registers[1] = registers[0] + registers[1];
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);

    registers[1] += registers[0];
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);

    registers[1] -= registers[0];
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);

    ++registers[2];
    EXPECT_EQ(registers[2], 1);
}

TEST(RegistersTest, OperationSelfAssigns) {
    auto registers = Registers();

    registers[1] = ALTERNATIVE_TEST_VALUE;
    registers[2] = ALTERNATIVE_TEST_VALUE;
    registers[1] += registers[2];

    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE + ALTERNATIVE_TEST_VALUE);

    registers[1] = registers[1] - registers[2];
    EXPECT_EQ(registers[1], ALTERNATIVE_TEST_VALUE);
}

TEST(RegistersTest, AccessOutOfRange) {
    auto registers = Registers();

    EXPECT_THROW(registers[-1], std::out_of_range);
    EXPECT_THROW(registers[DEFAULT_SIZE_REGISTERS], std::out_of_range);
}
