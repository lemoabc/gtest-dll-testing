#include "ModuleBTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace {
    // Store test cases in a global vector
    std::vector<testing::TestSuite*> g_testSuites;
}

void ModuleBTest::SetUp() {
    // Setup code before each test
}

void ModuleBTest::TearDown() {
    // Cleanup code after each test
}

TEST_F(ModuleBTest, IsEmpty_WithNullptr_ReturnsTrue) {
    EXPECT_TRUE(stringUtil.IsEmpty(nullptr));
}

TEST_F(ModuleBTest, IsEmpty_WithEmptyString_ReturnsTrue) {
    EXPECT_TRUE(stringUtil.IsEmpty(""));
}

TEST_F(ModuleBTest, IsEmpty_WithNonEmptyString_ReturnsFalse) {
    EXPECT_FALSE(stringUtil.IsEmpty("Hello"));
}

TEST_F(ModuleBTest, IsEmpty_WithSingleCharacter_ReturnsFalse) {
    EXPECT_FALSE(stringUtil.IsEmpty("a"));
}

// Function to get all test suites
std::vector<testing::TestSuite*> GetTestSuites() {
    std::vector<testing::TestSuite*> testSuites;
    const testing::UnitTest& unitTest = *testing::UnitTest::GetInstance();
    
    for (int i = 0; i < unitTest.total_test_suite_count(); ++i) {
        testSuites.push_back(const_cast<testing::TestSuite*>(unitTest.GetTestSuite(i)));
    }
    return testSuites;
}

// Export test registration function
extern "C" __declspec(dllexport) void RegisterTests() {
    // Force the linker to include the test cases
    g_testSuites = GetTestSuites();
}
