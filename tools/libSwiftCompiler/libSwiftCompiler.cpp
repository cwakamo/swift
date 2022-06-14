#include "swift/FrontendTool/FrontendTool.h"
#include "llvm/ADT/ArrayRef.h"

#include <vector>

using namespace swift;

extern "C" void swiftcompiler_foo(void) {
  std::vector<const char *> argv;
  
  (void)performFrontend(argv,
                        "swiftc",
                        (void *)&swiftcompiler_foo,
                        nullptr);
}
