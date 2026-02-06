/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_TYPE_TRAITS_HPP
#define BABELTRACE_CPP_COMMON_BT2C_TYPE_TRAITS_HPP

/*!
@file

@brief
    General purpose C++ type traits.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/type-traits.hpp"
@endcode
*/

#include <type_traits>

namespace bt2c {

/*!
@brief
    Provides the member constant \c value equal to:

<dl>
  <dt>\bt_p{T} is in the list of types \bt_p{Ts}
  <dd>\c true

  <dt>Otherwise
  <dd>\c false
</dl>
*/
template <typename T, typename... Ts>
struct IsOneOf : std::false_type
{
};

template <typename T, typename... Ts>
struct IsOneOf<T, T, Ts...> : std::true_type
{
};

template <typename T, typename U, typename... Ts>
struct IsOneOf<T, U, Ts...> : IsOneOf<T, Ts...>
{
};

/// Alias for the value of IsOneOf.
template <typename T, typename... Ts>
inline constexpr bool IsOneOfV = IsOneOf<T, Ts...>::value;

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_TYPE_TRAITS_HPP */
