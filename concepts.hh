// -*- C++ -*-
//===-------------------------- concepts ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once

#include "__config.hh"
#include "type_traits.hh"

_LIBCPP_BEGIN_NAMESPACE_STD

#if _LIBCPP_STD_VER > 17 && defined(__cpp_concepts) && __cpp_concepts >= 201811L

template <class _Tp, class _Up> concept __same_as_impl = _VSTD::_IsSame<_Tp, _Up>::value;
template <class _Tp, class _Up> concept same_as        = __same_as_impl<_Tp, _Up> &&__same_as_impl<_Up, _Tp>;

#endif

_LIBCPP_END_NAMESPACE_STD
