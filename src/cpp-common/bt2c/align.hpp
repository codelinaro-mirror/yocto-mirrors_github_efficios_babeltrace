/*
 * Copyright (c) 2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_ALIGN_HPP
#define BABELTRACE_CPP_COMMON_BT2C_ALIGN_HPP

#include <type_traits>

#include "common/align.h"

namespace bt2c {

/*!
@brief
    Returns the \em next multiple of \bt_p{align} from \bt_p{val},
    (an integer variable), or \bt_p{val} if it's already a multiple
    of \bt_p{align}.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/align.hpp"
@endcode

@param[in] val
    Value to align.
@param[in] align
    Alignment.

@returns
    Aligned value.

@pre
    - \bt_p{align} is greater than 0.
    - \bt_p{align} is a power of two.
*/
template <typename ValT, typename AlignT>
ValT align(const ValT val, const AlignT align) noexcept
{
    static_assert(std::is_unsigned_v<ValT>, "`ValT` is unsigned.");
    return BT_ALIGN(val, static_cast<ValT>(align));
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_ALIGN_HPP */
