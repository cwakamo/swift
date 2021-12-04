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

#include "swift/AST/DiagnosticConsumer.h"
#include "swift/AST/DiagnosticEngine.h"
#include "swift/AST/DiagnosticsFrontend.h"
#include "swift/Basic/LLVM.h"
#include "swift/Basic/InitializeLibSwift.h"
#include "swift/Frontend/Frontend.h"
#include "swift/FrontendTool/FrontendTool.h"
#include "swift-c/Compiler/Compiler.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

#include <vector>
#include <string>

using namespace swift;

struct swift_compiler_delegate_s {
  swift_compiler_diagnostic_handler_t diagnosticHandler;
};

swift_compiler_delegate_t swift_compiler_delegate_create(void) {
  return new swift_compiler_delegate_s;
}

void swift_compiler_delegate_dispose(swift_compiler_delegate_t delegate) {
  delete delegate;
}

void swift_compiler_delegate_set_diagnostic_handler(
  swift_compiler_delegate_t delegate,
  swift_compiler_diagnostic_handler_t diagnosticHandler) {
  delegate->diagnosticHandler = diagnosticHandler;  
}

struct swift_compiler_invocation_s {
  SmallVector<std::string, 256> Args;
};

swift_compiler_invocation_t swift_compiler_invocation_create(void) {
  return new swift_compiler_invocation_s;
}

void swift_compiler_invocation_dispose(swift_compiler_invocation_t invocation) {
  delete invocation;
}

void swift_compiler_invocation_set_frontend_arguments(
  swift_compiler_invocation_t invocation,
  int count, const char **args) {
  invocation->Args.clear();
  for (int i = 0; i < count; ++i) {
    invocation->Args.push_back(args[i]);
  }
}

void swift_compiler_invocation_set_driver_arguments(
  swift_compiler_invocation_t invocation,
  int count, const char **args) {
  swift_compiler_invocation_set_frontend_arguments(invocation, count, args);
}

namespace swift {
namespace compilerlib {
class DiagnosticConsumer : public swift::DiagnosticConsumer {
public:
  virtual void handleDiagnostic(SourceManager &SM,
                                const DiagnosticInfo &Info) override;
};
  
class FrontendObserver : public swift::FrontendObserver {
private:
  DiagnosticConsumer *CLDC;
public:
  FrontendObserver(DiagnosticConsumer *CLDC) : CLDC(CLDC) {};
  ~FrontendObserver() = default;
  
  void configuredCompiler(CompilerInstance &instance) override;
}; 
}
}

void compilerlib::DiagnosticConsumer::handleDiagnostic(SourceManager &SM,
  const DiagnosticInfo &Info)
{
  abort();
}

void compilerlib::FrontendObserver::configuredCompiler(
  CompilerInstance &instance)
{
  if (CLDC) {
    // Add our custom DiagnosticConsumer to the CompilerInstance.
    instance.getDiags().addConsumer(*CLDC);
  }
}

int swift_compiler_invokeFrontend(swift_compiler_invocation_t invocation,
                                  swift_compiler_delegate_t delegate)
{
  // This is done here and not done in FrontendTool.cpp, because
  // FrontendTool.cpp is linked to tools, which don't use libswift.
  initializeLibSwift();
 
  SmallVector<const char *, 256> argv;
  for (auto &arg : invocation->Args) {
    argv.push_back(arg.c_str());
  }
  
  compilerlib::DiagnosticConsumer CLDC;
  std::unique_ptr<compilerlib::FrontendObserver> Observer(
    new compilerlib::FrontendObserver(&CLDC));
  
  return performFrontend(argv, "swift-frontend",
    (void *)&swift_compiler_invokeFrontend, Observer.get());
}
