add_library(ModuleB SHARED
    ModuleB.cpp
    ModuleB.h
)

target_compile_definitions(ModuleB PRIVATE MODULEB_EXPORTS)

set_target_properties(ModuleB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

install(TARGETS ModuleB
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
