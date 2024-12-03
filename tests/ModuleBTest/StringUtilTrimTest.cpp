#include "ModuleBTest.h"
#include <gtest/gtest.h>

class StringUtilTrimTest : public ModuleBTest {
protected:
    void SetUp() override {
        ModuleBTest::SetUp();
    }
};

TEST_F(StringUtilTrimTest, Trim_WithWhitespaceOnBothEnds_RemovesWhitespace) {
    EXPECT_EQ(stringUtil.Trim("  Hello World  "), "Hello World");
    EXPECT_EQ(stringUtil.Trim("\t\nHello\t\n"), "Hello");
}

TEST_F(StringUtilTrimTest, Trim_WithNoWhitespace_ReturnsSameString) {
    EXPECT_EQ(stringUtil.Trim("Hello"), "Hello");
}

TEST_F(StringUtilTrimTest, Trim_WithOnlyWhitespace_ReturnsEmptyString) {
    EXPECT_EQ(stringUtil.Trim("   "), "");
    EXPECT_EQ(stringUtil.Trim("\t\n\r"), "");
}

TEST_F(StringUtilTrimTest, TrimLeft_WithWhitespace_RemovesLeftWhitespace) {
    EXPECT_EQ(stringUtil.TrimLeft("  Hello World  "), "Hello World  ");
    EXPECT_EQ(stringUtil.TrimLeft("\t\nHello"), "Hello");
}

TEST_F(StringUtilTrimTest, TrimLeft_WithNoLeftWhitespace_ReturnsSameString) {
    EXPECT_EQ(stringUtil.TrimLeft("Hello  "), "Hello  ");
}

TEST_F(StringUtilTrimTest, TrimRight_WithWhitespace_RemovesRightWhitespace) {
    EXPECT_EQ(stringUtil.TrimRight("  Hello World  "), "  Hello World");
    EXPECT_EQ(stringUtil.TrimRight("Hello\t\n"), "Hello");
}

TEST_F(StringUtilTrimTest, TrimRight_WithNoRightWhitespace_ReturnsSameString) {
    EXPECT_EQ(stringUtil.TrimRight("  Hello"), "  Hello");
}
