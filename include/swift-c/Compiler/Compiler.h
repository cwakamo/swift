//===--- Compiler.h - C API for Swift Compilation -----------------*- C -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2022 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This C API serves as a programmatic interface to invoking the Swift
// compiler in-process. With limited exceptions, it provides means to
// observe the compilation process (including things like diagnostics),
// but it is not intended to provide a full-fledged interface to allow
// for manipulation of the Swift compiler pipeline.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_C_COMPILER_H
#define SWIFT_C_COMPILER_H

#include "CompilerMacros.h"

#include <stdint.h>

/// The version constants for the SwiftCompiler C API.
/// SWIFTCOMPILER_VERSION_MINOR should increase when there are API additions.
/// SWIFTCOMPILER_VERSION_MAJOR is intended for "major" source/ABI breaking
/// changes.
#define SWIFTCOMPILER_VERSION_MAJOR 0
#define SWIFTCOMPILER_VERSION_MINOR 1

SWIFTCOMPILER_BEGIN_DECLS

//=== Types ---------------------------------------------------------------===//

typedef struct swiftcompiler_invocation_s *swiftcompiler_invocation_t;
typedef struct swiftcompiler_diagnostic_s *swiftcompiler_diagnostic_t;

typedef struct swiftcompiler_observer_s {
  void(*handleDiagnostic)(void *context, swiftcompiler_diagnostic_t diagnostic);
  void(*disposeContext)(void *context);
} swiftcompiler_observer_t;

//=== Initialization ------------------------------------------------------===//

/// Initializes the Swift compiler library for use.
/// Must be called before calling any other API in this library.
SWIFTCOMPILER_PUBLIC void swiftcompiler_initialize(void);

//=== Invocation ----------------------------------------------------------===//

SWIFTCOMPILER_PUBLIC swiftcompiler_invocation_t
swiftcompiler_invocation_create(void);

SWIFTCOMPILER_PUBLIC void
swiftcompiler_invocation_set_argv(swiftcompiler_invocation_t invocation,
                                  int argc, const char **argv);

SWIFTCOMPILER_PUBLIC void
swiftcompiler_invocation_set_observer(swiftcompiler_invocation_t invocation,
                                      swiftcompiler_observer_t observer,
                                      void *context);

SWIFTCOMPILER_PUBLIC void
swiftcompiler_invocation_add_remapped_source_file(
  swiftcompiler_invocation_t invocation,
  const char *file,
  const char *contents);

SWIFTCOMPILER_PUBLIC void
swiftcompiler_invocation_dispose(swiftcompiler_invocation_t invocation);

/// Invokes the Swift compiler with the given \c swiftcompiler_invocation_t .
SWIFTCOMPILER_PUBLIC int
swiftcompiler_invoke_compiler(swiftcompiler_invocation_t invocation);

//=== Diagnostics ---------------------------------------------------------===//

typedef enum {
  swiftcompiler_diagnostic_severity_error = 0,
  swiftcompiler_diagnostic_severity_warning,
  swiftcompiler_diagnostic_severity_note,
  swiftcompiler_diagnostic_severity_remark,
} swiftcompiler_diagnostic_severity_t;

typedef struct {
  const char *file;
  uint64_t line;
  uint64_t column;
} swiftcompiler_diagnostic_location_t;

typedef struct {
  swiftcompiler_diagnostic_location_t location;
  uint64_t length;
} swiftcompiler_diagnostic_range_t;

typedef struct {
  swiftcompiler_diagnostic_range_t range;
  const char *replacement_text;
} swiftcompiler_diagnostic_fixit_t;

SWIFTCOMPILER_PUBLIC swiftcompiler_diagnostic_location_t
swiftcompiler_diagnostic_get_location(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC swiftcompiler_diagnostic_severity_t
swiftcompiler_diagnostic_get_severity(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC uint64_t
swiftcompiler_diagnostic_get_range_count(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC swiftcompiler_diagnostic_range_t
swiftcompiler_diagnostic_get_range_at_index(swiftcompiler_diagnostic_t,
                                            uint64_t index);

SWIFTCOMPILER_PUBLIC uint64_t
swiftcompiler_diagnostic_get_fixit_count(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC swiftcompiler_diagnostic_fixit_t
swiftcompiler_diagnostic_get_fixit_at_index(swiftcompiler_diagnostic_t,
                                            uint64_t index);

SWIFTCOMPILER_PUBLIC const char *
swiftcompiler_diagnostic_get_message(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC const char *
swiftcompiler_diagnostic_get_message_format(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_PUBLIC const char *
swiftcompiler_diagnostic_create_message_with_format(swiftcompiler_diagnostic_t,
                                                    const char *message_format,
                                                    const char *open_quote_mark,
                                                    const char *close_quote_mark,
                                                    const char *aka_format,
                                                    const char *opaque_format);

SWIFTCOMPILER_PUBLIC uint64_t
swiftcompiler_diagnostic_get_id(swiftcompiler_diagnostic_t);

SWIFTCOMPILER_END_DECLS

#endif // SWIFT_C_COMPILER_H