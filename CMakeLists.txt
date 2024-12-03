cmake_minimum_required(VERSION 3.20)
project(TestProject VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用测试
enable_testing()

# Set GTest options before downloading
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib." FORCE)

# 下载并构建 GTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

# 设置安装路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory" FORCE)
endif()

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)
