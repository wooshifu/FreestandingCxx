// -*- C++ -*-
//===------------------------ type_traits ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once

/*
    type_traits synopsis

namespace std
{

    // helper class:
    template <class T, T v> struct integral_constant;
    typedef integral_constant<bool, true>  true_type;   // C++11
    typedef integral_constant<bool, false> false_type;  // C++11

    template <bool B>                                   // C++14
    using bool_constant = integral_constant<bool, B>;   // C++14
    typedef bool_constant<true> true_type;              // C++14
    typedef bool_constant<false> false_type;            // C++14

    // helper traits
    template <bool, class T = void> struct enable_if;
    template <bool, class T, class F> struct conditional;

    // Primary classification traits:
    template <class T> struct is_void;
    template <class T> struct is_null_pointer;  // C++14
    template <class T> struct is_integral;
    template <class T> struct is_floating_point;
    template <class T> struct is_array;
    template <class T> struct is_pointer;
    template <class T> struct is_lvalue_reference;
    template <class T> struct is_rvalue_reference;
    template <class T> struct is_member_object_pointer;
    template <class T> struct is_member_function_pointer;
    template <class T> struct is_enum;
    template <class T> struct is_union;
    template <class T> struct is_class;
    template <class T> struct is_function;

    // Secondary classification traits:
    template <class T> struct is_reference;
    template <class T> struct is_arithmetic;
    template <class T> struct is_fundamental;
    template <class T> struct is_member_pointer;
    template <class T> struct is_scalar;
    template <class T> struct is_object;
    template <class T> struct is_compound;

    // Const-volatile properties and transformations:
    template <class T> struct is_const;
    template <class T> struct is_volatile;
    template <class T> struct remove_const;
    template <class T> struct remove_volatile;
    template <class T> struct remove_cv;
    template <class T> struct add_const;
    template <class T> struct add_volatile;
    template <class T> struct add_cv;

    // Reference transformations:
    template <class T> struct remove_reference;
    template <class T> struct add_lvalue_reference;
    template <class T> struct add_rvalue_reference;

    // Pointer transformations:
    template <class T> struct remove_pointer;
    template <class T> struct add_pointer;

    template<class T> struct type_identity;                     // C++20
    template<class T>
      using type_identity_t = typename type_identity<T>::type;  // C++20

    // Integral properties:
    template <class T> struct is_signed;
    template <class T> struct is_unsigned;
    template <class T> struct make_signed;
    template <class T> struct make_unsigned;

    // Array properties and transformations:
    template <class T> struct rank;
    template <class T, unsigned I = 0> struct extent;
    template <class T> struct remove_extent;
    template <class T> struct remove_all_extents;

    template <class T> struct is_bounded_array;                 // C++20
    template <class T> struct is_unbounded_array;               // C++20

    // Member introspection:
    template <class T> struct is_pod;
    template <class T> struct is_trivial;
    template <class T> struct is_trivially_copyable;
    template <class T> struct is_standard_layout;
    template <class T> struct is_literal_type;
    template <class T> struct is_empty;
    template <class T> struct is_polymorphic;
    template <class T> struct is_abstract;
    template <class T> struct is_final; // C++14
    template <class T> struct is_aggregate; // C++17

    template <class T, class... Args> struct is_constructible;
    template <class T>                struct is_default_constructible;
    template <class T>                struct is_copy_constructible;
    template <class T>                struct is_move_constructible;
    template <class T, class U>       struct is_assignable;
    template <class T>                struct is_copy_assignable;
    template <class T>                struct is_move_assignable;
    template <class T, class U>       struct is_swappable_with;       // C++17
    template <class T>                struct is_swappable;            // C++17
    template <class T>                struct is_destructible;

    template <class T, class... Args> struct is_trivially_constructible;
    template <class T>                struct is_trivially_default_constructible;
    template <class T>                struct is_trivially_copy_constructible;
    template <class T>                struct is_trivially_move_constructible;
    template <class T, class U>       struct is_trivially_assignable;
    template <class T>                struct is_trivially_copy_assignable;
    template <class T>                struct is_trivially_move_assignable;
    template <class T>                struct is_trivially_destructible;

    template <class T, class... Args> struct is_nothrow_constructible;
    template <class T>                struct is_nothrow_default_constructible;
    template <class T>                struct is_nothrow_copy_constructible;
    template <class T>                struct is_nothrow_move_constructible;
    template <class T, class U>       struct is_nothrow_assignable;
    template <class T>                struct is_nothrow_copy_assignable;
    template <class T>                struct is_nothrow_move_assignable;
    template <class T, class U>       struct is_nothrow_swappable_with; // C++17
    template <class T>                struct is_nothrow_swappable;      // C++17
    template <class T>                struct is_nothrow_destructible;

    template <class T> struct has_virtual_destructor;

    template<class T> struct has_unique_object_representations;         // C++17

    // Relationships between types:
    template <class T, class U> struct is_same;
    template <class Base, class Derived> struct is_base_of;

    template <class From, class To> struct is_convertible;
    template <typename From, typename To> struct is_nothrow_convertible;                  // C++20
    template <typename From, typename To> inline constexpr bool is_nothrow_convertible_v; // C++20

    template <class Fn, class... ArgTypes> struct is_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_invocable_r;

    template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;

    // Alignment properties and transformations:
    template <class T> struct alignment_of;
    template <size_t Len, size_t Align = most_stringent_alignment_requirement>
        struct aligned_storage;
    template <size_t Len, class... Types> struct aligned_union;
    template <class T> struct remove_cvref; // C++20

    template <class T> struct decay;
    template <class... T> struct common_type;
    template <class T> struct underlying_type;
    template <class> class result_of; // undefined
    template <class Fn, class... ArgTypes> class result_of<Fn(ArgTypes...)>;
    template <class Fn, class... ArgTypes> struct invoke_result;  // C++17

    // const-volatile modifications:
    template <class T>
      using remove_const_t    = typename remove_const<T>::type;  // C++14
    template <class T>
      using remove_volatile_t = typename remove_volatile<T>::type;  // C++14
    template <class T>
      using remove_cv_t       = typename remove_cv<T>::type;  // C++14
    template <class T>
      using add_const_t       = typename add_const<T>::type;  // C++14
    template <class T>
      using add_volatile_t    = typename add_volatile<T>::type;  // C++14
    template <class T>
      using add_cv_t          = typename add_cv<T>::type;  // C++14

    // reference modifications:
    template <class T>
      using remove_reference_t     = typename remove_reference<T>::type;  // C++14
    template <class T>
      using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;  // C++14
    template <class T>
      using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;  // C++14

    // sign modifications:
    template <class T>
      using make_signed_t   = typename make_signed<T>::type;  // C++14
    template <class T>
      using make_unsigned_t = typename make_unsigned<T>::type;  // C++14

    // array modifications:
    template <class T>
      using remove_extent_t      = typename remove_extent<T>::type;  // C++14
    template <class T>
      using remove_all_extents_t = typename remove_all_extents<T>::type;  // C++14

    template <class T>
      inline constexpr bool is_bounded_array_v
        = is_bounded_array<T>::value;                                     // C++20
      inline constexpr bool is_unbounded_array_v
        = is_unbounded_array<T>::value;                                   // C++20

    // pointer modifications:
    template <class T>
      using remove_pointer_t = typename remove_pointer<T>::type;  // C++14
    template <class T>
      using add_pointer_t    = typename add_pointer<T>::type;  // C++14

    // other transformations:
    template <size_t Len, std::size_t Align=default-alignment>
      using aligned_storage_t = typename aligned_storage<Len,Align>::type;  // C++14
    template <std::size_t Len, class... Types>
      using aligned_union_t   = typename aligned_union<Len,Types...>::type;  // C++14
    template <class T>
      using remove_cvref_t    = typename remove_cvref<T>::type;  // C++20
    template <class T>
      using decay_t           = typename decay<T>::type;  // C++14
    template <bool b, class T=void>
      using enable_if_t       = typename enable_if<b,T>::type;  // C++14
    template <bool b, class T, class F>
      using conditional_t     = typename conditional<b,T,F>::type;  // C++14
    template <class... T>
      using common_type_t     = typename common_type<T...>::type;  // C++14
    template <class T>
      using underlying_type_t = typename underlying_type<T>::type;  // C++14
    template <class T>
      using result_of_t       = typename result_of<T>::type;  // C++14
    template <class Fn, class... ArgTypes>
      using invoke_result_t   = typename invoke_result<Fn, ArgTypes...>::type;  // C++17

    template <class...>
      using void_t = void;   // C++17

      // See C++14 20.10.4.1, primary type categories
      template <class T> inline constexpr bool is_void_v
        = is_void<T>::value;                                             // C++17
      template <class T> inline constexpr bool is_null_pointer_v
        = is_null_pointer<T>::value;                                     // C++17
      template <class T> inline constexpr bool is_integral_v
        = is_integral<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_floating_point_v
        = is_floating_point<T>::value;                                   // C++17
      template <class T> inline constexpr bool is_array_v
        = is_array<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_pointer_v
        = is_pointer<T>::value;                                          // C++17
      template <class T> inline constexpr bool is_lvalue_reference_v
        = is_lvalue_reference<T>::value;                                 // C++17
      template <class T> inline constexpr bool is_rvalue_reference_v
        = is_rvalue_reference<T>::value;                                 // C++17
      template <class T> inline constexpr bool is_member_object_pointer_v
        = is_member_object_pointer<T>::value;                            // C++17
      template <class T> inline constexpr bool is_member_function_pointer_v
        = is_member_function_pointer<T>::value;                          // C++17
      template <class T> inline constexpr bool is_enum_v
        = is_enum<T>::value;                                             // C++17
      template <class T> inline constexpr bool is_union_v
        = is_union<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_class_v
        = is_class<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_function_v
        = is_function<T>::value;                                         // C++17

      // See C++14 20.10.4.2, composite type categories
      template <class T> inline constexpr bool is_reference_v
        = is_reference<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_arithmetic_v
        = is_arithmetic<T>::value;                                       // C++17
      template <class T> inline constexpr bool is_fundamental_v
        = is_fundamental<T>::value;                                      // C++17
      template <class T> inline constexpr bool is_object_v
        = is_object<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_scalar_v
        = is_scalar<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_compound_v
        = is_compound<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_member_pointer_v
        = is_member_pointer<T>::value;                                   // C++17

      // See C++14 20.10.4.3, type properties
      template <class T> inline constexpr bool is_const_v
        = is_const<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_volatile_v
        = is_volatile<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_trivial_v
        = is_trivial<T>::value;                                          // C++17
      template <class T> inline constexpr bool is_trivially_copyable_v
        = is_trivially_copyable<T>::value;                               // C++17
      template <class T> inline constexpr bool is_standard_layout_v
        = is_standard_layout<T>::value;                                  // C++17
      template <class T> inline constexpr bool is_pod_v
        = is_pod<T>::value;                                              // C++17
      template <class T> inline constexpr bool is_literal_type_v
        = is_literal_type<T>::value;                                     // C++17
      template <class T> inline constexpr bool is_empty_v
        = is_empty<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_polymorphic_v
        = is_polymorphic<T>::value;                                      // C++17
      template <class T> inline constexpr bool is_abstract_v
        = is_abstract<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_final_v
        = is_final<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_aggregate_v
        = is_aggregate<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_signed_v
        = is_signed<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_unsigned_v
        = is_unsigned<T>::value;                                         // C++17
      template <class T, class... Args> inline constexpr bool is_constructible_v
        = is_constructible<T, Args...>::value;                           // C++17
      template <class T> inline constexpr bool is_default_constructible_v
        = is_default_constructible<T>::value;                            // C++17
      template <class T> inline constexpr bool is_copy_constructible_v
        = is_copy_constructible<T>::value;                               // C++17
      template <class T> inline constexpr bool is_move_constructible_v
        = is_move_constructible<T>::value;                               // C++17
      template <class T, class U> inline constexpr bool is_assignable_v
        = is_assignable<T, U>::value;                                    // C++17
      template <class T> inline constexpr bool is_copy_assignable_v
        = is_copy_assignable<T>::value;                                  // C++17
      template <class T> inline constexpr bool is_move_assignable_v
        = is_move_assignable<T>::value;                                  // C++17
      template <class T, class U> inline constexpr bool is_swappable_with_v
        = is_swappable_with<T, U>::value;                                // C++17
      template <class T> inline constexpr bool is_swappable_v
        = is_swappable<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_destructible_v
        = is_destructible<T>::value;                                     // C++17
      template <class T, class... Args> inline constexpr bool is_trivially_constructible_v
        = is_trivially_constructible<T, Args...>::value;                 // C++17
      template <class T> inline constexpr bool is_trivially_default_constructible_v
        = is_trivially_default_constructible<T>::value;                  // C++17
      template <class T> inline constexpr bool is_trivially_copy_constructible_v
        = is_trivially_copy_constructible<T>::value;                     // C++17
      template <class T> inline constexpr bool is_trivially_move_constructible_v
        = is_trivially_move_constructible<T>::value;                     // C++17
      template <class T, class U> inline constexpr bool is_trivially_assignable_v
        = is_trivially_assignable<T, U>::value;                          // C++17
      template <class T> inline constexpr bool is_trivially_copy_assignable_v
        = is_trivially_copy_assignable<T>::value;                        // C++17
      template <class T> inline constexpr bool is_trivially_move_assignable_v
        = is_trivially_move_assignable<T>::value;                        // C++17
      template <class T> inline constexpr bool is_trivially_destructible_v
        = is_trivially_destructible<T>::value;                           // C++17
      template <class T, class... Args> inline constexpr bool is_nothrow_constructible_v
        = is_nothrow_constructible<T, Args...>::value;                   // C++17
      template <class T> inline constexpr bool is_nothrow_default_constructible_v
        = is_nothrow_default_constructible<T>::value;                    // C++17
      template <class T> inline constexpr bool is_nothrow_copy_constructible_v
        = is_nothrow_copy_constructible<T>::value;                       // C++17
      template <class T> inline constexpr bool is_nothrow_move_constructible_v
        = is_nothrow_move_constructible<T>::value;                       // C++17
      template <class T, class U> inline constexpr bool is_nothrow_assignable_v
        = is_nothrow_assignable<T, U>::value;                            // C++17
      template <class T> inline constexpr bool is_nothrow_copy_assignable_v
        = is_nothrow_copy_assignable<T>::value;                          // C++17
      template <class T> inline constexpr bool is_nothrow_move_assignable_v
        = is_nothrow_move_assignable<T>::value;                          // C++17
      template <class T, class U> inline constexpr bool is_nothrow_swappable_with_v
        = is_nothrow_swappable_with<T, U>::value;                       // C++17
      template <class T> inline constexpr bool is_nothrow_swappable_v
        = is_nothrow_swappable<T>::value;                               // C++17
      template <class T> inline constexpr bool is_nothrow_destructible_v
        = is_nothrow_destructible<T>::value;                             // C++17
      template <class T> inline constexpr bool has_virtual_destructor_v
        = has_virtual_destructor<T>::value;                              // C++17
      template<class T> inline constexpr bool has_unique_object_representations_v // C++17
        = has_unique_object_representations<T>::value;

      // See C++14 20.10.5, type property queries
      template <class T> inline constexpr size_t alignment_of_v
        = alignment_of<T>::value;                                        // C++17
      template <class T> inline constexpr size_t rank_v
        = rank<T>::value;                                                // C++17
      template <class T, unsigned I = 0> inline constexpr size_t extent_v
        = extent<T, I>::value;                                           // C++17

      // See C++14 20.10.6, type relations
      template <class T, class U> inline constexpr bool is_same_v
        = is_same<T, U>::value;                                          // C++17
      template <class Base, class Derived> inline constexpr bool is_base_of_v
        = is_base_of<Base, Derived>::value;                              // C++17
      template <class From, class To> inline constexpr bool is_convertible_v
        = is_convertible<From, To>::value;                               // C++17
      template <class Fn, class... ArgTypes> inline constexpr bool is_invocable_v
        = is_invocable<Fn, ArgTypes...>::value;                          // C++17
      template <class R, class Fn, class... ArgTypes> inline constexpr bool is_invocable_r_v
        = is_invocable_r<R, Fn, ArgTypes...>::value;                     // C++17
      template <class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_v
        = is_nothrow_invocable<Fn, ArgTypes...>::value;                  // C++17
      template <class R, class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_r_v
        = is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;             // C++17

      // [meta.logical], logical operator traits:
      template<class... B> struct conjunction;                           // C++17
      template<class... B>
        inline constexpr bool conjunction_v = conjunction<B...>::value;  // C++17
      template<class... B> struct disjunction;                           // C++17
      template<class... B>
        inline constexpr bool disjunction_v = disjunction<B...>::value;  // C++17
      template<class B> struct negation;                                 // C++17
      template<class B>
        inline constexpr bool negation_v = negation<B>::value;           // C++17

}

*/
#include "__config.hh"
#include "cstddef.hh"
//#include <version>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _T1, class _T2> struct _LIBCPP_TEMPLATE_VIS pair;
template <class _Tp> class _LIBCPP_TEMPLATE_VIS reference_wrapper;
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS hash;

