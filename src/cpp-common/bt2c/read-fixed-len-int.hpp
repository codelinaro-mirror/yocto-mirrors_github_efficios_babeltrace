/*
 * Copyright (c) 2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_READ_FIXED_LEN_INT_HPP
#define BABELTRACE_CPP_COMMON_BT2C_READ_FIXED_LEN_INT_HPP

/*!
@file

@brief
    Fixed-length integer reading function templates.

@ingroup common-cpp-bt2c

The function templates of this file read a fixed-length integer of
any standard size, signedness, and byte order from a byte buffer. They
use \c std::memcpy() with the size of their template parameter.

Those functions are optimal with compiler optimization. For example,
with GCC 14.2 with the <code>-O2</code> level on a little-endian
system,

@code{.cpp}
bt2c::readFixedLenIntBe<unsigned int>(someBuf);
@endcode

becomes

@code{.undefined}
movl    (%rdi), %eax
bswap   %eax
@endcode

@code{.cpp}
#include "cpp-common/bt2c/read-fixed-len-int.hpp"
@endcode
*/

#include <cstdint>
#include <cstring>
#include <type_traits>

#include "endian.hpp"

namespace bt2c {

/*!
@brief
    Reads a fixed-length integer of unknown byte order into a value of
    integral type \bt_p{IntT} from the buffer \bt_p{buf} and returns it.

@param[in] buf
    Buffer from which to read.

@returns
    Decoded integer.

@pre
    \bt_p{buf} has at least <code>sizeof(IntT)</code> bytes available.
*/
template <typename IntT>
IntT readFixedLenInt(const std::uint8_t * const buf)
{
    static_assert(std::is_integral_v<IntT>, "`IntT` is an integral type.");

    IntT val;

    std::memcpy(&val, buf, sizeof(val));
    return val;
}

/*!
@brief
    Reads a fixed-length little-endian integer into a value of
    integral type \bt_p{IntT} from the buffer \bt_p{buf} and returns it.

@param[in] buf
    Buffer from which to read.

@returns
    Decoded integer.

@pre
    \bt_p{buf} has at least <code>sizeof(IntT)</code> bytes available.
*/
template <typename IntT>
IntT readFixedLenIntLe(const std::uint8_t * const buf)
{
    return littleEndianToNative(readFixedLenInt<IntT>(buf));
}

/*!
@brief
    Reads a fixed-length big-endian integer into a value of
    integral type \bt_p{IntT} from the buffer \bt_p{buf} and returns it.

@param[in] buf
    Buffer from which to read.

@returns
    Decoded integer.

@pre
    \bt_p{buf} has at least <code>sizeof(IntT)</code> bytes available.
*/
template <typename IntT>
IntT readFixedLenIntBe(const std::uint8_t * const buf)
{
    return bigEndianToNative(readFixedLenInt<IntT>(buf));
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_READ_FIXED_LEN_INT_HPP */
