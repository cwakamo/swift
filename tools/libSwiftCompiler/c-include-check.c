// This file serves as a sanity check to ensure that the header is parseable
// from C and that no C++ code has sneaked in.

#include "swift-c/Compiler/Compiler.h"
typedef swiftcompiler_invocation_t _check_it_exists;