template <class _Tp, _Tp __v> struct _LIBCPP_TEMPLATE_VIS integral_constant {
  static _LIBCPP_CONSTEXPR const _Tp value = __v;
  typedef _Tp value_type;
  typedef integral_constant type;
  _LIBCPP_INLINE_VISIBILITY
  _LIBCPP_CONSTEXPR operator value_type() const _NOEXCEPT { return value; }
#if _LIBCPP_STD_VER > 11
  _LIBCPP_INLINE_VISIBILITY
  constexpr value_type operator()() const _NOEXCEPT { return value; }
#endif
};

template <class _Tp, _Tp __v> _LIBCPP_CONSTEXPR const _Tp integral_constant<_Tp, __v>::value;

#if _LIBCPP_STD_VER > 14
template <bool __b> using bool_constant = integral_constant<bool, __b>;
#define _LIBCPP_BOOL_CONSTANT(__b) bool_constant<(__b)>
#else
#define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool, (__b)>
#endif

typedef _LIBCPP_BOOL_CONSTANT(true) true_type;
typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

template <bool _Val> using _BoolConstant _LIBCPP_NODEBUG_TYPE = integral_constant<bool, _Val>;

template <bool> struct _MetaBase;
template <> struct _MetaBase<true> {
  template <class _Tp, class _Up> using _SelectImpl _LIBCPP_NODEBUG_TYPE = _Tp;
  template <template <class...> class _FirstFn, template <class...> class, class... _Args>
  using _SelectApplyImpl _LIBCPP_NODEBUG_TYPE                                      = _FirstFn<_Args...>;
  template <class _First, class...> using _FirstImpl _LIBCPP_NODEBUG_TYPE          = _First;
  template <class, class _Second, class...> using _SecondImpl _LIBCPP_NODEBUG_TYPE = _Second;
  template <class _Tp = void> using _EnableIfImpl _LIBCPP_NODEBUG_TYPE             = _Tp;
  template <class _Result, class _First, class... _Rest>
  using _OrImpl _LIBCPP_NODEBUG_TYPE =
      typename _MetaBase<_First::value != true && sizeof...(_Rest) != 0>::template _OrImpl<_First, _Rest...>;
  template <class _Result, class _First, class... _Rest>
  using _AndImpl _LIBCPP_NODEBUG_TYPE =
      typename _MetaBase<_First::value == true && sizeof...(_Rest) != 0>::template _AndImpl<_First, _Rest...>;
};

template <> struct _MetaBase<false> {
  template <class _Tp, class _Up> using _SelectImpl _LIBCPP_NODEBUG_TYPE = _Up;
  template <template <class...> class, template <class...> class _SecondFn, class... _Args>
  using _SelectApplyImpl _LIBCPP_NODEBUG_TYPE                            = _SecondFn<_Args...>;
  template <class _Result, class...> using _OrImpl _LIBCPP_NODEBUG_TYPE  = _Result;
  template <class _Result, class...> using _AndImpl _LIBCPP_NODEBUG_TYPE = _Result;
};
template <bool _Cond, class _Ret = void>
using _EnableIf _LIBCPP_NODEBUG_TYPE = typename _MetaBase<_Cond>::template _EnableIfImpl<_Ret>;
template <bool _Cond, class _IfRes, class _ElseRes>
using _If _LIBCPP_NODEBUG_TYPE = typename _MetaBase<_Cond>::template _SelectImpl<_IfRes, _ElseRes>;
template <class... _Rest>
using _Or _LIBCPP_NODEBUG_TYPE = typename _MetaBase<sizeof...(_Rest) != 0>::template _OrImpl<false_type, _Rest...>;
template <class... _Rest>
using _And _LIBCPP_NODEBUG_TYPE = typename _MetaBase<sizeof...(_Rest) != 0>::template _AndImpl<true_type, _Rest...>;
template <class _Pred> struct _Not : _BoolConstant<!_Pred::value> {};
template <class... _Args>
using _FirstType _LIBCPP_NODEBUG_TYPE = typename _MetaBase<(sizeof...(_Args) >= 1)>::template _FirstImpl<_Args...>;
template <class... _Args>
using _SecondType _LIBCPP_NODEBUG_TYPE = typename _MetaBase<(sizeof...(_Args) >= 2)>::template _SecondImpl<_Args...>;

template <template <class...> class _Func, class... _Args> struct _Lazy : _Func<_Args...> {};

// Member detector base

template <template <class...> class _Templ, class... _Args, class = _Templ<_Args...>> true_type __sfinae_test_impl(int);
template <template <class...> class, class...> false_type __sfinae_test_impl(...);

template <template <class...> class _Templ, class... _Args>
using _IsValidExpansion _LIBCPP_NODEBUG_TYPE = decltype(__sfinae_test_impl<_Templ, _Args...>(0));

template <class> struct __void_t { typedef void type; };

template <class _Tp> struct __identity { typedef _Tp type; };

template <class _Tp, bool> struct _LIBCPP_TEMPLATE_VIS __dependent_type : public _Tp {};

template <bool _Bp, class _If, class _Then> struct _LIBCPP_TEMPLATE_VIS conditional { typedef _If type; };
template <class _If, class _Then> struct _LIBCPP_TEMPLATE_VIS conditional<false, _If, _Then> { typedef _Then type; };

#if _LIBCPP_STD_VER > 11
template <bool _Bp, class _If, class _Then> using conditional_t = typename conditional<_Bp, _If, _Then>::type;
#endif

