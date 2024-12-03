#include "ModuleBTest.h"
#include <gtest/gtest.h>

class StringUtilBasicTest : public ModuleBTest {
protected:
    void SetUp() override {
        ModuleBTest::SetUp();
    }
};

TEST_F(StringUtilBasicTest, Length_WithNullptr_ReturnsZero) {
    EXPECT_EQ(stringUtil.Length(nullptr), 0);
}

TEST_F(StringUtilBasicTest, Length_WithEmptyString_ReturnsZero) {
    EXPECT_EQ(stringUtil.Length(""), 0);
    EXPECT_EQ(stringUtil.Length(std::string()), 0);
}

TEST_F(StringUtilBasicTest, Length_WithNonEmptyString_ReturnsCorrectLength) {
    EXPECT_EQ(stringUtil.Length("Hello"), 5);
    EXPECT_EQ(stringUtil.Length(std::string("World")), 5);
}

TEST_F(StringUtilBasicTest, ToUpper_WithMixedCase_ReturnsUpperCase) {
    EXPECT_EQ(stringUtil.ToUpper("Hello World"), "HELLO WORLD");
    EXPECT_EQ(stringUtil.ToUpper("hello123"), "HELLO123");
}

TEST_F(StringUtilBasicTest, ToLower_WithMixedCase_ReturnsLowerCase) {
    EXPECT_EQ(stringUtil.ToLower("Hello World"), "hello world");
    EXPECT_EQ(stringUtil.ToLower("HELLO123"), "hello123");
}

TEST_F(StringUtilBasicTest, StartsWith_WithValidPrefix_ReturnsTrue) {
    EXPECT_TRUE(stringUtil.StartsWith("Hello World", "Hello"));
    EXPECT_TRUE(stringUtil.StartsWith("Hello", ""));
}

TEST_F(StringUtilBasicTest, StartsWith_WithInvalidPrefix_ReturnsFalse) {
    EXPECT_FALSE(stringUtil.StartsWith("Hello World", "World"));
    EXPECT_FALSE(stringUtil.StartsWith("Hello", "Hello World"));
}

TEST_F(StringUtilBasicTest, EndsWith_WithValidSuffix_ReturnsTrue) {
    EXPECT_TRUE(stringUtil.EndsWith("Hello World", "World"));
    EXPECT_TRUE(stringUtil.EndsWith("Hello", ""));
}

TEST_F(StringUtilBasicTest, EndsWith_WithInvalidSuffix_ReturnsFalse) {
    EXPECT_FALSE(stringUtil.EndsWith("Hello World", "Hello"));
    EXPECT_FALSE(stringUtil.EndsWith("World", "Hello World"));
}
