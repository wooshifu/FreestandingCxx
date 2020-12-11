// -*- C++ -*-
//===--------------------------- __config ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once

#ifdef __cplusplus

#ifdef __GNUC__
#define _GNUC_VER (__GNUC__ * 100 + __GNUC_MINOR__)
// The _GNUC_VER_NEW macro better represents the new GCC versioning scheme
// introduced in GCC 5.0.
#define _GNUC_VER_NEW (_GNUC_VER * 10 + __GNUC_PATCHLEVEL__)
#else
#define _GNUC_VER     0
#define _GNUC_VER_NEW 0
#endif

#ifndef _LIBCPP_ABI_VERSION
#define _LIBCPP_ABI_VERSION 1
#endif

#ifndef _LIBCPP_STD_VER
#if __cplusplus <= 201103L
#define _LIBCPP_STD_VER 11
#elif __cplusplus <= 201402L
#define _LIBCPP_STD_VER 14
#elif __cplusplus <= 201703L
#define _LIBCPP_STD_VER 17
#else
#define _LIBCPP_STD_VER 18 // current year, or date of c++2a ratification
#endif
#endif // _LIBCPP_STD_VER

#define _LIBCPP_CONCAT1(_LIBCPP_X, _LIBCPP_Y) _LIBCPP_X##_LIBCPP_Y
#define _LIBCPP_CONCAT(_LIBCPP_X, _LIBCPP_Y)  _LIBCPP_CONCAT1(_LIBCPP_X, _LIBCPP_Y)

#ifndef _LIBCPP_ABI_NAMESPACE
#define _LIBCPP_ABI_NAMESPACE _LIBCPP_CONCAT(__, _LIBCPP_ABI_VERSION)
#endif

// '__is_identifier' returns '0' if '__x' is a reserved identifier provided by
// the compiler and '1' otherwise.
#ifndef __is_identifier
#define __is_identifier(__x) 1
#endif

#ifndef __has_declspec_attribute
#define __has_declspec_attribute(__x) 0
#endif

#define __has_keyword(__x) !(__is_identifier(__x))

#if defined(__clang__)
#define _LIBCPP_COMPILER_CLANG
#ifndef __apple_build_version__
#define _LIBCPP_CLANG_VER (__clang_major__ * 100 + __clang_minor__)
#endif
#elif defined(__GNUC__)
#define _LIBCPP_COMPILER_GCC
#elif defined(_MSC_VER)
#define _LIBCPP_COMPILER_MSVC
#elif defined(__IBMCPP__)
#define _LIBCPP_COMPILER_IBM
#endif

#if __has_attribute(__no_sanitize__) && !defined(_LIBCPP_COMPILER_GCC)
#define _LIBCPP_NO_CFI __attribute__((__no_sanitize__("cfi")))
#else
#define _LIBCPP_NO_CFI
#endif

#define _LIBCPP_PREFERRED_ALIGNOF(_Tp) __alignof(_Tp)

#if defined(_LIBCPP_COMPILER_CLANG)

#define _LIBCPP_ALWAYS_INLINE __attribute__((__always_inline__))

#elif defined(_LIBCPP_COMPILER_GCC)

#endif // _LIBCPP_COMPILER_[CLANG|GCC|MSVC|IBM]

#ifndef _LIBCPP_HIDDEN
#if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#define _LIBCPP_HIDDEN __attribute__((__visibility__("hidden")))
#else
#define _LIBCPP_HIDDEN
#endif
#endif

#ifndef _LIBCPP_FUNC_VIS
#if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#define _LIBCPP_FUNC_VIS __attribute__((__visibility__("default")))
#else
#define _LIBCPP_FUNC_VIS
#endif
#endif

#ifndef _LIBCPP_TEMPLATE_VIS
#if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#if __has_attribute(__type_visibility__)
#define _LIBCPP_TEMPLATE_VIS __attribute__((__type_visibility__("default")))
#else
#define _LIBCPP_TEMPLATE_VIS __attribute__((__visibility__("default")))
#endif
#else
#define _LIBCPP_TEMPLATE_VIS
#endif
#endif