template <bool, class _Tp = void> struct _LIBCPP_TEMPLATE_VIS enable_if {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS enable_if<true, _Tp> { typedef _Tp type; };

#if _LIBCPP_STD_VER > 11
template <bool _Bp, class _Tp = void> using enable_if_t = typename enable_if<_Bp, _Tp>::type;
#endif

// is_same

#if __has_keyword(__is_same)

template <class _Tp, class _Up> struct _LIBCPP_TEMPLATE_VIS is_same : _BoolConstant<__is_same(_Tp, _Up)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Up> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_same_v = __is_same(_Tp, _Up);
#endif

#else

template <class _Tp, class _Up> struct _LIBCPP_TEMPLATE_VIS is_same : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_same<_Tp, _Tp> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Up> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_same_v = is_same<_Tp, _Up>::value;
#endif

#endif // __is_same

template <class _Tp, class _Up>
using _IsSame = _BoolConstant<
#ifdef __clang__
    __is_same(_Tp, _Up)
#else
    _VSTD::is_same<_Tp, _Up>::value
#endif
    >;

template <class _Tp, class _Up>
using _IsNotSame = _BoolConstant<
#ifdef __clang__
    !__is_same(_Tp, _Up)
#else
    !_VSTD::is_same<_Tp, _Up>::value
#endif
    >;

template <class _Tp>
using __test_for_primary_template                = _EnableIf<_IsSame<_Tp, typename _Tp::__primary_template>::value>;
template <class _Tp> using __is_primary_template = _IsValidExpansion<__test_for_primary_template, _Tp>;

// addressof
#ifndef _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

template <class _Tp>
inline _LIBCPP_CONSTEXPR_AFTER_CXX14 _LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY _Tp *addressof(_Tp &__x) _NOEXCEPT {
  return __builtin_addressof(__x);
}

#else

template <class _Tp> inline _LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY _Tp *addressof(_Tp &__x) _NOEXCEPT {
  return reinterpret_cast<_Tp *>(const_cast<char *>(&reinterpret_cast<const volatile char &>(__x)));
}

#endif // _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

#if defined(_LIBCPP_HAS_OBJC_ARC) && !defined(_LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF)
// Objective-C++ Automatic Reference Counting uses qualified pointers
// that require special addressof() signatures. When
// _LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF is defined, the compiler
// itself is providing these definitions. Otherwise, we provide them.
template <class _Tp> inline _LIBCPP_INLINE_VISIBILITY __strong _Tp *addressof(__strong _Tp &__x) _NOEXCEPT {
  return &__x;
}

#ifdef _LIBCPP_HAS_OBJC_ARC_WEAK
template <class _Tp> inline _LIBCPP_INLINE_VISIBILITY __weak _Tp *addressof(__weak _Tp &__x) _NOEXCEPT { return &__x; }
#endif

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY __autoreleasing _Tp *addressof(__autoreleasing _Tp &__x) _NOEXCEPT {
  return &__x;
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY __unsafe_unretained _Tp *addressof(__unsafe_unretained _Tp &__x) _NOEXCEPT {
  return &__x;
}
#endif

#if !defined(_LIBCPP_CXX03_LANG)
template <class _Tp> _Tp *addressof(const _Tp &&) noexcept = delete;
#endif

struct __two {
  char __lx[2];
};

// helper class:

// is_const

#if __has_keyword(__is_const)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const : _BoolConstant<__is_const(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_const_v = __is_const(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const<_Tp const> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_const_v = is_const<_Tp>::value;
#endif

#endif // __has_keyword(__is_const)

// is_volatile

#if __has_keyword(__is_volatile)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_volatile : _BoolConstant<__is_volatile(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_volatile_v = __is_volatile(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_volatile : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_volatile<_Tp volatile> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_volatile_v = is_volatile<_Tp>::value;
#endif

#endif // __has_keyword(__is_volatile)

// remove_const

#if __has_keyword(__remove_const)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_const { typedef __remove_const(_Tp) type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_const_t = __remove_const(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_const { typedef _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_const<const _Tp> { typedef _Tp type; };
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_const_t = typename remove_const<_Tp>::type;
#endif

#endif // __has_keyword(__remove_const)

// remove_volatile

#if __has_keyword(__remove_volatile)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_volatile { typedef __remove_volatile(_Tp) type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_volatile_t = __remove_volatile(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_volatile { typedef _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_volatile<volatile _Tp> { typedef _Tp type; };
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_volatile_t = typename remove_volatile<_Tp>::type;
#endif

#endif // __has_keyword(__remove_volatile)

// remove_cv

#if __has_keyword(__remove_cv)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_cv { typedef __remove_cv(_Tp) type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_cv_t = __remove_cv(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_cv {
  typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
};
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_cv_t = typename remove_cv<_Tp>::type;
#endif

#endif // __has_keyword(__remove_cv)

// is_void

#if __has_keyword(__is_void)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_void : _BoolConstant<__is_void(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_void_v = __is_void(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_void : public is_same<typename remove_cv<_Tp>::type, void> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_void_v = is_void<_Tp>::value;
#endif

#endif // __has_keyword(__is_void)

// __is_nullptr_t

template <class _Tp> struct __is_nullptr_t_impl : public false_type {};
template <> struct __is_nullptr_t_impl<nullptr_t> : public true_type {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS __is_nullptr_t : public __is_nullptr_t_impl<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 11
template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_null_pointer : public __is_nullptr_t_impl<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_null_pointer_v = is_null_pointer<_Tp>::value;
#endif
#endif // _LIBCPP_STD_VER > 11

// is_integral

#if __has_keyword(__is_integral)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_integral : _BoolConstant<__is_integral(_Tp)> {};

#if _LIBCPP_STD_VER > 14
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_integral_v = __is_integral(_Tp);
#endif

#else

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_integral
    : public _BoolConstant<__libcpp_is_integral<typename remove_cv<_Tp>::type>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_integral_v = is_integral<_Tp>::value;
#endif

#endif // __has_keyword(__is_integral)

// is_floating_point

template <class _Tp> struct __libcpp_is_floating_point : public false_type {};
template <> struct __libcpp_is_floating_point<float> : public true_type {};
template <> struct __libcpp_is_floating_point<double> : public true_type {};
template <> struct __libcpp_is_floating_point<long double> : public true_type {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_floating_point : public __libcpp_is_floating_point<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_floating_point_v = is_floating_point<_Tp>::value;
#endif

// is_array

#if __has_keyword(__is_array)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_array : _BoolConstant<__is_array(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_array_v = __is_array(_Tp);
#endif

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_array : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_array<_Tp[]> : public true_type {};
template <class _Tp, size_t _Np> struct _LIBCPP_TEMPLATE_VIS is_array<_Tp[_Np]> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_array_v = is_array<_Tp>::value;
#endif

#endif // __has_keyword(__is_array)

// is_pointer

// In clang 10.0.0 and earlier __is_pointer didn't work with Objective-C types.
#if __has_keyword(__is_pointer) && _LIBCPP_CLANG_VER > 1000

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_pointer : _BoolConstant<__is_pointer(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_pointer_v = __is_pointer(_Tp);
#endif

#else // __has_keyword(__is_pointer)

template <class _Tp> struct __libcpp_is_pointer : public false_type {};
template <class _Tp> struct __libcpp_is_pointer<_Tp *> : public true_type {};

template <class _Tp> struct __libcpp_remove_objc_qualifiers { typedef _Tp type; };
#if defined(_LIBCPP_HAS_OBJC_ARC)
template <class _Tp> struct __libcpp_remove_objc_qualifiers<_Tp __strong> { typedef _Tp type; };
template <class _Tp> struct __libcpp_remove_objc_qualifiers<_Tp __weak> { typedef _Tp type; };
template <class _Tp> struct __libcpp_remove_objc_qualifiers<_Tp __autoreleasing> { typedef _Tp type; };
template <class _Tp> struct __libcpp_remove_objc_qualifiers<_Tp __unsafe_unretained> { typedef _Tp type; };
#endif

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_pointer
    : public __libcpp_is_pointer<typename __libcpp_remove_objc_qualifiers<typename remove_cv<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_pointer_v = is_pointer<_Tp>::value;
#endif

#endif // __has_keyword(__is_pointer)

// is_reference

#if __has_keyword(__is_lvalue_reference) && __has_keyword(__is_rvalue_reference) && __has_keyword(__is_reference)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_lvalue_reference : _BoolConstant<__is_lvalue_reference(_Tp)> {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_rvalue_reference : _BoolConstant<__is_rvalue_reference(_Tp)> {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_reference : _BoolConstant<__is_reference(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_reference_v = __is_reference(_Tp);

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_lvalue_reference_v = __is_lvalue_reference(_Tp);

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_rvalue_reference_v = __is_rvalue_reference(_Tp);
#endif

#else // __has_keyword(__is_lvalue_reference) && etc...

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_lvalue_reference : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_lvalue_reference<_Tp &> : public true_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_rvalue_reference : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_rvalue_reference<_Tp &&> : public true_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_reference : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_reference<_Tp &> : public true_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_reference<_Tp &&> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_reference_v = is_reference<_Tp>::value;

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_lvalue_reference_v = is_lvalue_reference<_Tp>::value;

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_rvalue_reference_v = is_rvalue_reference<_Tp>::value;
#endif

#endif // __has_keyword(__is_lvalue_reference) && etc...

// is_union

#if __has_feature(is_union) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_union : public integral_constant<bool, __is_union(_Tp)> {};

#else

template <class _Tp> struct __libcpp_union : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_union : public __libcpp_union<typename remove_cv<_Tp>::type> {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_union_v = is_union<_Tp>::value;
#endif

// is_class

#if __has_feature(is_class) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_class : public integral_constant<bool, __is_class(_Tp)> {};

#else

namespace __is_class_imp {
template <class _Tp> char __test(int _Tp::*);
template <class _Tp> __two __test(...);
} // namespace __is_class_imp

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_class
    : public integral_constant<bool, sizeof(__is_class_imp::__test<_Tp>(0)) == 1 && !is_union<_Tp>::value> {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_class_v = is_class<_Tp>::value;
#endif

// is_function

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_function : public _BoolConstant<
#ifdef __clang__
                                              __is_function(_Tp)
#else
                                              !(is_reference<_Tp>::value || is_const<const _Tp>::value)
#endif
                                              > {
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_function_v = is_function<_Tp>::value;
#endif

template <class _Tp> struct __libcpp_is_member_pointer {
  enum { __is_member = false, __is_func = false, __is_obj = false };
};
template <class _Tp, class _Up> struct __libcpp_is_member_pointer<_Tp _Up::*> {
  enum {
    __is_member = true,
    __is_func   = is_function<_Tp>::value,
    __is_obj    = !__is_func,
  };
};

#if __has_keyword(__is_member_function_pointer)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_member_function_pointer : _BoolConstant<__is_member_function_pointer(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_function_pointer_v = __is_member_function_pointer(_Tp);
#endif

#else // __has_keyword(__is_member_function_pointer)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_member_function_pointer
    : public _BoolConstant<__libcpp_is_member_pointer<typename remove_cv<_Tp>::type>::__is_func> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_function_pointer_v = is_member_function_pointer<_Tp>::value;
#endif

#endif // __has_keyword(__is_member_function_pointer)

// is_member_pointer

#if __has_keyword(__is_member_pointer)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_member_pointer : _BoolConstant<__is_member_pointer(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_pointer_v = __is_member_pointer(_Tp);
#endif

#else // __has_keyword(__is_member_pointer)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_member_pointer
    : public _BoolConstant<__libcpp_is_member_pointer<typename remove_cv<_Tp>::type>::__is_member> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_pointer_v = is_member_pointer<_Tp>::value;
#endif

#endif // __has_keyword(__is_member_pointer)

// is_member_object_pointer

#if __has_keyword(__is_member_object_pointer)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_member_object_pointer : _BoolConstant<__is_member_object_pointer(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_object_pointer_v = __is_member_object_pointer(_Tp);
#endif

#else // __has_keyword(__is_member_object_pointer)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_member_object_pointer
    : public _BoolConstant<__libcpp_is_member_pointer<typename remove_cv<_Tp>::type>::__is_obj> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_member_object_pointer_v = is_member_object_pointer<_Tp>::value;
#endif

#endif // __has_keyword(__is_member_object_pointer)

// is_enum

#if __has_feature(is_enum) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_enum : public integral_constant<bool, __is_enum(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_enum_v = __is_enum(_Tp);
#endif

#else

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_enum
    : public integral_constant<bool, !is_void<_Tp>::value && !is_integral<_Tp>::value &&
                                         !is_floating_point<_Tp>::value && !is_array<_Tp>::value &&
                                         !is_pointer<_Tp>::value && !is_reference<_Tp>::value &&
                                         !is_member_pointer<_Tp>::value && !is_union<_Tp>::value &&
                                         !is_class<_Tp>::value && !is_function<_Tp>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_enum_v = is_enum<_Tp>::value;
#endif

#endif // __has_feature(is_enum) || defined(_LIBCPP_COMPILER_GCC)

// is_arithmetic

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_arithmetic
    : public integral_constant<bool, is_integral<_Tp>::value || is_floating_point<_Tp>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_arithmetic_v = is_arithmetic<_Tp>::value;
#endif

// is_fundamental

// In clang 9 and lower, this builtin did not work for nullptr_t. Additionally, in C++03 mode,
// nullptr isn't defined by the compiler so, this builtin won't work.
#if __has_keyword(__is_fundamental) && _LIBCPP_CLANG_VER > 900 && !defined(_LIBCPP_CXX03_LANG)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_fundamental : _BoolConstant<__is_fundamental(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_fundamental_v = __is_fundamental(_Tp);
#endif

#else // __has_keyword(__is_fundamental)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_fundamental
    : public integral_constant<bool, is_void<_Tp>::value || __is_nullptr_t<_Tp>::value || is_arithmetic<_Tp>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_fundamental_v = is_fundamental<_Tp>::value;
#endif

#endif // __has_keyword(__is_fundamental)

// is_scalar

// >= 11 because in C++03 nullptr isn't actually nullptr
#if __has_keyword(__is_scalar) && !defined(_LIBCPP_CXX03_LANG)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_scalar : _BoolConstant<__is_scalar(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_scalar_v = __is_scalar(_Tp);
#endif

#else // __has_keyword(__is_scalar)

template <class _Tp> struct __is_block : false_type {};
#if defined(_LIBCPP_HAS_EXTENSION_BLOCKS)
template <class _Rp, class... _Args> struct __is_block<_Rp (^)(_Args...)> : true_type {};
#endif

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_scalar
    : public integral_constant<bool, is_arithmetic<_Tp>::value || is_member_pointer<_Tp>::value ||
                                         is_pointer<_Tp>::value || __is_nullptr_t<_Tp>::value ||
                                         __is_block<_Tp>::value || is_enum<_Tp>::value> {};

template <> struct _LIBCPP_TEMPLATE_VIS is_scalar<nullptr_t> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_scalar_v = is_scalar<_Tp>::value;
#endif

#endif // __has_keyword(__is_scalar)

// is_object

#if __has_keyword(__is_object)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_object : _BoolConstant<__is_object(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_object_v = __is_object(_Tp);
#endif

#else // __has_keyword(__is_object)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_object
    : public integral_constant<bool, is_scalar<_Tp>::value || is_array<_Tp>::value || is_union<_Tp>::value ||
                                         is_class<_Tp>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_object_v = is_object<_Tp>::value;
#endif

#endif // __has_keyword(__is_object)

// is_compound

// >= 11 because in C++03 nullptr isn't actually nullptr
#if __has_keyword(__is_compound) && !defined(_LIBCPP_CXX03_LANG)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_compound : _BoolConstant<__is_compound(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_compound_v = __is_compound(_Tp);
#endif

#else // __has_keyword(__is_compound)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_compound : public integral_constant<bool, !is_fundamental<_Tp>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_compound_v = is_compound<_Tp>::value;
#endif

#endif // __has_keyword(__is_compound)

// __is_referenceable  [defns.referenceable]

struct __is_referenceable_impl {
  template <class _Tp> static _Tp &__test(int);
  template <class _Tp> static __two __test(...);
};

template <class _Tp>
struct __is_referenceable
    : integral_constant<bool, _IsNotSame<decltype(__is_referenceable_impl::__test<_Tp>(0)), __two>::value> {};

// add_const

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_const { typedef _LIBCPP_NODEBUG_TYPE const _Tp type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_const_t = typename add_const<_Tp>::type;
#endif

// add_volatile

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_volatile { typedef _LIBCPP_NODEBUG_TYPE volatile _Tp type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_volatile_t = typename add_volatile<_Tp>::type;
#endif

// add_cv
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_cv { typedef _LIBCPP_NODEBUG_TYPE const volatile _Tp type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_cv_t = typename add_cv<_Tp>::type;
#endif

// remove_reference

#if __has_keyword(__remove_reference)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference { typedef __remove_reference(_Tp) type; };

#else // __has_keyword(__remove_reference)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference<_Tp &> { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference<_Tp &&> { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_reference_t = typename remove_reference<_Tp>::type;
#endif

#endif // __has_keyword(__remove_reference)

// add_lvalue_reference

template <class _Tp, bool = __is_referenceable<_Tp>::value> struct __add_lvalue_reference_impl {
  typedef _LIBCPP_NODEBUG_TYPE _Tp type;
};
template <class _Tp> struct __add_lvalue_reference_impl<_Tp, true> { typedef _LIBCPP_NODEBUG_TYPE _Tp &type; };

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_lvalue_reference {
  typedef _LIBCPP_NODEBUG_TYPE typename __add_lvalue_reference_impl<_Tp>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_lvalue_reference_t = typename add_lvalue_reference<_Tp>::type;
#endif

template <class _Tp, bool = __is_referenceable<_Tp>::value> struct __add_rvalue_reference_impl {
  typedef _LIBCPP_NODEBUG_TYPE _Tp type;
};
template <class _Tp> struct __add_rvalue_reference_impl<_Tp, true> { typedef _LIBCPP_NODEBUG_TYPE _Tp &&type; };

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_rvalue_reference {
  typedef _LIBCPP_NODEBUG_TYPE typename __add_rvalue_reference_impl<_Tp>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_rvalue_reference_t = typename add_rvalue_reference<_Tp>::type;
#endif

// Suppress deprecation notice for volatile-qualified return type resulting
// from volatile-qualified types _Tp.
_LIBCPP_SUPPRESS_DEPRECATED_PUSH
template <class _Tp> _Tp &&__declval(int);
template <class _Tp> _Tp __declval(long);
_LIBCPP_SUPPRESS_DEPRECATED_POP

template <class _Tp> decltype(_VSTD::__declval<_Tp>(0)) declval() _NOEXCEPT;

// __uncvref

template <class _Tp> struct __uncvref {
  typedef _LIBCPP_NODEBUG_TYPE typename remove_cv<typename remove_reference<_Tp>::type>::type type;
};

template <class _Tp> struct __unconstref {
  typedef _LIBCPP_NODEBUG_TYPE typename remove_const<typename remove_reference<_Tp>::type>::type type;
};

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp> using __uncvref_t _LIBCPP_NODEBUG_TYPE = typename __uncvref<_Tp>::type;
#endif

// __is_same_uncvref

template <class _Tp, class _Up>
struct __is_same_uncvref : _IsSame<typename __uncvref<_Tp>::type, typename __uncvref<_Up>::type> {};

#if _LIBCPP_STD_VER > 17
// remove_cvref - same as __uncvref
template <class _Tp> struct remove_cvref : public __uncvref<_Tp> {};

template <class _Tp> using remove_cvref_t = typename remove_cvref<_Tp>::type;
#endif

struct __any {
  __any(...);
};

// remove_pointer

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_pointer { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_pointer<_Tp *> { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_pointer<_Tp *const> { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_pointer<_Tp *volatile> {
  typedef _LIBCPP_NODEBUG_TYPE _Tp type;
};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_pointer<_Tp *const volatile> {
  typedef _LIBCPP_NODEBUG_TYPE _Tp type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_pointer_t = typename remove_pointer<_Tp>::type;
#endif

// add_pointer

template <class _Tp, bool = __is_referenceable<_Tp>::value || _IsSame<typename remove_cv<_Tp>::type, void>::value>
struct __add_pointer_impl {
  typedef _LIBCPP_NODEBUG_TYPE typename remove_reference<_Tp>::type *type;
};
template <class _Tp> struct __add_pointer_impl<_Tp, false> { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS add_pointer {
  typedef _LIBCPP_NODEBUG_TYPE typename __add_pointer_impl<_Tp>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using add_pointer_t = typename add_pointer<_Tp>::type;
#endif

// type_identity
#if _LIBCPP_STD_VER > 17
template <class _Tp> struct type_identity { typedef _Tp type; };
template <class _Tp> using type_identity_t = typename type_identity<_Tp>::type;
#endif

// is_signed

// In clang 9 and earlier, this builtin did not work for floating points or enums
#if __has_keyword(__is_signed) && _LIBCPP_CLANG_VER > 900

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_signed : _BoolConstant<__is_signed(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_signed_v = __is_signed(_Tp);
#endif

#else // __has_keyword(__is_signed)

template <class _Tp, bool = is_integral<_Tp>::value>
struct __libcpp_is_signed_impl : public _LIBCPP_BOOL_CONSTANT(_Tp(-1) < _Tp(0)) {};

template <class _Tp> struct __libcpp_is_signed_impl<_Tp, false> : public true_type {}; // floating point

template <class _Tp, bool = is_arithmetic<_Tp>::value>
struct __libcpp_is_signed : public __libcpp_is_signed_impl<_Tp> {};

template <class _Tp> struct __libcpp_is_signed<_Tp, false> : public false_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_signed : public __libcpp_is_signed<_Tp> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_signed_v = is_signed<_Tp>::value;
#endif

#endif // __has_keyword(__is_signed)

// is_unsigned

#if __has_keyword(__is_unsigned)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_unsigned : _BoolConstant<__is_unsigned(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_unsigned_v = __is_unsigned(_Tp);
#endif

#else // __has_keyword(__is_unsigned)

template <class _Tp, bool = is_integral<_Tp>::value>
struct __libcpp_is_unsigned_impl : public _LIBCPP_BOOL_CONSTANT(_Tp(0) < _Tp(-1)) {};

template <class _Tp> struct __libcpp_is_unsigned_impl<_Tp, false> : public false_type {}; // floating point

template <class _Tp, bool = is_arithmetic<_Tp>::value>
struct __libcpp_is_unsigned : public __libcpp_is_unsigned_impl<_Tp> {};

template <class _Tp> struct __libcpp_is_unsigned<_Tp, false> : public false_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_unsigned : public __libcpp_is_unsigned<_Tp> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_unsigned_v = is_unsigned<_Tp>::value;
#endif

#endif // __has_keyword(__is_unsigned)

// rank

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS rank : public integral_constant<size_t, 0> {};
template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS rank<_Tp[]> : public integral_constant<size_t, rank<_Tp>::value + 1> {};
template <class _Tp, size_t _Np>
struct _LIBCPP_TEMPLATE_VIS rank<_Tp[_Np]> : public integral_constant<size_t, rank<_Tp>::value + 1> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR size_t rank_v = rank<_Tp>::value;
#endif

// extent

#if __has_keyword(__array_extent)

template <class _Tp, size_t _Dim = 0>
struct _LIBCPP_TEMPLATE_VIS extent : integral_constant<size_t, __array_extent(_Tp, _Dim)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, unsigned _Ip = 0> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR size_t extent_v = __array_extent(_Tp, _Ip);
#endif

#else // __has_keyword(__array_extent)

template <class _Tp, unsigned _Ip = 0> struct _LIBCPP_TEMPLATE_VIS extent : public integral_constant<size_t, 0> {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS extent<_Tp[], 0> : public integral_constant<size_t, 0> {};
template <class _Tp, unsigned _Ip>
struct _LIBCPP_TEMPLATE_VIS extent<_Tp[], _Ip> : public integral_constant<size_t, extent<_Tp, _Ip - 1>::value> {};
template <class _Tp, size_t _Np>
struct _LIBCPP_TEMPLATE_VIS extent<_Tp[_Np], 0> : public integral_constant<size_t, _Np> {};
template <class _Tp, size_t _Np, unsigned _Ip>
struct _LIBCPP_TEMPLATE_VIS extent<_Tp[_Np], _Ip> : public integral_constant<size_t, extent<_Tp, _Ip - 1>::value> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, unsigned _Ip = 0> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR size_t extent_v = extent<_Tp, _Ip>::value;
#endif

#endif // __has_keyword(__array_extent)

// remove_extent

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_extent { typedef _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_extent<_Tp[]> { typedef _Tp type; };
template <class _Tp, size_t _Np> struct _LIBCPP_TEMPLATE_VIS remove_extent<_Tp[_Np]> { typedef _Tp type; };

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_extent_t = typename remove_extent<_Tp>::type;
#endif

// remove_all_extents

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_all_extents { typedef _Tp type; };
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_all_extents<_Tp[]> {
  typedef typename remove_all_extents<_Tp>::type type;
};
template <class _Tp, size_t _Np> struct _LIBCPP_TEMPLATE_VIS remove_all_extents<_Tp[_Np]> {
  typedef typename remove_all_extents<_Tp>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_all_extents_t = typename remove_all_extents<_Tp>::type;
#endif

#if _LIBCPP_STD_VER > 17
// is_bounded_array

template <class> struct _LIBCPP_TEMPLATE_VIS is_bounded_array : false_type {};
template <class _Tp, size_t _Np> struct _LIBCPP_TEMPLATE_VIS is_bounded_array<_Tp[_Np]> : true_type {};

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_bounded_array_v = is_bounded_array<_Tp>::value;

// is_unbounded_array

template <class> struct _LIBCPP_TEMPLATE_VIS is_unbounded_array : false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_unbounded_array<_Tp[]> : true_type {};

template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_unbounded_array_v = is_unbounded_array<_Tp>::value;
#endif

// decay

template <class _Up, bool> struct __decay { typedef _LIBCPP_NODEBUG_TYPE typename remove_cv<_Up>::type type; };

template <class _Up> struct __decay<_Up, true> {
public:
  typedef _LIBCPP_NODEBUG_TYPE
      typename conditional<is_array<_Up>::value, typename remove_extent<_Up>::type *,
                           typename conditional<is_function<_Up>::value, typename add_pointer<_Up>::type,
                                                typename remove_cv<_Up>::type>::type>::type type;
};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS decay {
private:
  typedef _LIBCPP_NODEBUG_TYPE typename remove_reference<_Tp>::type _Up;

public:
  typedef _LIBCPP_NODEBUG_TYPE typename __decay<_Up, __is_referenceable<_Up>::value>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using decay_t = typename decay<_Tp>::type;
#endif

// is_abstract

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_abstract : public integral_constant<bool, __is_abstract(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_abstract_v = is_abstract<_Tp>::value;
#endif

// is_final

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS __libcpp_is_final : public integral_constant<bool, __is_final(_Tp)> {};

#if _LIBCPP_STD_VER > 11
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_final : public integral_constant<bool, __is_final(_Tp)> {};
#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_final_v = is_final<_Tp>::value;
#endif

// is_aggregate
#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_IS_AGGREGATE)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_aggregate : public integral_constant<bool, __is_aggregate(_Tp)> {};

#if !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR constexpr bool is_aggregate_v = is_aggregate<_Tp>::value;
#endif

#endif // _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_IS_AGGREGATE)

// is_base_of

template <class _Bp, class _Dp>
struct _LIBCPP_TEMPLATE_VIS is_base_of : public integral_constant<bool, __is_base_of(_Bp, _Dp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Bp, class _Dp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_base_of_v = is_base_of<_Bp, _Dp>::value;
#endif

// is_convertible

#if __has_feature(is_convertible_to) && !defined(_LIBCPP_USE_IS_CONVERTIBLE_FALLBACK)

template <class _T1, class _T2>
struct _LIBCPP_TEMPLATE_VIS is_convertible : public integral_constant<bool, __is_convertible_to(_T1, _T2)> {};

#else // __has_feature(is_convertible_to)

namespace __is_convertible_imp {
template <class _Tp> void __test_convert(_Tp);

template <class _From, class _To, class = void> struct __is_convertible_test : public false_type {};

template <class _From, class _To>
struct __is_convertible_test<_From, _To,
                             decltype(_VSTD::__is_convertible_imp::__test_convert<_To>(_VSTD::declval<_From>()))>
    : public true_type {};

template <class _Tp, bool _IsArray = is_array<_Tp>::value, bool _IsFunction = is_function<_Tp>::value,
          bool _IsVoid = is_void<_Tp>::value>
struct __is_array_function_or_void {
  enum { value = 0 };
};
template <class _Tp> struct __is_array_function_or_void<_Tp, true, false, false> {
  enum { value = 1 };
};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, true, false> {
  enum { value = 2 };
};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, false, true> {
  enum { value = 3 };
};
} // namespace __is_convertible_imp

template <class _Tp,
          unsigned = __is_convertible_imp::__is_array_function_or_void<typename remove_reference<_Tp>::type>::value>
struct __is_convertible_check {
  static const size_t __v = 0;
};

template <class _Tp> struct __is_convertible_check<_Tp, 0> { static const size_t __v = sizeof(_Tp); };

template <class _T1, class _T2,
          unsigned _T1_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T1>::value,
          unsigned _T2_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T2>::value>
struct __is_convertible
    : public integral_constant<bool, __is_convertible_imp::__is_convertible_test<_T1, _T2>::value>{};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 1> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 1> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 1> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 1> : public false_type{};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 2> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 2> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 2> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 2> : public false_type{};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 3> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 3> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 3> : public false_type{};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 3> : public true_type{};

template <class _T1, class _T2> struct _LIBCPP_TEMPLATE_VIS is_convertible : public __is_convertible<_T1, _T2> {
  static const size_t __complete_check1 = __is_convertible_check<_T1>::__v;
  static const size_t __complete_check2 = __is_convertible_check<_T2>::__v;
};

#endif // __has_feature(is_convertible_to)

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _From, class _To>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_convertible_v = is_convertible<_From, _To>::value;
#endif

// is_nothrow_convertible

#if _LIBCPP_STD_VER > 17

template <typename _Tp> static void __test_noexcept(_Tp) noexcept;

template <typename _Fm, typename _To>
static bool_constant<noexcept(_VSTD::__test_noexcept<_To>(declval<_Fm>()))> __is_nothrow_convertible_test();

template <typename _Fm, typename _To>
struct __is_nothrow_convertible_helper : decltype(__is_nothrow_convertible_test<_Fm, _To>()) {};

template <typename _Fm, typename _To>
struct is_nothrow_convertible
    : _Or<_And<is_void<_To>, is_void<_Fm>>,
          _Lazy<_And, is_convertible<_Fm, _To>, __is_nothrow_convertible_helper<_Fm, _To>>>::type {};

template <typename _Fm, typename _To>
inline constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<_Fm, _To>::value;

#endif // _LIBCPP_STD_VER > 17

// is_empty

#if __has_feature(is_empty) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_empty : public integral_constant<bool, __is_empty(_Tp)> {};

#else // __has_feature(is_empty)

template <class _Tp> struct __is_empty1 : public _Tp { double __lx; };

struct __is_empty2 {
  double __lx;
};

template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_empty : public integral_constant<bool, sizeof(__is_empty1<_Tp>) == sizeof(__is_empty2)> {};

template <class _Tp> struct __libcpp_empty<_Tp, false> : public false_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_empty : public __libcpp_empty<_Tp> {};

#endif // __has_feature(is_empty)

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_empty_v = is_empty<_Tp>::value;
#endif

// is_polymorphic

#if __has_feature(is_polymorphic) || defined(_LIBCPP_COMPILER_MSVC)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_polymorphic : public integral_constant<bool, __is_polymorphic(_Tp)> {};

#else

template <typename _Tp>
char &__is_polymorphic_impl(
    typename enable_if<sizeof((_Tp *)dynamic_cast<const volatile void *>(declval<_Tp *>())) != 0, int>::type);
template <typename _Tp> __two &__is_polymorphic_impl(...);

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_polymorphic
    : public integral_constant<bool, sizeof(__is_polymorphic_impl<_Tp>(0)) == 1> {};

#endif // __has_feature(is_polymorphic)

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_polymorphic_v = is_polymorphic<_Tp>::value;
#endif

// has_virtual_destructor

#if __has_feature(has_virtual_destructor) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS has_virtual_destructor : public integral_constant<bool, __has_virtual_destructor(_Tp)> {};

#else

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS has_virtual_destructor : public false_type {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool has_virtual_destructor_v = has_virtual_destructor<_Tp>::value;
#endif

// has_unique_object_representations

#if _LIBCPP_STD_VER > 14 && defined(_LIBCPP_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS has_unique_object_representations
    : public integral_constant<bool, __has_unique_object_representations(remove_cv_t<remove_all_extents_t<_Tp>>)> {};

#if !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool has_unique_object_representations_v =
    has_unique_object_representations<_Tp>::value;
#endif

#endif

// alignment_of

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS alignment_of : public integral_constant<size_t, alignof(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR size_t alignment_of_v = alignment_of<_Tp>::value;
#endif

// aligned_storage

template <class _Hp, class _Tp> struct __type_list {
  typedef _Hp _Head;
  typedef _Tp _Tail;
};

struct __nat {
#ifndef _LIBCPP_CXX03_LANG
  __nat()              = delete;
  __nat(const __nat &) = delete;
  __nat &operator=(const __nat &) = delete;
  ~__nat()                        = delete;
#endif
};

template <class _Tp> struct __align_type {
  static const size_t value = _LIBCPP_PREFERRED_ALIGNOF(_Tp);
  typedef _Tp type;
};

struct __struct_double {
  long double __lx;
};
struct __struct_double4 {
  double __lx[4];
};

typedef __type_list<
    __align_type<unsigned char>,
    __type_list<
        __align_type<unsigned short>,
        __type_list<
            __align_type<unsigned int>,
            __type_list<
                __align_type<unsigned long>,
                __type_list<
                    __align_type<unsigned long long>,
                    __type_list<__align_type<double>,
                                __type_list<__align_type<long double>,
                                            __type_list<__align_type<__struct_double>,
                                                        __type_list<__align_type<__struct_double4>,
                                                                    __type_list<__align_type<int *>, __nat>>>>>>>>>>
    __all_types;

template <size_t _Align> struct alignas(_Align) __fallback_overaligned {};

template <class _TL, size_t _Align> struct __find_pod;

template <class _Hp, size_t _Align> struct __find_pod<__type_list<_Hp, __nat>, _Align> {
  typedef typename conditional<_Align == _Hp::value, typename _Hp::type, __fallback_overaligned<_Align>>::type type;
};

template <class _Hp, class _Tp, size_t _Align> struct __find_pod<__type_list<_Hp, _Tp>, _Align> {
  typedef
      typename conditional<_Align == _Hp::value, typename _Hp::type, typename __find_pod<_Tp, _Align>::type>::type type;
};

template <class _TL, size_t _Len> struct __find_max_align;

template <class _Hp, size_t _Len>
struct __find_max_align<__type_list<_Hp, __nat>, _Len> : public integral_constant<size_t, _Hp::value> {};

template <size_t _Len, size_t _A1, size_t _A2> struct __select_align {
private:
  static const size_t __min = _A2 < _A1 ? _A2 : _A1;
  static const size_t __max = _A1 < _A2 ? _A2 : _A1;

public:
  static const size_t value = _Len < __max ? __min : __max;
};

template <class _Hp, class _Tp, size_t _Len>
struct __find_max_align<__type_list<_Hp, _Tp>, _Len>
    : public integral_constant<size_t, __select_align<_Len, _Hp::value, __find_max_align<_Tp, _Len>::value>::value> {};

template <size_t _Len, size_t _Align = __find_max_align<__all_types, _Len>::value>
struct _LIBCPP_TEMPLATE_VIS aligned_storage {
  typedef typename __find_pod<__all_types, _Align>::type _Aligner;
  union type {
    _Aligner __align;
    unsigned char __data[(_Len + _Align - 1) / _Align * _Align];
  };
};

#if _LIBCPP_STD_VER > 11
template <size_t _Len, size_t _Align = __find_max_align<__all_types, _Len>::value>
using aligned_storage_t = typename aligned_storage<_Len, _Align>::type;
#endif

#define _CREATE_ALIGNED_STORAGE_SPECIALIZATION(n)                                                                      \
  template <size_t _Len> struct _LIBCPP_TEMPLATE_VIS aligned_storage<_Len, n> {                                        \
    struct alignas(n) type {                                                                                           \
      unsigned char __lx[(_Len + n - 1) / n * n];                                                                      \
    };                                                                                                                 \
  }

_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x2);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x8);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x10);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x20);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x40);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x80);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x100);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x200);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x400);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x800);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1000);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x2000);
// PE/COFF does not support alignment beyond 8192 (=0x2000)
#if !defined(_LIBCPP_OBJECT_FORMAT_COFF)
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4000);
#endif // !defined(_LIBCPP_OBJECT_FORMAT_COFF)

#undef _CREATE_ALIGNED_STORAGE_SPECIALIZATION

// aligned_union

template <size_t _I0, size_t... _In> struct __static_max;

template <size_t _I0> struct __static_max<_I0> { static const size_t value = _I0; };

template <size_t _I0, size_t _I1, size_t... _In> struct __static_max<_I0, _I1, _In...> {
  static const size_t value = _I0 >= _I1 ? __static_max<_I0, _In...>::value : __static_max<_I1, _In...>::value;
};

template <size_t _Len, class _Type0, class... _Types> struct aligned_union {
  static const size_t alignment_value =
      __static_max<_LIBCPP_PREFERRED_ALIGNOF(_Type0), _LIBCPP_PREFERRED_ALIGNOF(_Types)...>::value;
  static const size_t __len = __static_max<_Len, sizeof(_Type0), sizeof(_Types)...>::value;
  typedef typename aligned_storage<__len, alignment_value>::type type;
};

#if _LIBCPP_STD_VER > 11
template <size_t _Len, class... _Types> using aligned_union_t = typename aligned_union<_Len, _Types...>::type;
#endif

template <class _Tp> struct __numeric_type {
  static void __test(...);
  static float __test(float);
  static double __test(char);
  static double __test(int);
  static double __test(unsigned);
  static double __test(long);
  static double __test(unsigned long);
  static double __test(long long);
  static double __test(unsigned long long);
  static double __test(double);
  static long double __test(long double);

  typedef decltype(__test(declval<_Tp>())) type;
  static const bool value = _IsNotSame<type, void>::value;
};

template <> struct __numeric_type<void> { static const bool value = true; };

// __promote

template <class _A1, class _A2 = void, class _A3 = void,
          bool = __numeric_type<_A1>::value &&__numeric_type<_A2>::value &&__numeric_type<_A3>::value>
class __promote_imp {
public:
  static const bool value = false;
};

template <class _A1, class _A2, class _A3> class __promote_imp<_A1, _A2, _A3, true> {
private:
  typedef typename __promote_imp<_A1>::type __type1;
  typedef typename __promote_imp<_A2>::type __type2;
  typedef typename __promote_imp<_A3>::type __type3;

public:
  typedef decltype(__type1() + __type2() + __type3()) type;
  static const bool value = true;
};

template <class _A1, class _A2> class __promote_imp<_A1, _A2, void, true> {
private:
  typedef typename __promote_imp<_A1>::type __type1;
  typedef typename __promote_imp<_A2>::type __type2;

public:
  typedef decltype(__type1() + __type2()) type;
  static const bool value = true;
};

template <class _A1> class __promote_imp<_A1, void, void, true> {
public:
  typedef typename __numeric_type<_A1>::type type;
  static const bool value = true;
};

template <class _A1, class _A2 = void, class _A3 = void> class __promote : public __promote_imp<_A1, _A2, _A3> {};

// make_signed / make_unsigned

typedef __type_list<
    signed char,
    __type_list<signed short, __type_list<signed int, __type_list<signed long, __type_list<signed long long,
#ifndef _LIBCPP_HAS_NO_INT128
                                                                                           __type_list<__int128_t,
#endif
                                                                                                       __nat
#ifndef _LIBCPP_HAS_NO_INT128
                                                                                                       >
#endif
                                                                                           >>>>>
    __signed_types;

typedef __type_list<
    unsigned char, __type_list<unsigned short,
                               __type_list<unsigned int, __type_list<unsigned long, __type_list<unsigned long long,
#ifndef _LIBCPP_HAS_NO_INT128
                                                                                                __type_list<__uint128_t,
#endif
                                                                                                            __nat
#ifndef _LIBCPP_HAS_NO_INT128
                                                                                                            >
#endif
                                                                                                >>>>>
    __unsigned_types;

template <class _TypeList, size_t _Size, bool = _Size <= sizeof(typename _TypeList::_Head)> struct __find_first;

template <class _Hp, class _Tp, size_t _Size> struct __find_first<__type_list<_Hp, _Tp>, _Size, true> {
  typedef _LIBCPP_NODEBUG_TYPE _Hp type;
};

template <class _Hp, class _Tp, size_t _Size> struct __find_first<__type_list<_Hp, _Tp>, _Size, false> {
  typedef _LIBCPP_NODEBUG_TYPE typename __find_first<_Tp, _Size>::type type;
};

template <class _Tp, class _Up, bool = is_const<typename remove_reference<_Tp>::type>::value,
          bool = is_volatile<typename remove_reference<_Tp>::type>::value>
struct __apply_cv {
  typedef _LIBCPP_NODEBUG_TYPE _Up type;
};

template <class _Tp, class _Up> struct __apply_cv<_Tp, _Up, true, false> {
  typedef _LIBCPP_NODEBUG_TYPE const _Up type;
};

template <class _Tp, class _Up> struct __apply_cv<_Tp, _Up, false, true> { typedef volatile _Up type; };

template <class _Tp, class _Up> struct __apply_cv<_Tp, _Up, true, true> { typedef const volatile _Up type; };

template <class _Tp, class _Up> struct __apply_cv<_Tp &, _Up, false, false> { typedef _Up &type; };

template <class _Tp, class _Up> struct __apply_cv<_Tp &, _Up, true, false> { typedef const _Up &type; };

template <class _Tp, class _Up> struct __apply_cv<_Tp &, _Up, false, true> { typedef volatile _Up &type; };

template <class _Tp, class _Up> struct __apply_cv<_Tp &, _Up, true, true> { typedef const volatile _Up &type; };

template <class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value> struct __make_signed {};

template <class _Tp> struct __make_signed<_Tp, true> {
  typedef typename __find_first<__signed_types, sizeof(_Tp)>::type type;
};

template <> struct __make_signed<bool, true> {};
template <> struct __make_signed<signed short, true> { typedef short type; };
template <> struct __make_signed<unsigned short, true> { typedef short type; };
template <> struct __make_signed<signed int, true> { typedef int type; };
template <> struct __make_signed<unsigned int, true> { typedef int type; };
template <> struct __make_signed<signed long, true> { typedef long type; };
template <> struct __make_signed<unsigned long, true> { typedef long type; };
template <> struct __make_signed<signed long long, true> { typedef long long type; };
template <> struct __make_signed<unsigned long long, true> { typedef long long type; };
#ifndef _LIBCPP_HAS_NO_INT128
template <> struct __make_signed<__int128_t, true> { typedef __int128_t type; };
template <> struct __make_signed<__uint128_t, true> { typedef __int128_t type; };
#endif

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS make_signed {
  typedef typename __apply_cv<_Tp, typename __make_signed<typename remove_cv<_Tp>::type>::type>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using make_signed_t = typename make_signed<_Tp>::type;
#endif

template <class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value> struct __make_unsigned {};

template <class _Tp> struct __make_unsigned<_Tp, true> {
  typedef typename __find_first<__unsigned_types, sizeof(_Tp)>::type type;
};

template <> struct __make_unsigned<bool, true> {};
template <> struct __make_unsigned<signed short, true> { typedef unsigned short type; };
template <> struct __make_unsigned<unsigned short, true> { typedef unsigned short type; };
template <> struct __make_unsigned<signed int, true> { typedef unsigned int type; };
template <> struct __make_unsigned<unsigned int, true> { typedef unsigned int type; };
template <> struct __make_unsigned<signed long, true> { typedef unsigned long type; };
template <> struct __make_unsigned<unsigned long, true> { typedef unsigned long type; };
template <> struct __make_unsigned<signed long long, true> { typedef unsigned long long type; };
template <> struct __make_unsigned<unsigned long long, true> { typedef unsigned long long type; };
#ifndef _LIBCPP_HAS_NO_INT128
template <> struct __make_unsigned<__int128_t, true> { typedef __uint128_t type; };
template <> struct __make_unsigned<__uint128_t, true> { typedef __uint128_t type; };
#endif

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS make_unsigned {
  typedef typename __apply_cv<_Tp, typename __make_unsigned<typename remove_cv<_Tp>::type>::type>::type type;
};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using make_unsigned_t = typename make_unsigned<_Tp>::type;
#endif

#if _LIBCPP_STD_VER > 14
template <class...> using void_t = void;
#endif

#if _LIBCPP_STD_VER > 17
// Let COND_RES(X, Y) be:
template <class _Tp, class _Up> using __cond_type = decltype(false ? _VSTD::declval<_Tp>() : _VSTD::declval<_Up>());

template <class _Tp, class _Up, class = void> struct __common_type3 {};

// sub-bullet 4 - "if COND_RES(CREF(D1), CREF(D2)) denotes a type..."
template <class _Tp, class _Up> struct __common_type3<_Tp, _Up, void_t<__cond_type<const _Tp &, const _Up &>>> {
  using type = remove_cvref_t<__cond_type<const _Tp &, const _Up &>>;
};

template <class _Tp, class _Up, class = void> struct __common_type2_imp : __common_type3<_Tp, _Up> {};
#else
template <class _Tp, class _Up, class = void> struct __common_type2_imp {};
#endif

// sub-bullet 3 - "if decay_t<decltype(false ? declval<D1>() : declval<D2>())> ..."
template <class _Tp, class _Up>
struct __common_type2_imp<_Tp, _Up,
                          typename __void_t<decltype(true ? _VSTD::declval<_Tp>() : _VSTD::declval<_Up>())>::type> {
  typedef _LIBCPP_NODEBUG_TYPE
      typename decay<decltype(true ? _VSTD::declval<_Tp>() : _VSTD::declval<_Up>())>::type type;
};

template <class, class = void> struct __common_type_impl {};

// Clang provides variadic templates in C++03 as an extension.
#if !defined(_LIBCPP_CXX03_LANG) || defined(__clang__)
#define _LIBCPP_OPTIONAL_PACK(...) , __VA_ARGS__
template <class... Tp> struct __common_types;
template <class... _Tp> struct _LIBCPP_TEMPLATE_VIS common_type;
#else
#define _LIBCPP_OPTIONAL_PACK(...)
struct __no_arg;
template <class _Tp, class _Up, class = __no_arg> struct __common_types;
template <class _Tp = __no_arg, class _Up = __no_arg, class _Vp = __no_arg, class _Unused = __no_arg>
struct common_type {
  static_assert(sizeof(_Unused) == 0, "common_type accepts at most 3 arguments in C++03");
};
#endif // _LIBCPP_CXX03_LANG

template <class _Tp, class _Up>
struct __common_type_impl<__common_types<_Tp, _Up>, typename __void_t<typename common_type<_Tp, _Up>::type>::type> {
  typedef typename common_type<_Tp, _Up>::type type;
};

template <class _Tp, class _Up, class _Vp _LIBCPP_OPTIONAL_PACK(class... _Rest)>
struct __common_type_impl<__common_types<_Tp, _Up, _Vp _LIBCPP_OPTIONAL_PACK(_Rest...)>,
                          typename __void_t<typename common_type<_Tp, _Up>::type>::type>
    : __common_type_impl<__common_types<typename common_type<_Tp, _Up>::type, _Vp _LIBCPP_OPTIONAL_PACK(_Rest...)>> {};

// bullet 1 - sizeof...(Tp) == 0

template <> struct _LIBCPP_TEMPLATE_VIS common_type<> {};

// bullet 2 - sizeof...(Tp) == 1

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS common_type<_Tp> : public common_type<_Tp, _Tp> {};

// bullet 3 - sizeof...(Tp) == 2

// sub-bullet 1 - "If is_same_v<T1, D1> is false or ..."
template <class _Tp, class _Up>
struct _LIBCPP_TEMPLATE_VIS common_type<_Tp, _Up>
    : conditional<_IsSame<_Tp, typename decay<_Tp>::type>::value && _IsSame<_Up, typename decay<_Up>::type>::value,
                  __common_type2_imp<_Tp, _Up>,
                  common_type<typename decay<_Tp>::type, typename decay<_Up>::type>>::type {};

// bullet 4 - sizeof...(Tp) > 2

template <class _Tp, class _Up, class _Vp _LIBCPP_OPTIONAL_PACK(class... _Rest)>
struct _LIBCPP_TEMPLATE_VIS common_type<_Tp, _Up, _Vp _LIBCPP_OPTIONAL_PACK(_Rest...)>
    : __common_type_impl<__common_types<_Tp, _Up, _Vp _LIBCPP_OPTIONAL_PACK(_Rest...)>> {};

#undef _LIBCPP_OPTIONAL_PACK

#if _LIBCPP_STD_VER > 11
template <class... _Tp> using common_type_t = typename common_type<_Tp...>::type;
#endif

// is_assignable

template <typename, typename _Tp> struct __select_2nd { typedef _LIBCPP_NODEBUG_TYPE _Tp type; };

#if __has_keyword(__is_assignable)

template <class _Tp, class _Up> struct _LIBCPP_TEMPLATE_VIS is_assignable : _BoolConstant<__is_assignable(_Tp, _Up)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Arg> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_assignable_v = __is_assignable(_Tp, _Arg);
#endif

#else // __has_keyword(__is_assignable)

template <class _Tp, class _Arg>
typename __select_2nd<decltype((_VSTD::declval<_Tp>() = _VSTD::declval<_Arg>())), true_type>::type
__is_assignable_test(int);

template <class, class> false_type __is_assignable_test(...);

template <class _Tp, class _Arg, bool = is_void<_Tp>::value || is_void<_Arg>::value>
struct __is_assignable_imp : public decltype((_VSTD::__is_assignable_test<_Tp, _Arg>(0))) {};

template <class _Tp, class _Arg> struct __is_assignable_imp<_Tp, _Arg, true> : public false_type {};

template <class _Tp, class _Arg> struct is_assignable : public __is_assignable_imp<_Tp, _Arg> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Arg>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_assignable_v = is_assignable<_Tp, _Arg>::value;
#endif

#endif // __has_keyword(__is_assignable)

// is_copy_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_copy_assignable
    : public is_assignable<typename add_lvalue_reference<_Tp>::type,
                           typename add_lvalue_reference<typename add_const<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_copy_assignable_v = is_copy_assignable<_Tp>::value;
#endif

// is_move_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_move_assignable
    : public is_assignable<typename add_lvalue_reference<_Tp>::type, typename add_rvalue_reference<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_move_assignable_v = is_move_assignable<_Tp>::value;
#endif

// is_destructible

#if __has_keyword(__is_destructible)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_destructible : _BoolConstant<__is_destructible(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_destructible_v = __is_destructible(_Tp);
#endif

#else // __has_keyword(__is_destructible)

//  if it's a reference, return true
//  if it's a function, return false
//  if it's   void,     return false
//  if it's an array of unknown bound, return false
//  Otherwise, return "declval<_Up&>().~_Up()" is well-formed
//    where _Up is remove_all_extents<_Tp>::type

template <class> struct __is_destructible_apply { typedef int type; };

template <typename _Tp> struct __is_destructor_wellformed {
  template <typename _Tp1>
  static char __test(typename __is_destructible_apply<decltype(_VSTD::declval<_Tp1 &>().~_Tp1())>::type);

  template <typename _Tp1> static __two __test(...);

  static const bool value = sizeof(__test<_Tp>(12)) == sizeof(char);
};

template <class _Tp, bool> struct __destructible_imp;

template <class _Tp>
struct __destructible_imp<_Tp, false>
    : public _VSTD::integral_constant<
          bool, __is_destructor_wellformed<typename _VSTD::remove_all_extents<_Tp>::type>::value> {};

template <class _Tp> struct __destructible_imp<_Tp, true> : public _VSTD::true_type {};

template <class _Tp, bool> struct __destructible_false;

template <class _Tp>
struct __destructible_false<_Tp, false> : public __destructible_imp<_Tp, _VSTD::is_reference<_Tp>::value> {};

template <class _Tp> struct __destructible_false<_Tp, true> : public _VSTD::false_type {};

template <class _Tp> struct is_destructible : public __destructible_false<_Tp, _VSTD::is_function<_Tp>::value> {};

template <class _Tp> struct is_destructible<_Tp[]> : public _VSTD::false_type {};

template <> struct is_destructible<void> : public _VSTD::false_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_destructible_v = is_destructible<_Tp>::value;
#endif

#endif // __has_keyword(__is_destructible)

// move

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR typename remove_reference<_Tp>::type &&move(_Tp &&__t) _NOEXCEPT {
  typedef _LIBCPP_NODEBUG_TYPE typename remove_reference<_Tp>::type _Up;
  return static_cast<_Up &&>(__t);
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR _Tp &&forward(typename remove_reference<_Tp>::type &__t) _NOEXCEPT {
  return static_cast<_Tp &&>(__t);
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR _Tp &&forward(typename remove_reference<_Tp>::type &&__t) _NOEXCEPT {
  static_assert(!is_lvalue_reference<_Tp>::value, "can not forward an rvalue as an lvalue");
  return static_cast<_Tp &&>(__t);
}

template <class _Tp> inline _LIBCPP_INLINE_VISIBILITY typename decay<_Tp>::type __decay_copy(_Tp &&__t) {
  return _VSTD::forward<_Tp>(__t);
}

template <class _MP, bool _IsMemberFunctionPtr, bool _IsMemberObjectPtr> struct __member_pointer_traits_imp {};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...), true, false> {
  typedef _Class _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...), true, false> {
  typedef _Class _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const, true, false> {
  typedef _Class const _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const, true, false> {
  typedef _Class const _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile, true, false> {
  typedef _Class volatile _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile, true, false> {
  typedef _Class volatile _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile, true, false> {
  typedef _Class const volatile _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile, true, false> {
  typedef _Class const volatile _ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

#if __has_feature(cxx_reference_qualified_functions) || defined(_LIBCPP_COMPILER_GCC)

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &, true, false> {
  typedef _Class &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) &, true, false> {
  typedef _Class &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const &, true, false> {
  typedef _Class const &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const &, true, false> {
  typedef _Class const &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile &, true, false> {
  typedef _Class volatile &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile &, true, false> {
  typedef _Class volatile &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile &, true, false> {
  typedef _Class const volatile &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile &, true, false> {
  typedef _Class const volatile &_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &&, true, false> {
  typedef _Class &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) &&, true, false> {
  typedef _Class &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const &&, true, false> {
  typedef _Class const &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const &&, true, false> {
  typedef _Class const &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile &&, true, false> {
  typedef _Class volatile &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile &&, true, false> {
  typedef _Class volatile &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile &&, true, false> {
  typedef _Class const volatile &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param...);
};

template <class _Rp, class _Class, class... _Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile &&, true, false> {
  typedef _Class const volatile &&_ClassType;
  typedef _Rp _ReturnType;
  typedef _Rp(_FnType)(_Param..., ...);
};

#endif // __has_feature(cxx_reference_qualified_functions) || defined(_LIBCPP_COMPILER_GCC)

template <class _Rp, class _Class> struct __member_pointer_traits_imp<_Rp _Class::*, false, true> {
  typedef _Class _ClassType;
  typedef _Rp _ReturnType;
};

template <class _MP>
struct __member_pointer_traits
    : public __member_pointer_traits_imp<typename remove_cv<_MP>::type, is_member_function_pointer<_MP>::value,
                                         is_member_object_pointer<_MP>::value> {
  //     typedef ... _ClassType;
  //     typedef ... _ReturnType;
  //     typedef ... _FnType;
};

template <class _DecayedFp> struct __member_pointer_class_type {};

template <class _Ret, class _ClassType> struct __member_pointer_class_type<_Ret _ClassType::*> {
  typedef _ClassType type;
};

// template <class T, class... Args> struct is_constructible;

namespace __is_construct {
struct __nat {};
} // namespace __is_construct

#if defined(_LIBCPP_COMPILER_GCC) && _GNUC_VER_NEW >= 10000
#define _LIBCPP_GCC_SUPPORTS_IS_CONSTRUCTIBLE
#endif

#if !defined(_LIBCPP_CXX03_LANG) && !__has_feature(is_constructible) && !defined(_LIBCPP_GCC_SUPPORTS_IS_CONSTRUCTIBLE)

template <class _Tp, class... _Args> struct __libcpp_is_constructible;

template <class _To, class _From> struct __is_invalid_base_to_derived_cast {
  static_assert(is_reference<_To>::value, "Wrong specialization");
  using _RawFrom          = __uncvref_t<_From>;
  using _RawTo            = __uncvref_t<_To>;
  static const bool value = _And<_IsNotSame<_RawFrom, _RawTo>, is_base_of<_RawFrom, _RawTo>,
                                 _Not<__libcpp_is_constructible<_RawTo, _From>>>::value;
};

template <class _To, class _From> struct __is_invalid_lvalue_to_rvalue_cast : false_type {
  static_assert(is_reference<_To>::value, "Wrong specialization");
};

template <class _ToRef, class _FromRef> struct __is_invalid_lvalue_to_rvalue_cast<_ToRef &&, _FromRef &> {
  using _RawFrom = __uncvref_t<_FromRef>;
  using _RawTo   = __uncvref_t<_ToRef>;
  static const bool value =
      _And<_Not<is_function<_RawTo>>, _Or<_IsSame<_RawFrom, _RawTo>, is_base_of<_RawTo, _RawFrom>>>::value;
};

struct __is_constructible_helper {
  template <class _To> static void __eat(_To);

  // This overload is needed to work around a Clang bug that disallows
  // static_cast<T&&>(e) for non-reference-compatible types.
  // Example: static_cast<int&&>(declval<double>());
  // NOTE: The static_cast implementation below is required to support
  //  classes with explicit conversion operators.
  template <class _To, class _From, class = decltype(__eat<_To>(_VSTD::declval<_From>()))>
  static true_type __test_cast(int);

  template <class _To, class _From, class = decltype(static_cast<_To>(_VSTD::declval<_From>()))>
  static integral_constant<bool, !__is_invalid_base_to_derived_cast<_To, _From>::value &&
                                     !__is_invalid_lvalue_to_rvalue_cast<_To, _From>::value>
  __test_cast(long);

  template <class, class> static false_type __test_cast(...);

  template <class _Tp, class... _Args, class = decltype(_Tp(_VSTD::declval<_Args>()...))>
  static true_type __test_nary(int);
  template <class _Tp, class...> static false_type __test_nary(...);

  template <class _Tp, class _A0, class = decltype(::new _Tp(_VSTD::declval<_A0>()))>
  static is_destructible<_Tp> __test_unary(int);
  template <class, class> static false_type __test_unary(...);
};

template <class _Tp, bool = is_void<_Tp>::value>
struct __is_default_constructible : decltype(__is_constructible_helper::__test_nary<_Tp>(0)) {};

template <class _Tp> struct __is_default_constructible<_Tp, true> : false_type {};

template <class _Tp> struct __is_default_constructible<_Tp[], false> : false_type {};

template <class _Tp, size_t _Nx>
struct __is_default_constructible<_Tp[_Nx], false>
    : __is_default_constructible<typename remove_all_extents<_Tp>::type> {};

template <class _Tp, class... _Args> struct __libcpp_is_constructible {
  static_assert(sizeof...(_Args) > 1, "Wrong specialization");
  typedef decltype(__is_constructible_helper::__test_nary<_Tp, _Args...>(0)) type;
};

template <class _Tp> struct __libcpp_is_constructible<_Tp> : __is_default_constructible<_Tp> {};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp, _A0> : public decltype(__is_constructible_helper::__test_unary<_Tp, _A0>(0)) {};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp &, _A0> : public decltype(__is_constructible_helper::__test_cast<_Tp &, _A0>(0)) {
};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp &&, _A0>
    : public decltype(__is_constructible_helper::__test_cast<_Tp &&, _A0>(0)) {};

#endif

#if __has_feature(is_constructible) || defined(_LIBCPP_GCC_SUPPORTS_IS_CONSTRUCTIBLE)
template <class _Tp, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_constructible : public integral_constant<bool, __is_constructible(_Tp, _Args...)> {};
#else
template <class _Tp, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_constructible : public __libcpp_is_constructible<_Tp, _Args...>::type {};
#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class... _Args>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_constructible_v = is_constructible<_Tp, _Args...>::value;
#endif

// is_default_constructible

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_default_constructible : public is_constructible<_Tp> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_default_constructible_v = is_default_constructible<_Tp>::value;
#endif

#ifndef _LIBCPP_CXX03_LANG
// First of all, we can't implement this check in C++03 mode because the {}
// default initialization syntax isn't valid.
// Second, we implement the trait in a funny manner with two defaulted template
// arguments to workaround Clang's PR43454.
template <class _Tp> void __test_implicit_default_constructible(_Tp);

template <class _Tp, class = void, bool = is_default_constructible<_Tp>::value>
struct __is_implicitly_default_constructible : false_type {};

template <class _Tp>
struct __is_implicitly_default_constructible<_Tp, decltype(__test_implicit_default_constructible<_Tp const &>({})),
                                             true> : true_type {};

template <class _Tp>
struct __is_implicitly_default_constructible<_Tp, decltype(__test_implicit_default_constructible<_Tp const &>({})),
                                             false> : false_type {};
#endif // !C++03

// is_copy_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_copy_constructible
    : public is_constructible<_Tp, typename add_lvalue_reference<typename add_const<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_copy_constructible_v = is_copy_constructible<_Tp>::value;
#endif

// is_move_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_move_constructible
    : public is_constructible<_Tp, typename add_rvalue_reference<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_move_constructible_v = is_move_constructible<_Tp>::value;
#endif

// is_trivially_constructible

#if __has_feature(is_trivially_constructible) || _GNUC_VER >= 501

template <class _Tp, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible
    : integral_constant<bool, __is_trivially_constructible(_Tp, _Args...)> {};

#else // !__has_feature(is_trivially_constructible)

template <class _Tp, class... _Args> struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible : false_type {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible<_Tp>
#if __has_feature(has_trivial_constructor) || defined(_LIBCPP_COMPILER_GCC)
    : integral_constant<bool, __has_trivial_constructor(_Tp)>
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
#endif
{
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible<_Tp, _Tp &&> : integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible<_Tp, const _Tp &>
    : integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_constructible<_Tp, _Tp &> : integral_constant<bool, is_scalar<_Tp>::value> {};

#endif // !__has_feature(is_trivially_constructible)

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class... _Args>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_constructible_v =
    is_trivially_constructible<_Tp, _Args...>::value;
#endif

// is_trivially_default_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_default_constructible : public is_trivially_constructible<_Tp> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<_Tp>::value;
#endif

// is_trivially_copy_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_copy_constructible
    : public is_trivially_constructible<_Tp, typename add_lvalue_reference<const _Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_copy_constructible_v =
    is_trivially_copy_constructible<_Tp>::value;
#endif

// is_trivially_move_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_move_constructible
    : public is_trivially_constructible<_Tp, typename add_rvalue_reference<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_move_constructible_v =
    is_trivially_move_constructible<_Tp>::value;
#endif

// is_trivially_assignable

#if __has_feature(is_trivially_assignable) || _GNUC_VER >= 501

template <class _Tp, class _Arg>
struct is_trivially_assignable : integral_constant<bool, __is_trivially_assignable(_Tp, _Arg)> {};

#else // !__has_feature(is_trivially_assignable)

template <class _Tp, class _Arg> struct is_trivially_assignable : public false_type {};

template <class _Tp> struct is_trivially_assignable<_Tp &, _Tp> : integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp> struct is_trivially_assignable<_Tp &, _Tp &> : integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_assignable<_Tp &, const _Tp &> : integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp> struct is_trivially_assignable<_Tp &, _Tp &&> : integral_constant<bool, is_scalar<_Tp>::value> {};

#endif // !__has_feature(is_trivially_assignable)

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Arg>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_assignable_v = is_trivially_assignable<_Tp, _Arg>::value;
#endif

// is_trivially_copy_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_copy_assignable
    : public is_trivially_assignable<typename add_lvalue_reference<_Tp>::type,
                                     typename add_lvalue_reference<typename add_const<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<_Tp>::value;
#endif

// is_trivially_move_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_move_assignable
    : public is_trivially_assignable<typename add_lvalue_reference<_Tp>::type,
                                     typename add_rvalue_reference<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_move_assignable_v = is_trivially_move_assignable<_Tp>::value;
#endif

// is_trivially_destructible

#if __has_keyword(__is_trivially_destructible)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_destructible
    : public integral_constant<bool, __is_trivially_destructible(_Tp)> {};

#elif __has_feature(has_trivial_destructor) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_destructible
    : public integral_constant<bool, is_destructible<_Tp>::value &&__has_trivial_destructor(_Tp)> {};

#else

template <class _Tp>
struct __libcpp_trivial_destructor : public integral_constant<bool, is_scalar<_Tp>::value || is_reference<_Tp>::value> {
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_destructible
    : public __libcpp_trivial_destructor<typename remove_all_extents<_Tp>::type> {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_trivially_destructible<_Tp[]> : public false_type {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_destructible_v = is_trivially_destructible<_Tp>::value;
#endif

// is_nothrow_constructible

#if __has_keyword(__is_nothrow_constructible)

template <class _Tp, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible
    : public integral_constant<bool, __is_nothrow_constructible(_Tp, _Args...)> {};

#else

template <bool, bool, class _Tp, class... _Args> struct __libcpp_is_nothrow_constructible;

template <class _Tp, class... _Args>
struct __libcpp_is_nothrow_constructible</*is constructible*/ true, /*is reference*/ false, _Tp, _Args...>
    : public integral_constant<bool, noexcept(_Tp(declval<_Args>()...))> {};

template <class _Tp> void __implicit_conversion_to(_Tp) noexcept {}

template <class _Tp, class _Arg>
struct __libcpp_is_nothrow_constructible</*is constructible*/ true, /*is reference*/ true, _Tp, _Arg>
    : public integral_constant<bool, noexcept(_VSTD::__implicit_conversion_to<_Tp>(declval<_Arg>()))> {};

template <class _Tp, bool _IsReference, class... _Args>
struct __libcpp_is_nothrow_constructible</*is constructible*/ false, _IsReference, _Tp, _Args...> : public false_type {
};

template <class _Tp, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible
    : __libcpp_is_nothrow_constructible<is_constructible<_Tp, _Args...>::value, is_reference<_Tp>::value, _Tp,
                                        _Args...> {};

template <class _Tp, size_t _Ns>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible<_Tp[_Ns]>
    : __libcpp_is_nothrow_constructible<is_constructible<_Tp>::value, is_reference<_Tp>::value, _Tp> {};

#endif // _LIBCPP_HAS_NO_NOEXCEPT

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class... _Args>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_constructible_v = is_nothrow_constructible<_Tp, _Args...>::value;
#endif

// is_nothrow_default_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_default_constructible : public is_nothrow_constructible<_Tp> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_default_constructible_v =
    is_nothrow_default_constructible<_Tp>::value;
#endif

// is_nothrow_copy_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_copy_constructible
    : public is_nothrow_constructible<_Tp, typename add_lvalue_reference<typename add_const<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<_Tp>::value;
#endif

// is_nothrow_move_constructible

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_move_constructible
    : public is_nothrow_constructible<_Tp, typename add_rvalue_reference<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<_Tp>::value;
#endif

// is_nothrow_assignable

#if __has_keyword(__is_nothrow_assignable)

template <class _Tp, class _Arg>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_assignable : public integral_constant<bool, __is_nothrow_assignable(_Tp, _Arg)> {
};

#else

template <bool, class _Tp, class _Arg> struct __libcpp_is_nothrow_assignable;

template <class _Tp, class _Arg> struct __libcpp_is_nothrow_assignable<false, _Tp, _Arg> : public false_type {};

template <class _Tp, class _Arg>
struct __libcpp_is_nothrow_assignable<true, _Tp, _Arg>
    : public integral_constant<bool, noexcept(_VSTD::declval<_Tp>() = _VSTD::declval<_Arg>())> {};

template <class _Tp, class _Arg>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_assignable
    : public __libcpp_is_nothrow_assignable<is_assignable<_Tp, _Arg>::value, _Tp, _Arg> {};

#endif // _LIBCPP_HAS_NO_NOEXCEPT

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp, class _Arg>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_assignable_v = is_nothrow_assignable<_Tp, _Arg>::value;
#endif

// is_nothrow_copy_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_copy_assignable
    : public is_nothrow_assignable<typename add_lvalue_reference<_Tp>::type,
                                   typename add_lvalue_reference<typename add_const<_Tp>::type>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<_Tp>::value;
#endif

// is_nothrow_move_assignable

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_move_assignable
    : public is_nothrow_assignable<typename add_lvalue_reference<_Tp>::type, typename add_rvalue_reference<_Tp>::type> {
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<_Tp>::value;
#endif

// is_nothrow_destructible

#if !defined(_LIBCPP_CXX03_LANG)

template <bool, class _Tp> struct __libcpp_is_nothrow_destructible;

template <class _Tp> struct __libcpp_is_nothrow_destructible<false, _Tp> : public false_type {};

template <class _Tp>
struct __libcpp_is_nothrow_destructible<true, _Tp>
    : public integral_constant<bool, noexcept(_VSTD::declval<_Tp>().~_Tp())> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible
    : public __libcpp_is_nothrow_destructible<is_destructible<_Tp>::value, _Tp> {};

template <class _Tp, size_t _Ns>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp[_Ns]> : public is_nothrow_destructible<_Tp> {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp &> : public true_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp &&> : public true_type {};

#else

template <class _Tp>
struct __libcpp_nothrow_destructor : public integral_constant<bool, is_scalar<_Tp>::value || is_reference<_Tp>::value> {
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible
    : public __libcpp_nothrow_destructor<typename remove_all_extents<_Tp>::type> {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp[]> : public false_type {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_nothrow_destructible_v = is_nothrow_destructible<_Tp>::value;
#endif

// is_pod

#if __has_feature(is_pod) || defined(_LIBCPP_COMPILER_GCC)

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_pod : public integral_constant<bool, __is_pod(_Tp)> {};

#else

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_pod
    : public integral_constant<
          bool, is_trivially_default_constructible<_Tp>::value && is_trivially_copy_constructible<_Tp>::value &&
                    is_trivially_copy_assignable<_Tp>::value && is_trivially_destructible<_Tp>::value> {};

#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_pod_v = is_pod<_Tp>::value;
#endif

// is_literal_type;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_literal_type : public integral_constant<bool, __is_literal_type(_Tp)> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_literal_type_v = is_literal_type<_Tp>::value;
#endif

// is_standard_layout;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_standard_layout
#if __has_feature(is_standard_layout) || defined(_LIBCPP_COMPILER_GCC)
    : public integral_constant<bool, __is_standard_layout(_Tp)>
#else
    : integral_constant<bool, is_scalar<typename remove_all_extents<_Tp>::type>::value>
#endif
{
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_standard_layout_v = is_standard_layout<_Tp>::value;
#endif

// is_trivially_copyable;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivially_copyable
#if __has_feature(is_trivially_copyable)
    : public integral_constant<bool, __is_trivially_copyable(_Tp)>
#elif _GNUC_VER >= 501
    : public integral_constant<bool, !is_volatile<_Tp>::value && __is_trivially_copyable(_Tp)>
#else
    : integral_constant<bool, is_scalar<typename remove_all_extents<_Tp>::type>::value>
#endif
{
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivially_copyable_v = is_trivially_copyable<_Tp>::value;
#endif

// is_trivial;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_trivial
#if __has_feature(is_trivial) || defined(_LIBCPP_COMPILER_GCC)
    : public integral_constant<bool, __is_trivial(_Tp)>
#else
    : integral_constant<bool, is_trivially_copyable<_Tp>::value && is_trivially_default_constructible<_Tp>::value>
#endif
{
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp> _LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_trivial_v = is_trivial<_Tp>::value;
#endif

template <class _Tp> struct __is_reference_wrapper_impl : public false_type {};
template <class _Tp> struct __is_reference_wrapper_impl<reference_wrapper<_Tp>> : public true_type {};
template <class _Tp>
struct __is_reference_wrapper : public __is_reference_wrapper_impl<typename remove_cv<_Tp>::type> {};

#ifndef _LIBCPP_CXX03_LANG

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type,
          class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet1 =
    typename enable_if<is_member_function_pointer<_DecayFp>::value && is_base_of<_ClassT, _DecayA0>::value>::type;

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type>
using __enable_if_bullet2 =
    typename enable_if<is_member_function_pointer<_DecayFp>::value && __is_reference_wrapper<_DecayA0>::value>::type;

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type,
          class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet3 =
    typename enable_if<is_member_function_pointer<_DecayFp>::value && !is_base_of<_ClassT, _DecayA0>::value &&
                       !__is_reference_wrapper<_DecayA0>::value>::type;

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type,
          class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet4 =
    typename enable_if<is_member_object_pointer<_DecayFp>::value && is_base_of<_ClassT, _DecayA0>::value>::type;

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type>
using __enable_if_bullet5 =
    typename enable_if<is_member_object_pointer<_DecayFp>::value && __is_reference_wrapper<_DecayA0>::value>::type;

template <class _Fp, class _A0, class _DecayFp = typename decay<_Fp>::type, class _DecayA0 = typename decay<_A0>::type,
          class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet6 =
    typename enable_if<is_member_object_pointer<_DecayFp>::value && !is_base_of<_ClassT, _DecayA0>::value &&
                       !__is_reference_wrapper<_DecayA0>::value>::type;

// __invoke forward declarations

// fall back - none of the bullets

#define _LIBCPP_INVOKE_RETURN(...)                                                                                     \
  noexcept(noexcept(__VA_ARGS__))->decltype(__VA_ARGS__) { return __VA_ARGS__; }

template <class... _Args> auto __invoke(__any, _Args &&...__args) -> __nat;

template <class... _Args> auto __invoke_constexpr(__any, _Args &&...__args) -> __nat;

// bullets 1, 2 and 3

template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet1<_Fp, _A0>>
inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
    _LIBCPP_INVOKE_RETURN((_VSTD::forward<_A0>(__a0).*__f)(_VSTD::forward<_Args>(__args)...))

        template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet1<_Fp, _A0>>
        inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
        _LIBCPP_INVOKE_RETURN((_VSTD::forward<_A0>(__a0).*__f)(_VSTD::forward<_Args>(__args)...))

            template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet2<_Fp, _A0>>
            inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
                _LIBCPP_INVOKE_RETURN((__a0.get().*__f)(_VSTD::forward<_Args>(__args)...))

                    template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet2<_Fp, _A0>>
                    inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
        _LIBCPP_INVOKE_RETURN((__a0.get().*__f)(_VSTD::forward<_Args>(__args)...))

            template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet3<_Fp, _A0>>
            inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
                _LIBCPP_INVOKE_RETURN(((*_VSTD::forward<_A0>(__a0)).*__f)(_VSTD::forward<_Args>(__args)...))

                    template <class _Fp, class _A0, class... _Args, class = __enable_if_bullet3<_Fp, _A0>>
                    inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0, _Args &&...__args)
        _LIBCPP_INVOKE_RETURN(((*_VSTD::forward<_A0>(__a0)).*__f)(_VSTD::forward<_Args>(__args)...))

    // bullets 4, 5 and 6

    template <class _Fp, class _A0, class = __enable_if_bullet4<_Fp, _A0>>
    inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0)
        _LIBCPP_INVOKE_RETURN(_VSTD::forward<_A0>(__a0).*__f)

            template <class _Fp, class _A0, class = __enable_if_bullet4<_Fp, _A0>>
            inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0) _LIBCPP_INVOKE_RETURN(_VSTD::forward<_A0>(__a0).*__f)

        template <class _Fp, class _A0, class = __enable_if_bullet5<_Fp, _A0>>
        inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0) _LIBCPP_INVOKE_RETURN(__a0.get().*__f)

            template <class _Fp, class _A0, class = __enable_if_bullet5<_Fp, _A0>>
            inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0) _LIBCPP_INVOKE_RETURN(__a0.get().*__f)

        template <class _Fp, class _A0, class = __enable_if_bullet6<_Fp, _A0>>
        inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _A0 &&__a0)
            _LIBCPP_INVOKE_RETURN((*_VSTD::forward<_A0>(__a0)).*__f)

                template <class _Fp, class _A0, class = __enable_if_bullet6<_Fp, _A0>>
                inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR auto __invoke_constexpr(_Fp &&__f, _A0 &&__a0)
                    _LIBCPP_INVOKE_RETURN((*_VSTD::forward<_A0>(__a0)).*__f)

    // bullet 7

    template <class _Fp, class... _Args>
    inline _LIBCPP_INLINE_VISIBILITY auto __invoke(_Fp &&__f, _Args &&...__args)
        _LIBCPP_INVOKE_RETURN(_VSTD::forward<_Fp>(__f)(_VSTD::forward<_Args>(__args)...))

            template <class _Fp, class... _Args>
            inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR auto __invoke_constexpr(_Fp &&__f, _Args &&...__args)
                _LIBCPP_INVOKE_RETURN(_VSTD::forward<_Fp>(__f)(_VSTD::forward<_Args>(__args)...))

#undef _LIBCPP_INVOKE_RETURN

    // __invokable
    template <class _Ret, class _Fp, class... _Args>
    struct __invokable_r {
  template <class _XFp, class... _XArgs>
  static auto __try_call(int) -> decltype(_VSTD::__invoke(_VSTD::declval<_XFp>(), _VSTD::declval<_XArgs>()...));
  template <class _XFp, class... _XArgs> static __nat __try_call(...);

  // FIXME: Check that _Ret, _Fp, and _Args... are all complete types, cv void,
  // or incomplete array types as required by the standard.
  using _Result = decltype(__try_call<_Fp, _Args...>(0));

  using type =
      typename conditional<_IsNotSame<_Result, __nat>::value,
                           typename conditional<is_void<_Ret>::value, true_type, is_convertible<_Result, _Ret>>::type,
                           false_type>::type;
  static const bool value = type::value;
};
template <class _Fp, class... _Args> using __invokable = __invokable_r<void, _Fp, _Args...>;

template <bool _IsInvokable, bool _IsCVVoid, class _Ret, class _Fp, class... _Args> struct __nothrow_invokable_r_imp {
  static const bool value = false;
};

template <class _Ret, class _Fp, class... _Args> struct __nothrow_invokable_r_imp<true, false, _Ret, _Fp, _Args...> {
  typedef __nothrow_invokable_r_imp _ThisT;

  template <class _Tp> static void __test_noexcept(_Tp) noexcept;

  static const bool value =
      noexcept(_ThisT::__test_noexcept<_Ret>(_VSTD::__invoke(_VSTD::declval<_Fp>(), _VSTD::declval<_Args>()...)));
};

template <class _Ret, class _Fp, class... _Args> struct __nothrow_invokable_r_imp<true, true, _Ret, _Fp, _Args...> {
  static const bool value = noexcept(_VSTD::__invoke(_VSTD::declval<_Fp>(), _VSTD::declval<_Args>()...));
};

template <class _Ret, class _Fp, class... _Args>
using __nothrow_invokable_r =
    __nothrow_invokable_r_imp<__invokable_r<_Ret, _Fp, _Args...>::value, is_void<_Ret>::value, _Ret, _Fp, _Args...>;

template <class _Fp, class... _Args>
using __nothrow_invokable = __nothrow_invokable_r_imp<__invokable<_Fp, _Args...>::value, true, void, _Fp, _Args...>;

template <class _Fp, class... _Args>
struct __invoke_of
    : public enable_if<__invokable<_Fp, _Args...>::value, typename __invokable_r<void, _Fp, _Args...>::_Result> {};

#endif // _LIBCPP_CXX03_LANG

// result_of

template <class _Callable> class result_of;

#ifndef _LIBCPP_CXX03_LANG

template <class _Fp, class... _Args>
class _LIBCPP_TEMPLATE_VIS result_of<_Fp(_Args...)> : public __invoke_of<_Fp, _Args...> {};

#else // C++03

template <class _Fn, bool, bool> class __result_of {};

template <class _Fn, class... _Args> class __result_of<_Fn(_Args...), true, false> {
public:
  typedef decltype(declval<_Fn>()(declval<_Args>()...)) type;
};

template <class _MP, class _Tp, bool _IsMemberFunctionPtr> struct __result_of_mp;

// member function pointer

template <class _MP, class _Tp>
struct __result_of_mp<_MP, _Tp, true> : public __identity<typename __member_pointer_traits<_MP>::_ReturnType> {};

// member data pointer

template <class _MP, class _Tp, bool> struct __result_of_mdp;

template <class _Rp, class _Class, class _Tp> struct __result_of_mdp<_Rp _Class::*, _Tp, false> {
  typedef typename __apply_cv<decltype(*_VSTD::declval<_Tp>()), _Rp>::type &type;
};

template <class _Rp, class _Class, class _Tp> struct __result_of_mdp<_Rp _Class::*, _Tp, true> {
  typedef typename __apply_cv<_Tp, _Rp>::type &type;
};

template <class _Rp, class _Class, class _Tp>
struct __result_of_mp<_Rp _Class::*, _Tp, false>
    : public __result_of_mdp<_Rp _Class::*, _Tp, is_base_of<_Class, typename remove_reference<_Tp>::type>::value> {};

template <class _Fn, class _Tp>
class __result_of<_Fn(_Tp), false, true> // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
                            is_member_function_pointer<typename remove_reference<_Fn>::type>::value> {};

template <class _Fn, class _Tp, class... _Args>
class __result_of<_Fn(_Tp, _Args...), false, true> // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
                            is_member_function_pointer<typename remove_reference<_Fn>::type>::value> {};

template <class _Fn, class... _Args>
class _LIBCPP_TEMPLATE_VIS result_of<_Fn(_Args...)>
    : public __result_of<_Fn(_Args...),
                         is_class<typename remove_reference<_Fn>::type>::value ||
                             is_function<typename remove_pointer<typename remove_reference<_Fn>::type>::type>::value,
                         is_member_pointer<typename remove_reference<_Fn>::type>::value> {};

#endif // C++03

#if _LIBCPP_STD_VER > 11
template <class _Tp> using result_of_t = typename result_of<_Tp>::type;
#endif

#if _LIBCPP_STD_VER > 14

// invoke_result

template <class _Fn, class... _Args> struct _LIBCPP_TEMPLATE_VIS invoke_result : __invoke_of<_Fn, _Args...> {};

template <class _Fn, class... _Args> using invoke_result_t = typename invoke_result<_Fn, _Args...>::type;

// is_invocable

template <class _Fn, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_invocable : integral_constant<bool, __invokable<_Fn, _Args...>::value> {};

template <class _Ret, class _Fn, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_invocable_r : integral_constant<bool, __invokable_r<_Ret, _Fn, _Args...>::value> {};

template <class _Fn, class... _Args>
_LIBCPP_INLINE_VAR constexpr bool is_invocable_v = is_invocable<_Fn, _Args...>::value;

template <class _Ret, class _Fn, class... _Args>
_LIBCPP_INLINE_VAR constexpr bool is_invocable_r_v = is_invocable_r<_Ret, _Fn, _Args...>::value;

// is_nothrow_invocable

template <class _Fn, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_invocable : integral_constant<bool, __nothrow_invokable<_Fn, _Args...>::value> {
};

template <class _Ret, class _Fn, class... _Args>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_invocable_r
    : integral_constant<bool, __nothrow_invokable_r<_Ret, _Fn, _Args...>::value> {};

template <class _Fn, class... _Args>
_LIBCPP_INLINE_VAR constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<_Fn, _Args...>::value;

template <class _Ret, class _Fn, class... _Args>
_LIBCPP_INLINE_VAR constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<_Ret, _Fn, _Args...>::value;

#endif // _LIBCPP_STD_VER > 14

template <class _Tp> struct __is_swappable;
template <class _Tp> struct __is_nothrow_swappable;

// swap, swap_ranges

template <class _ForwardIterator1, class _ForwardIterator2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 _ForwardIterator2
swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2);

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
#ifndef _LIBCPP_CXX03_LANG
    typename enable_if<is_move_constructible<_Tp>::value && is_move_assignable<_Tp>::value>::type
#else
    void
#endif
        _LIBCPP_CONSTEXPR_AFTER_CXX17
        swap(_Tp &__x, _Tp &__y)
            _NOEXCEPT_(is_nothrow_move_constructible<_Tp>::value &&is_nothrow_move_assignable<_Tp>::value) {
  _Tp __t(_VSTD::move(__x));
  __x = _VSTD::move(__y);
  __y = _VSTD::move(__t);
}

template <class _Tp, size_t _Np>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 typename enable_if<__is_swappable<_Tp>::value>::type
swap(_Tp (&__a)[_Np], _Tp (&__b)[_Np]) _NOEXCEPT_(__is_nothrow_swappable<_Tp>::value) {
  _VSTD::swap_ranges(__a, __a + _Np, __b);
}

template <class _ForwardIterator1, class _ForwardIterator2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 _ForwardIterator2
swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2) {
  for (; __first1 != __last1; ++__first1, (void)++__first2)
    swap(*__first1, *__first2);
  return __first2;
}

// iter_swap

template <class _ForwardIterator1, class _ForwardIterator2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 void iter_swap(_ForwardIterator1 __a,
                                                                              _ForwardIterator2 __b)
    //                                  _NOEXCEPT_(_NOEXCEPT_(swap(*__a, *__b)))
    _NOEXCEPT_(_NOEXCEPT_(swap(*_VSTD::declval<_ForwardIterator1>(), *_VSTD::declval<_ForwardIterator2>()))) {
  swap(*__a, *__b);
}

// __swappable

namespace __detail {
// ALL generic swap overloads MUST already have a declaration available at this point.

template <class _Tp, class _Up = _Tp, bool _NotVoid = !is_void<_Tp>::value && !is_void<_Up>::value>
struct __swappable_with {
  template <class _LHS, class _RHS>
  static decltype(swap(_VSTD::declval<_LHS>(), _VSTD::declval<_RHS>())) __test_swap(int);
  template <class, class> static __nat __test_swap(long);

  // Extra parens are needed for the C++03 definition of decltype.
  typedef decltype((__test_swap<_Tp, _Up>(0))) __swap1;
  typedef decltype((__test_swap<_Up, _Tp>(0))) __swap2;

  static const bool value = _IsNotSame<__swap1, __nat>::value && _IsNotSame<__swap2, __nat>::value;
};

template <class _Tp, class _Up> struct __swappable_with<_Tp, _Up, false> : false_type {};

template <class _Tp, class _Up = _Tp, bool _Swappable = __swappable_with<_Tp, _Up>::value>
struct __nothrow_swappable_with {
  static const bool value =
#ifndef _LIBCPP_HAS_NO_NOEXCEPT
      noexcept(swap(_VSTD::declval<_Tp>(), _VSTD::declval<_Up>())) &&noexcept(
          swap(_VSTD::declval<_Up>(), _VSTD::declval<_Tp>()));
#else
      false;
#endif
};

template <class _Tp, class _Up> struct __nothrow_swappable_with<_Tp, _Up, false> : false_type {};

} // namespace __detail

template <class _Tp>
struct __is_swappable : public integral_constant<bool, __detail::__swappable_with<_Tp &>::value> {};

template <class _Tp>
struct __is_nothrow_swappable : public integral_constant<bool, __detail::__nothrow_swappable_with<_Tp &>::value> {};

#if _LIBCPP_STD_VER > 14

template <class _Tp, class _Up>
struct _LIBCPP_TEMPLATE_VIS is_swappable_with
    : public integral_constant<bool, __detail::__swappable_with<_Tp, _Up>::value> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_swappable
    : public conditional<
          __is_referenceable<_Tp>::value,
          is_swappable_with<typename add_lvalue_reference<_Tp>::type, typename add_lvalue_reference<_Tp>::type>,
          false_type>::type {};

template <class _Tp, class _Up>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_swappable_with
    : public integral_constant<bool, __detail::__nothrow_swappable_with<_Tp, _Up>::value> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_swappable
    : public conditional<
          __is_referenceable<_Tp>::value,
          is_nothrow_swappable_with<typename add_lvalue_reference<_Tp>::type, typename add_lvalue_reference<_Tp>::type>,
          false_type>::type {};

template <class _Tp, class _Up>
_LIBCPP_INLINE_VAR constexpr bool is_swappable_with_v = is_swappable_with<_Tp, _Up>::value;

template <class _Tp> _LIBCPP_INLINE_VAR constexpr bool is_swappable_v = is_swappable<_Tp>::value;

template <class _Tp, class _Up>
_LIBCPP_INLINE_VAR constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<_Tp, _Up>::value;

template <class _Tp> _LIBCPP_INLINE_VAR constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<_Tp>::value;

#endif // _LIBCPP_STD_VER > 14

template <class _Tp, bool = is_enum<_Tp>::value> struct __underlying_type_impl;

template <class _Tp> struct __underlying_type_impl<_Tp, false> {};

template <class _Tp> struct __underlying_type_impl<_Tp, true> { typedef __underlying_type(_Tp) type; };

template <class _Tp> struct underlying_type : __underlying_type_impl<_Tp, is_enum<_Tp>::value> {};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using underlying_type_t = typename underlying_type<_Tp>::type;
#endif

template <class _Tp, bool = is_enum<_Tp>::value> struct __sfinae_underlying_type {
  typedef typename underlying_type<_Tp>::type type;
  typedef decltype(((type)1) + 0) __promoted_type;
};

template <class _Tp> struct __sfinae_underlying_type<_Tp, false> {};

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR int __convert_to_integral(int __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR unsigned __convert_to_integral(unsigned __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR long __convert_to_integral(long __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR unsigned long __convert_to_integral(unsigned long __val) {
  return __val;
}

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR long long __convert_to_integral(long long __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR unsigned long long __convert_to_integral(unsigned long long __val) {
  return __val;
}

template <typename _Fp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR typename enable_if<is_floating_point<_Fp>::value, long long>::type
__convert_to_integral(_Fp __val) {
  return __val;
}

#ifndef _LIBCPP_HAS_NO_INT128
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR __int128_t __convert_to_integral(__int128_t __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR __uint128_t __convert_to_integral(__uint128_t __val) {
  return __val;
}
#endif

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR typename __sfinae_underlying_type<_Tp>::__promoted_type
__convert_to_integral(_Tp __val) {
  return __val;
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp> struct __has_operator_addressof_member_imp {
  template <class _Up>
  static auto __test(int) -> typename __select_2nd<decltype(_VSTD::declval<_Up>().operator&()), true_type>::type;
  template <class> static auto __test(long) -> false_type;

  static const bool value = decltype(__test<_Tp>(0))::value;
};

template <class _Tp> struct __has_operator_addressof_free_imp {
  template <class _Up>
  static auto __test(int) -> typename __select_2nd<decltype(operator&(_VSTD::declval<_Up>())), true_type>::type;
  template <class> static auto __test(long) -> false_type;

  static const bool value = decltype(__test<_Tp>(0))::value;
};

template <class _Tp>
struct __has_operator_addressof : public integral_constant<bool, __has_operator_addressof_member_imp<_Tp>::value ||
                                                                     __has_operator_addressof_free_imp<_Tp>::value> {};

#endif // _LIBCPP_CXX03_LANG

#if _LIBCPP_STD_VER > 14

template <class... _Args> struct conjunction : _And<_Args...> {};
template <class... _Args> _LIBCPP_INLINE_VAR constexpr bool conjunction_v = conjunction<_Args...>::value;

template <class... _Args> struct disjunction : _Or<_Args...> {};
template <class... _Args> _LIBCPP_INLINE_VAR constexpr bool disjunction_v = disjunction<_Args...>::value;

template <class _Tp> struct negation : _Not<_Tp> {};
template <class _Tp> _LIBCPP_INLINE_VAR constexpr bool negation_v = negation<_Tp>::value;
#endif // _LIBCPP_STD_VER > 14

// These traits are used in __tree and __hash_table
struct __extract_key_fail_tag {};
struct __extract_key_self_tag {};
struct __extract_key_first_tag {};

template <class _ValTy, class _Key, class _RawValTy = typename __unconstref<_ValTy>::type>
struct __can_extract_key
    : conditional<_IsSame<_RawValTy, _Key>::value, __extract_key_self_tag, __extract_key_fail_tag>::type {};

template <class _Pair, class _Key, class _First, class _Second>
struct __can_extract_key<_Pair, _Key, pair<_First, _Second>>
    : conditional<_IsSame<typename remove_const<_First>::type, _Key>::value, __extract_key_first_tag,
                  __extract_key_fail_tag>::type {};

// __can_extract_map_key uses true_type/false_type instead of the tags.
// It returns true if _Key != _ContainerValueTy (the container is a map not a set)
// and _ValTy == _Key.
template <class _ValTy, class _Key, class _ContainerValueTy, class _RawValTy = typename __unconstref<_ValTy>::type>
struct __can_extract_map_key : integral_constant<bool, _IsSame<_RawValTy, _Key>::value> {};

// This specialization returns __extract_key_fail_tag for non-map containers
// because _Key == _ContainerValueTy
template <class _ValTy, class _Key, class _RawValTy>
struct __can_extract_map_key<_ValTy, _Key, _Key, _RawValTy> : false_type {};

#ifndef _LIBCPP_HAS_NO_BUILTIN_IS_CONSTANT_EVALUATED
#if _LIBCPP_STD_VER > 17
_LIBCPP_INLINE_VISIBILITY
inline constexpr bool is_constant_evaluated() noexcept { return __builtin_is_constant_evaluated(); }
#endif

inline _LIBCPP_CONSTEXPR bool __libcpp_is_constant_evaluated() _NOEXCEPT { return __builtin_is_constant_evaluated(); }
#else
inline _LIBCPP_CONSTEXPR bool __libcpp_is_constant_evaluated() _NOEXCEPT { return false; }
#endif

template <class _CharT> using _IsCharLikeType = _And<is_standard_layout<_CharT>, is_trivial<_CharT>>;

_LIBCPP_END_NAMESPACE_STD

#if _LIBCPP_STD_VER > 14
// std::byte
namespace std // purposefully not versioned
{}
#endif
