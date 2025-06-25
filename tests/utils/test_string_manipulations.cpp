#include <gtest/gtest.h>

#include "common.hpp"
#include <utils/string_manipulations.cpp>

const std::string EXAMPLE_VALUE = "test value";
const std::string FIRST_PART_EXAMPLE_VALUE = "test";
const std::string SECOND_PART_EXAMPLE_VALUE = "value";
const std::string RANDOM_SPACES = "    \t";
const std::string UPPER_EXAMPLE_VALUE = "TEST VALUE";
const std::string NO_SPACE_EXAMPLE_VALUE = "testvalue";
const std::string EXAMPLE_VALUE_ALTERNATIVE = "test hello";
const std::string SECOND_PART_EXAMPLE_VALUE_ALTERNATIVE = "hello";
const std::string ANOTHER_NON_EXISTING_EXAMPLE_VALUE = "no";

TEST(LeftTrimTest, NoSpace) {
    const std::string str = EXAMPLE_VALUE;

    const auto trimmed_str = ltrim(str);

    EXPECT_EQ(str, trimmed_str);
}

TEST(LeftTrimTest, Space) {
    const std::string str = RANDOM_SPACES + EXAMPLE_VALUE;

    const auto trimmed_str = ltrim(str);

    EXPECT_EQ(EXAMPLE_VALUE, trimmed_str);
}

TEST(RightTrimTest, NoSpace) {
    const std::string str = EXAMPLE_VALUE;

    const auto trimmed_str = rtrim(str);

    EXPECT_EQ(str, trimmed_str);
}

TEST(RightTrimTest, Space) {
    const std::string str = EXAMPLE_VALUE + RANDOM_SPACES;

    const auto trimmed_str = rtrim(str);

    EXPECT_EQ(EXAMPLE_VALUE, trimmed_str);
}

TEST(TrimTest, NoSpace) {
    const std::string str = EXAMPLE_VALUE;

    const auto trimmed_str = trim(str);

    EXPECT_EQ(str, trimmed_str);
}

TEST(TrimTest, Space) {
    const std::string str = RANDOM_SPACES + EXAMPLE_VALUE + RANDOM_SPACES;

    const auto trimmed_str = trim(str);

    EXPECT_EQ(EXAMPLE_VALUE, trimmed_str);
}

TEST(SplitTest, NoDelimiterIn) {
    const std::string str = NO_SPACE_EXAMPLE_VALUE;

    const auto splitted_str = split(str, " ");

    EXPECT_EQ(1, splitted_str.size());
    EXPECT_EQ(str, splitted_str[0]);
}

TEST(SplitTest, DelimiterIn) {
    const std::string str = EXAMPLE_VALUE;

    const auto splitted_str = split(str, " ");

    EXPECT_EQ(2, splitted_str.size());
    EXPECT_EQ(FIRST_PART_EXAMPLE_VALUE, splitted_str[0]);
    EXPECT_EQ(SECOND_PART_EXAMPLE_VALUE, splitted_str[1]);
}

TEST(ReplaceTokenTest, NoFromIn) {
    std::string str = EXAMPLE_VALUE;

    replace_token(str, ANOTHER_NON_EXISTING_EXAMPLE_VALUE, SECOND_PART_EXAMPLE_VALUE_ALTERNATIVE);

    EXPECT_EQ(EXAMPLE_VALUE, str);
}

TEST(ReplaceTokenTest, FromIn) {
    std::string str = EXAMPLE_VALUE;

    replace_token(str, SECOND_PART_EXAMPLE_VALUE, SECOND_PART_EXAMPLE_VALUE_ALTERNATIVE);

    EXPECT_EQ(EXAMPLE_VALUE_ALTERNATIVE, str);
}

TEST(UpperTest, UpperText) {
    std::string str = EXAMPLE_VALUE;

    upper(str);

    EXPECT_EQ(UPPER_EXAMPLE_VALUE, str);
}

TEST(LowerTest, LowerText) {
    std::string str = UPPER_EXAMPLE_VALUE;

    lower(str);

    EXPECT_EQ(EXAMPLE_VALUE, str);
}