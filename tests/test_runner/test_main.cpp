// UTF-8 with BOM
#include <gtest/gtest.h>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

// Define test factory function type
typedef void (*TestFactoryFunc)();

class TestLoader {
private:
    static std::vector<HMODULE> m_loadedDlls;

public:
    static bool LoadTestDlls() {
        // Get the path of the current executable
        WCHAR szExePath[MAX_PATH] = { 0 };
        if (GetModuleFileNameW(NULL, szExePath, MAX_PATH) == 0) {
            std::wcerr << L"Failed to get module path. Error: " << GetLastError() << std::endl;
            return false;
        }

        std::wstring binPath = std::wstring(szExePath);
        size_t lastSlash = binPath.find_last_of(L"\\");
        if (lastSlash != std::wstring::npos) {
            binPath = binPath.substr(0, lastSlash);
        }

        // Load test DLLs
        const wchar_t* testModules[] = {L"ModuleATest.dll", L"ModuleBTest.dll"};
        
        bool allLoaded = true;
        for (const wchar_t* module : testModules) {
            std::wstring dllPath = binPath + L"\\" + module;
            std::wcout << L"Loading DLL: " << dllPath << std::endl;
            HMODULE hDll = LoadLibraryW(dllPath.c_str());
            if (hDll) {
                // Get test registration function
                TestFactoryFunc registerTests = (TestFactoryFunc)GetProcAddress(hDll, "RegisterTests");
                if (registerTests) {
                    registerTests();  // Register test cases
                    m_loadedDlls.push_back(hDll);
                    std::wcout << L"Successfully loaded and registered tests from: " << module << std::endl;
                } else {
                    std::wcerr << L"Failed to get RegisterTests function from: " << module << std::endl;
                    FreeLibrary(hDll);
                    allLoaded = false;
                }
            } else {
                std::wcerr << L"Failed to load test DLL: " << module << std::endl;
                std::wcerr << L"Error code: " << GetLastError() << std::endl;
                allLoaded = false;
            }
        }
        return allLoaded;
    }

    static void UnloadTestDlls() {
        for (HMODULE hDll : m_loadedDlls) {
            FreeLibrary(hDll);
        }
        m_loadedDlls.clear();
    }

    static void ListTests() {
        const testing::UnitTest& unit_test = *testing::UnitTest::GetInstance();
        std::cout << "Available tests:\n";
        for (int i = 0; i < unit_test.total_test_suite_count(); ++i) {
            const testing::TestSuite* test_suite = unit_test.GetTestSuite(i);
            for (int j = 0; j < test_suite->total_test_count(); ++j) {
                const testing::TestInfo* test_info = test_suite->GetTestInfo(j);
                std::cout << test_suite->name() << "." << test_info->name() << "\n";
            }
        }
    }
};

// Static member variable definition
std::vector<HMODULE> TestLoader::m_loadedDlls;

void PrintHelp() {
    std::cout << "GTest Runner Help\n"
              << "================\n\n"
              << "Command Line Options:\n"
              << "------------------\n"
              << "1. Default Mode:\n"
              << "   test_runner.exe                       Run all tests\n\n"
              << "2. Google Test Native Options:\n"
              << "   --gtest_filter=TestSuite.TestCase     Run specific test\n"
              << "   --gtest_list_tests                    List all tests\n"
              << "   --gtest_repeat=N                      Repeat tests N times\n"
              << "   --gtest_output=xml:report.xml        Generate XML report\n"
              << "   --gtest_break_on_failure             Break on failure\n"
              << "   --gtest_catch_exceptions             Handle exceptions\n\n"
              << "3. Custom Options:\n"
              << "   --help                               Show this help message\n"
              << "   --list                               List all available tests\n"
              << "   --run <test_name>                    Run a specific test case\n"
              << "   --run-module <module>                Run all tests in a module\n\n"
              << "Examples:\n"
              << "--------\n"
              << "1. Run all tests:\n"
              << "   test_runner.exe\n\n"
              << "2. Run specific test with native option:\n"
              << "   test_runner.exe --gtest_filter=ModuleATest.AddTest\n\n"
              << "3. Run specific test with custom option:\n"
              << "   test_runner.exe --run ModuleATest.AddTest\n\n"
              << "4. Run all tests in ModuleA:\n"
              << "   test_runner.exe --run-module ModuleATest\n\n"
              << "5. Run tests with multiple options:\n"
              << "   test_runner.exe --run ModuleATest.AddTest --gtest_repeat=3\n\n"
              << "Notes:\n"
              << "-----\n"
              << "- Test names are case-sensitive\n"
              << "- Native and custom options can be mixed\n"
              << "- Use --list or --gtest_list_tests to see available tests\n"
              << "- Module names should be specified without the .dll extension\n"
              << "- For more GTest options, visit: https://google.github.io/googletest/\n";
}

void PrintUsage() {
    std::cout << "Usage:\n"
              << "1. Default Mode:\n"
              << "   test_runner.exe                       Run all tests\n\n"
              << "2. Google Test Native Options:\n"
              << "   --gtest_filter=<test_pattern>         Run specific test\n"
              << "   --gtest_list_tests                    List all tests\n\n"
              << "3. Custom Options:\n"
              << "   --help                               Show help message\n"
              << "   --list                               List available tests\n"
              << "   --run <test_name>                    Run specific test\n"
              << "   --run-module <module>                Run module tests\n\n"
              << "For more detailed information and examples, use: test_runner.exe --help\n";
}

int main(int argc, char** argv) {
    // First, load and register tests from DLLs
    if (!TestLoader::LoadTestDlls()) {
        std::cerr << "Failed to load test DLLs" << std::endl;
        return 1;
    }

    // Check for custom commands
    if (argc >= 2) {
        std::string command = argv[1];
        
        // Handle custom commands
        if (command == "--help") {
            PrintHelp();
            return 0;
        }
        
        if (command == "--list") {
            TestLoader::ListTests();
            return 0;
        }
        
        if ((command == "--run" && argc > 2) || (command == "--run-module" && argc > 2)) {
            // Prepare GTest arguments
            std::vector<char*> new_argv;
            new_argv.push_back(argv[0]);  // Program name

            std::string filter_arg_str;
            if (command == "--run") {
                std::string test_name = argv[2];
                std::cout << "Running test: " << test_name << std::endl;
                filter_arg_str = "--gtest_filter=" + test_name;
            } else {
                std::string module_name = argv[2];
                std::cout << "Running all tests in module: " << module_name << std::endl;
                filter_arg_str = "--gtest_filter=" + module_name + ".*";
            }
            
            char* filter_arg = new char[filter_arg_str.length() + 1];
            std::strcpy(filter_arg, filter_arg_str.c_str());
            new_argv.push_back(filter_arg);

            // Initialize GTest with modified arguments
            int new_argc = static_cast<int>(new_argv.size());
            testing::InitGoogleTest(&new_argc, new_argv.data());
            
            int result = RUN_ALL_TESTS();
            
            // Cleanup
            delete[] filter_arg;
            TestLoader::UnloadTestDlls();
            return result;
        }
    }

    // Default behavior: Initialize and run tests with original arguments
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    // Cleanup
    TestLoader::UnloadTestDlls();
    return result;
}
