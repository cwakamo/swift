# Use an 'internal' name, this is still experimental.
set(SWIFT_COMPILER_LIB_NAME "_InternalSwiftCompiler")

set(LLVM_EXPORTED_SYMBOL_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/libSwiftCompiler.exports)

add_swift_host_library(libSwiftCompiler SHARED
  c-include-check.c
  libSwiftCompiler.cpp
  HAS_SWIFT_MODULES)

add_dependencies(libSwiftCompiler clang)

target_link_libraries(libSwiftCompiler PRIVATE
  swiftFrontendTool
  swiftCompilerModules
)

set_target_properties(libSwiftCompiler
  PROPERTIES
  OUTPUT_NAME ${SWIFT_COMPILER_LIB_NAME})

add_llvm_symbol_exports(libSwiftCompiler ${LLVM_EXPORTED_SYMBOL_FILE})

add_link_opts(libSwiftCompiler)

add_dependencies(compiler libSwiftCompiler)

swift_install_in_component(TARGETS libSwiftCompiler
  ARCHIVE DESTINATION "lib${LLVM_LIBDIR_SUFFIX}/swift/${SWIFT_SDK_${SWIFT_HOST_VARIANT_SDK}_LIB_SUBDIR}" COMPONENT compiler
  LIBRARY DESTINATION "lib${LLVM_LIBDIR_SUFFIX}/swift/${SWIFT_SDK_${SWIFT_HOST_VARIANT_SDK}_LIB_SUBDIR}" COMPONENT compiler
  RUNTIME DESTINATION "bin" COMPONENT compiler)
