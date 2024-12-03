#include "ModuleBTest.h"
#include <gtest/gtest.h>

class StringUtilSplitJoinTest : public ModuleBTest {
protected:
    void SetUp() override {
        ModuleBTest::SetUp();
    }
};

TEST_F(StringUtilSplitJoinTest, Split_WithCommaDelimiter_ReturnsParts) {
    auto parts = stringUtil.Split("one,two,three", ',');
    ASSERT_EQ(parts.size(), 3);
    EXPECT_EQ(parts[0], "one");
    EXPECT_EQ(parts[1], "two");
    EXPECT_EQ(parts[2], "three");
}

TEST_F(StringUtilSplitJoinTest, Split_WithEmptyParts_SkipsEmptyParts) {
    auto parts = stringUtil.Split("one,,three", ',');
    ASSERT_EQ(parts.size(), 2);
    EXPECT_EQ(parts[0], "one");
    EXPECT_EQ(parts[1], "three");
}

TEST_F(StringUtilSplitJoinTest, Split_WithNoDelimiter_ReturnsWholeString) {
    auto parts = stringUtil.Split("hello", ',');
    ASSERT_EQ(parts.size(), 1);
    EXPECT_EQ(parts[0], "hello");
}

TEST_F(StringUtilSplitJoinTest, Split_WithEmptyString_ReturnsEmptyVector) {
    auto parts = stringUtil.Split("", ',');
    EXPECT_TRUE(parts.empty());
}

TEST_F(StringUtilSplitJoinTest, Join_WithMultipleParts_ReturnsJoinedString) {
    std::vector<std::string> parts = {"one", "two", "three"};
    EXPECT_EQ(stringUtil.Join(parts, ","), "one,two,three");
}

TEST_F(StringUtilSplitJoinTest, Join_WithEmptyVector_ReturnsEmptyString) {
    std::vector<std::string> parts;
    EXPECT_EQ(stringUtil.Join(parts, ","), "");
}

TEST_F(StringUtilSplitJoinTest, Join_WithSinglePart_ReturnsPart) {
    std::vector<std::string> parts = {"hello"};
    EXPECT_EQ(stringUtil.Join(parts, ","), "hello");
}

TEST_F(StringUtilSplitJoinTest, Join_WithCustomDelimiter_UsesDelimiter) {
    std::vector<std::string> parts = {"one", "two", "three"};
    EXPECT_EQ(stringUtil.Join(parts, " - "), "one - two - three");
}
