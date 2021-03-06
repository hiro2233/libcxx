// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef SUPPORT_DEMANGLE_H
#define SUPPORT_DEMANGLE_H

#include "test_macros.h"
#include <string>
#include <cstdlib>

#if !defined(TEST_HAS_NO_DEMANGLE)
# if defined(__GNUC__) || defined(__clang__)
#   if __has_include("cxxabi.h")
#     include "cxxabi.h"
#   else
#     define TEST_HAS_NO_DEMANGLE
#   endif
# else
#   define TEST_HAS_NO_DEMANGLE
# endif
#endif

#if defined(TEST_HAS_NO_DEMANGLE)
inline std::string demangle(const char* mangled_name) {
  return mangled_name;
}
#else
template <size_t N> struct Printer;
inline std::string demangle(const char* mangled_name) {
  int status = 0;
  std::string input(mangled_name);
  input.insert(0, "_Z");
  char* out = __cxxabiv1::__cxa_demangle(input.c_str(), nullptr, nullptr, &status);
  if (out != nullptr) {
    std::string res(out);
    std::free(out);
    return res;
  }
  return mangled_name;
}
#endif

#endif // SUPPORT_DEMANGLE_H
