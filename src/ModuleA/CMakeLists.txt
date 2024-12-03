add_library(ModuleA SHARED
    ModuleA.cpp
    ModuleA.h
)

target_compile_definitions(ModuleA PRIVATE MODULEA_EXPORTS)

set_target_properties(ModuleA PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

install(TARGETS ModuleA
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
