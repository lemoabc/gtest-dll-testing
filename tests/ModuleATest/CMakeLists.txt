add_library(ModuleATest SHARED
    ModuleATest.cpp
    ModuleATest.h
    gui/widget/button_test.cpp
    gui/menu/menu_test.cpp
)

target_compile_definitions(ModuleATest 
    PRIVATE 
    GTEST_LINKED_AS_SHARED_LIBRARY=1
    GTEST_CREATE_SHARED_LIBRARY=1
    GTEST_HAS_PTHREAD=0
)

# Add include directories for GTest
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ModuleATest
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(ModuleATest
    PRIVATE
    GTest::gtest
    ModuleA
)

set_target_properties(ModuleATest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

install(TARGETS ModuleATest
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)
