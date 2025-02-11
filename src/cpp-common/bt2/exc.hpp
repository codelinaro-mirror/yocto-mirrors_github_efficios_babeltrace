/*
 * Copyright (c) 2020-2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_EXC_HPP
#define BABELTRACE_CPP_COMMON_BT2_EXC_HPP

#include "cpp-common/bt2c/exc.hpp"

/*!
@file

@brief
    Exception classes.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/exc.hpp"
@endcode
*/

namespace bt2 {

/*!
@brief
    General error.

Corresponds to any libbabeltrace2 status enumerator ending with
<code>_ERROR</code> (except <code>_MEMORY_ERROR</code> and
<code>_OVERFLOW_ERROR</code>).
*/
using Error = bt2c::Error;

/*!
@brief
    Overflow error.

Corresponds to any libbabeltrace2 status enumerator ending with
<code>_OVERFLOW_ERROR</code>.
*/
using OverflowError = bt2c::OverflowError;

/*!
@brief
    Memory error.

Corresponds to any libbabeltrace2 status enumerator ending with
<code>_MEMORY_ERROR</code>.
*/
using MemoryError = bt2c::MemoryError;

/*!
@brief
    Not available right now: try again later.

Corresponds to any libbabeltrace2 status enumerator ending with
<code>_AGAIN</code>.
*/
using TryAgain = bt2c::TryAgain;

/*
 * .
 */

/*!
@brief
    Unknown query object.

Corresponds to any libbabeltrace2 status enumerator ending with
<code>_UNKNOWN_OBJECT</code>.
*/
class UnknownObject : public std::exception
{
public:
    explicit UnknownObject() noexcept = default;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_EXC_HPP */
