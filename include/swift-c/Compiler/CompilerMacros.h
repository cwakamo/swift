//===-- CompilerMacros.h - Swift Compiler Library Macros ----------*- C -*-===//
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

#ifdef  __cplusplus
# define SWIFTCOMPILER_BEGIN_DECLS  extern "C" {
# define SWIFTCOMPILER_END_DECLS    }
#else
# define SWIFTCOMPILER_BEGIN_DECLS
# define SWIFTCOMPILER_END_DECLS
#endif

#ifndef SWIFTCOMPILER_PUBLIC
# ifdef _WIN32
#  ifdef libSwiftCompiler_EXPORTS
#    define SWIFTCOMPILER_PUBLIC __declspec(dllexport)
#  else
#    define SWIFTCOMPILER_PUBLIC __declspec(dllimport)
#  endif
# else
#  define SWIFTCOMPILER_PUBLIC
# endif
#endif
