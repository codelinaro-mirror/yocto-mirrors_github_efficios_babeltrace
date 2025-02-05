/*
 * Copyright (c) 2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_CONTAINS_HPP
#define BABELTRACE_CPP_COMMON_BT2C_CONTAINS_HPP

namespace bt2c {

/*!
@brief
    Returns whether or not the STL container \bt_p{container} contains
    a copy of \bt_p{val}.

@ingroup common-cpp-bt2c

This function uses \bt_p{container.find()} and \bt_p{container.end()}.

@code{.cpp}
#include "cpp-common/bt2c/contains.hpp"
@endcode

@param[in] container
    STL container of which to know whether or not it contains
    a copy of \bt_p{val}.
@param[in] val
    Value to check.

@retval false
    \bt_p{container} doesn't contain a copy of \bt_p{val}.
@retval true
    \bt_p{container} contains a copy of \bt_p{val}.
*/
template <typename T, typename V>
bool contains(const T& container, const V& val) noexcept
{
    return container.find(val) != container.end();
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_CONTAINS_HPP */
