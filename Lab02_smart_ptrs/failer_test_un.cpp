#include <gtest/gtest.h>
#include <iostream>
#include "un.hpp"

TEST(UniquePtrCopyConstructor, CompilationFailure) {
  UniquePtr<int> up(new int(3));
  UniquePtr<int> upCopy(up);
}

TEST(UniquePtrCopyAssignment, CompilationFailure) {
  UniquePtr<int> up(new int(3));
  UniquePtr<int> upCopy(new int(5));
  upCopy = up;
}