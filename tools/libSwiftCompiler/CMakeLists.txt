set(SWIFT_COMPILER_LIB_NAME "SwiftCompiler")

set(LLVM_EXPORTED_SYMBOL_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/libSwiftCompiler.exports)

add_swift_host_library(libSwiftCompiler SHARED
  libSwiftCompiler.cpp
  c-include-check.c)

target_link_libraries(libSwiftCompiler PRIVATE
    swiftDriver
    swiftFrontendTool
    libswiftStub)

set_target_properties(libSwiftCompiler
    PROPERTIES
    OUTPUT_NAME ${SWIFT_COMPILER_LIB_NAME})

add_llvm_symbol_exports(libSwiftCompiler ${LLVM_EXPORTED_SYMBOL_FILE})

# Adds -dead_strip option
add_link_opts(libSwiftCompiler)

add_dependencies(compiler libSwiftCompiler)
swift_install_in_component(TARGETS libSwiftCompiler
  ARCHIVE DESTINATION "lib${LLVM_LIBDIR_SUFFIX}" COMPONENT compiler
  LIBRARY DESTINATION "lib${LLVM_LIBDIR_SUFFIX}" COMPONENT compiler
  RUNTIME DESTINATION "bin" COMPONENT compiler)

# TODO: Need to establish a way to make these headers go to local/include/swift-c instead
swift_install_in_component(DIRECTORY "${SWIFT_MAIN_INCLUDE_DIR}/swift-c/Compiler/"
                           DESTINATION "include/swift-c/Compiler"
                           COMPONENT compiler)
