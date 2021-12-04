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

#include <stddef.h>
#include <stdint.h>

/// The version constants for the SwiftCompiler C API.
/// SWIFTCOMPILER_VERSION_MINOR should increase when there are API additions.
/// SWIFTCOMPILER_VERSION_MAJOR is intended for "major" source/ABI breaking
/// changes.
#define SWIFTCOMPILER_VERSION_MAJOR 0
#define SWIFTCOMPILER_VERSION_MINOR 1

SWIFTCOMPILER_BEGIN_DECLS

//--- ---//

typedef struct swift_compiler_diagnostic_s * swift_compiler_diagnostic_t;
typedef void(*swift_compiler_diagnostic_handler_t)(swift_compiler_diagnostic_t);

typedef struct {
  const char *file;
  size_t line;
  size_t column;
} swift_compiler_diagnostic_location_t;

typedef struct {
  swift_compiler_diagnostic_location_t location;
  size_t length;
} swift_compiler_diagnostic_range_t;

typedef struct {
  swift_compiler_diagnostic_range_t range;
  const char *replacement_text;
} swift_compiler_diagnostic_fixit_t;

typedef enum {
  swift_compiler_diagnostic_severity_error,
  swift_compiler_diagnostic_severity_warning,
  swift_compiler_diagnostic_severity_remark,
  swift_compiler_diagnostic_severity_note,
} swift_compiler_diagnostic_severity_t;

SWIFTCOMPILER_PUBLIC
swift_compiler_diagnostic_location_t
swift_compiler_diagnostic_get_location(swift_compiler_diagnostic_t diagnostic);

SWIFTCOMPILER_PUBLIC
swift_compiler_diagnostic_severity_t
swift_compiler_diagnostic_get_severity(swift_compiler_diagnostic_t diagnostic);

SWIFTCOMPILER_PUBLIC
const char *
swift_compiler_diagnostic_get_message(swift_compiler_diagnostic_t diagnostic);

SWIFTCOMPILER_PUBLIC
const char *
swift_compiler_diagnostic_get_format_string(
  swift_compiler_diagnostic_t diagnostic);

SWIFTCOMPILER_PUBLIC
const char *
swift_compiler_diagnostic_get_message_with_custom_format_string(
  swift_compiler_diagnostic_t diagnostic, const char *format_string);

SWIFTCOMPILER_PUBLIC
void
swift_compiler_diagnostic_get_ranges(swift_compiler_diagnostic_t diagnostic,
  size_t *outCount, swift_compiler_diagnostic_range_t **outRanges);

SWIFTCOMPILER_PUBLIC
void
swift_compiler_diagnostic_get_fixits(swift_compiler_diagnostic_t diagnostic,
  size_t *outCount, swift_compiler_diagnostic_fixit_t **outFixits);

SWIFTCOMPILER_PUBLIC
uint64_t
swift_compiler_diagnostic_get_id(swift_compiler_diagnostic_t diagnostic);

//--- ---//

typedef struct swift_compiler_delegate_s * swift_compiler_delegate_t;

SWIFTCOMPILER_PUBLIC
swift_compiler_delegate_t swift_compiler_delegate_create(void);

SWIFTCOMPILER_PUBLIC
void swift_compiler_delegate_dispose(swift_compiler_delegate_t delegate);

SWIFTCOMPILER_PUBLIC
void swift_compiler_delegate_set_diagnostic_handler(
  swift_compiler_delegate_t delegate,
  swift_compiler_diagnostic_handler_t diagnosticHandler);

//--- ---//

typedef struct swift_compiler_invocation_s * swift_compiler_invocation_t;

SWIFTCOMPILER_PUBLIC
swift_compiler_invocation_t swift_compiler_invocation_create(void);

SWIFTCOMPILER_PUBLIC
void swift_compiler_invocation_dispose(swift_compiler_invocation_t invocation);

SWIFTCOMPILER_PUBLIC
void swift_compiler_invocation_set_frontend_arguments(
  swift_compiler_invocation_t invocation, int count, const char **args);

SWIFTCOMPILER_PUBLIC
void swift_compiler_invocation_add_source_buffer(
  swift_compiler_invocation_t invocation, const char *file, const char *buffer);

//--- ---//

SWIFTCOMPILER_PUBLIC
int swift_compiler_invokeFrontend(swift_compiler_invocation_t invocation,
                                  swift_compiler_delegate_t delegate);
  
SWIFTCOMPILER_END_DECLS
