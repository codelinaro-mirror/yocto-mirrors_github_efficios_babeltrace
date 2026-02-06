/*
 * Copyright (c) 2020 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_TYPE_TRAITS_HPP
#define BABELTRACE_CPP_COMMON_BT2_TYPE_TRAITS_HPP

#include "internal/utils.hpp"

/*!
@file

@brief
    Type traits.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/type-traits.hpp"
@endcode

This header offers bt2::AddConst, bt2::AddConstT, bt2::RemoveConst,
and bt2::RemoveConstT.
*/

namespace bt2 {

/*!
@brief
    Offers #Type which is the constant version of the wrapper
    type \bt_p{ObjT}.

@tparam ObjT
    Wrapper of which to get the constant version.
*/
template <typename ObjT>
struct AddConst
{
    /// Constant version of \bt_p{ObjT}.
    using Type = typename internal::TypeDescr<ObjT>::Const;
};

/// Alias for the type of AddConst.
template <typename ObjT>
using AddConstT = typename AddConst<ObjT>::Type;

/*!
@brief
    Offers #Type which is the non-constant version of the wrapper
    type \bt_p{ObjT}.

@tparam ObjT
    Wrapper of which to get the non-constant version.
*/
template <typename ObjT>
struct RemoveConst
{
    /// Non-constant version of \bt_p{ObjT}.
    using Type = typename internal::TypeDescr<ObjT>::NonConst;
};

/// Alias for the type of RemoveConstT.
template <typename ObjT>
using RemoveConstT = typename RemoveConst<ObjT>::Type;

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_TYPE_TRAITS_HPP */
