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
              << "  --help                 Show this help message\n"
              << "  --list                 List all available tests\n"
              << "  --run <test_name>      Run a specific test case\n"
              << "  --run-module <module>  Run all tests in a specific module\n"
              << "  --run-all             Run all available tests\n\n"
              << "Examples:\n"
              << "--------\n"
              << "1. Show all available tests:\n"
              << "   test_runner.exe --list\n\n"
              << "2. Run a specific test:\n"
              << "   test_runner.exe --run ModuleATest.AddTest\n\n"
              << "3. Run all tests in ModuleA:\n"
              << "   test_runner.exe --run-module ModuleATest\n\n"
              << "4. Run all tests:\n"
              << "   test_runner.exe --run-all\n\n"
              << "Notes:\n"
              << "-----\n"
              << "- Test names are case-sensitive\n"
              << "- Use --list to see the exact names of available tests\n"
              << "- Module names should be specified without the .dll extension\n";
}

void PrintUsage() {
    std::cout << "Usage:\n"
              << "  test_runner.exe --help                  Show help information\n"
              << "  test_runner.exe --list                  List all available tests\n"
              << "  test_runner.exe --run <test_name>       Run a specific test\n"
              << "  test_runner.exe --run-module <module>   Run all tests in specified module\n"
              << "  test_runner.exe --run-all              Run all tests\n\n"
              << "For more detailed information, use: test_runner.exe --help\n";
}

int main(int argc, char** argv) {
    // First, load and register tests from DLLs
    if (!TestLoader::LoadTestDlls()) {
        std::cerr << "Failed to load test DLLs" << std::endl;
        return 1;
    }

    // if no command line arguments, run GTest
    if (argc < 2) {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    std::string command = argv[1];
    
    // Check for help command first
    if (command == "--help") {
        PrintHelp();
        return 0;
    }

    // Prepare command line arguments for GTest
    std::vector<char*> new_argv;
    new_argv.push_back(argv[0]);  // Program name

    // Handle test filter for specific test
    if ((command == "--run" && argc > 2) || (command == "--run-module" && argc > 2)) {
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
    }

    // Initialize GTest with modified arguments
    int new_argc = static_cast<int>(new_argv.size());
    testing::InitGoogleTest(&new_argc, new_argv.data());

    int result = 0;

    if (command == "--list") {
        TestLoader::ListTests();
    }
    else if ((command == "--run" && argc > 2) || (command == "--run-module" && argc > 2)) {
        result = RUN_ALL_TESTS();
    }
    else if (command == "--run-all") {
        result = RUN_ALL_TESTS();
    }
    else if (command != "--help") {  // Don't show usage if help was requested
        PrintUsage();
        result = 1;
    }
    
    // Clean up dynamically allocated memory
    if ((command == "--run" && argc > 2) || (command == "--run-module" && argc > 2)) {
        delete[] new_argv[1];
    }

    // Clean up
    TestLoader::UnloadTestDlls();
    
    return result;
}
