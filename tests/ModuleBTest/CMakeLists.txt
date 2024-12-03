add_library(ModuleBTest SHARED
    ModuleBTest.cpp
    StringUtilBasicTest.cpp
    StringUtilTrimTest.cpp
    StringUtilSplitJoinTest.cpp
    ModuleBTest.h
)

target_compile_definitions(ModuleBTest 
    PRIVATE 
    GTEST_LINKED_AS_SHARED_LIBRARY=1
    GTEST_CREATE_SHARED_LIBRARY=1
    GTEST_HAS_PTHREAD=0
)

# Add include directories for GTest
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ModuleBTest
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(ModuleBTest
    PRIVATE
    GTest::gtest
    ModuleB
)

set_target_properties(ModuleBTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

install(TARGETS ModuleBTest
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)