#if __has_attribute(exclude_from_explicit_instantiation)
#define _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION __attribute__((__exclude_from_explicit_instantiation__))
#else
// Try to approximate the effect of exclude_from_explicit_instantiation
// (which is that entities are not assumed to be provided by explicit
// template instantiations in the dylib) by always inlining those entities.
#define _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION _LIBCPP_ALWAYS_INLINE
#endif
//
#ifndef _LIBCPP_HIDE_FROM_ABI
#if _LIBCPP_HIDE_FROM_ABI_PER_TU
#define _LIBCPP_HIDE_FROM_ABI _LIBCPP_HIDDEN _LIBCPP_INTERNAL_LINKAGE
#else
#define _LIBCPP_HIDE_FROM_ABI _LIBCPP_HIDDEN _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION
#endif
#endif

// Just so we can migrate to the new macros gradually.
#define _LIBCPP_INLINE_VISIBILITY _LIBCPP_HIDE_FROM_ABI

// Inline namespaces are available in Clang/GCC/MSVC regardless of C++ dialect.
#define _LIBCPP_BEGIN_NAMESPACE_STD                                                                                    \
  namespace std {                                                                                                      \
  inline namespace _LIBCPP_ABI_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD                                                                                      \
  }                                                                                                                    \
  }
#define _VSTD std::_LIBCPP_ABI_NAMESPACE
_LIBCPP_BEGIN_NAMESPACE_STD _LIBCPP_END_NAMESPACE_STD

#ifndef _LIBCPP_HAS_NO_NOEXCEPT
#define _NOEXCEPT     noexcept
#define _NOEXCEPT_(x) noexcept(x)
#else
#define _NOEXCEPT throw()
#define _NOEXCEPT_(x)
#endif

#ifdef _LIBCPP_CXX03_LANG
#define _LIBCPP_CONSTEXPR
#else
#define _LIBCPP_CONSTEXPR constexpr
#endif

// Macros to enter and leave a state where deprecation warnings are suppressed.
#if !defined(_LIBCPP_SUPPRESS_DEPRECATED_PUSH) && (defined(_LIBCPP_COMPILER_CLANG) || defined(_LIBCPP_COMPILER_GCC))
#define _LIBCPP_SUPPRESS_DEPRECATED_PUSH                                                                               \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
#define _LIBCPP_SUPPRESS_DEPRECATED_POP _Pragma("GCC diagnostic pop")
#endif
#if !defined(_LIBCPP_SUPPRESS_DEPRECATED_PUSH)
#define _LIBCPP_SUPPRESS_DEPRECATED_PUSH
#define _LIBCPP_SUPPRESS_DEPRECATED_POP
#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#define _LIBCPP_CONSTEXPR_AFTER_CXX14 constexpr
#else
#define _LIBCPP_CONSTEXPR_AFTER_CXX14
#endif

#if _LIBCPP_STD_VER > 17 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#define _LIBCPP_CONSTEXPR_AFTER_CXX17 constexpr
#else
#define _LIBCPP_CONSTEXPR_AFTER_CXX17
#endif

#if _LIBCPP_STD_VER > 14 && defined(__cpp_inline_variables) && (__cpp_inline_variables >= 201606L)
#define _LIBCPP_INLINE_VAR inline
#else
#define _LIBCPP_INLINE_VAR
#endif

#ifndef _LIBCPP_NODEBUG_TYPE
#if __has_attribute(__nodebug__) && (defined(_LIBCPP_CLANG_VER) && _LIBCPP_CLANG_VER >= 900)
#define _LIBCPP_NODEBUG_TYPE __attribute__((nodebug))
#else
#define _LIBCPP_NODEBUG_TYPE
#endif
#endif // !defined(_LIBCPP_NODEBUG_TYPE)

#endif // __cplusplus
