//===------------ libSwiftCompiler.cpp - Swift Compiler -------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2020 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// Implementation of the compiler C API
//
//===----------------------------------------------------------------------===//

#include "swift/DriverTool/DriverTool.h"
#include "swift-c/Compiler/Compiler.h"

int swift_compiler_invoke(int argc, const char **argv) {
  return swift::mainEntry(argc, argv);
}
