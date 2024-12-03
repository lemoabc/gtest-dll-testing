#include "ModuleATest.h"
#include <gtest/gtest.h>
#include <vector>

namespace {
    // Store test cases in a global vector
    std::vector<testing::TestSuite*> g_testSuites;
}

void ModuleATest::SetUp() {
    // Setup code before each test
}

void ModuleATest::TearDown() {
    // Cleanup code after each test
}

TEST_F(ModuleATest, AddTest) {
    EXPECT_EQ(calc.Add(2, 3), 5);
    EXPECT_EQ(calc.Add(-1, 1), 0);
}

TEST_F(ModuleATest, SubtractTest) {
    EXPECT_EQ(calc.Subtract(5, 3), 2);
    EXPECT_EQ(calc.Subtract(1, 1), 0);
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
