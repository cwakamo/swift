//===-- Compiler.h - Swift Compiler Library -----------------------*- C -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2021 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "CompilerMacros.h"

/// The version constants for the SwiftCompiler C API.
/// SWIFTCOMPILER_VERSION_MINOR should increase when there are API additions.
/// SWIFTCOMPILER_VERSION_MAJOR is intended for "major" source/ABI breaking changes.
#define SWIFTCOMPILER_VERSION_MAJOR 0
#define SWIFTCOMPILER_VERSION_MINOR 1

SWIFTCOMPILER_BEGIN_DECLS
  
SWIFTCOMPILER_PUBLIC
int swift_compiler_invoke(int argc, const char **argv);
  
SWIFTCOMPILER_END_DECLS
