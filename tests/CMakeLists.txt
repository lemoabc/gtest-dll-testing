# 添加测试运行器
add_executable(test_runner
    test_runner/test_main.cpp
)

target_link_libraries(test_runner
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

set_target_properties(test_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS test_runner
    RUNTIME DESTINATION bin
)

# 添加测试模块
add_subdirectory(ModuleATest)
add_subdirectory(ModuleBTest)
