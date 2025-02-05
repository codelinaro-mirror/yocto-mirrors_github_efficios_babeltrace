/*
 * Copyright (c) 2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_STD_INT_HPP
#define BABELTRACE_CPP_COMMON_BT2C_STD_INT_HPP

/*!
@file

@brief
    Standard integer types.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/std-int.hpp"
@endcode

This file offers both the bt2c::Signedness enumerators and
the bt2c::StdIntT alias template.
*/

#include <cstdint>

namespace bt2c {

/*! @brief Integer signedness. */
enum class Signedness
{
    /*! @brief Unsigned. */
    Unsigned,

    /*! @brief Signed. */
    Signed,
};

namespace internal {

template <std::size_t LenBitsV, Signedness SignednessV>
struct StdIntTBase;

template <>
struct StdIntTBase<8, Signedness::Signed>
{
    using Type = std::int8_t;
};

template <>
struct StdIntTBase<8, Signedness::Unsigned>
{
    using Type = std::uint8_t;
};

template <>
struct StdIntTBase<16, Signedness::Signed>
{
    using Type = std::int16_t;
};

template <>
struct StdIntTBase<16, Signedness::Unsigned>
{
    using Type = std::uint16_t;
};

template <>
struct StdIntTBase<32, Signedness::Signed>
{
    using Type = std::int32_t;
};

template <>
struct StdIntTBase<32, Signedness::Unsigned>
{
    using Type = std::uint32_t;
};

template <>
struct StdIntTBase<64, Signedness::Signed>
{
    using Type = std::int64_t;
};

template <>
struct StdIntTBase<64, Signedness::Unsigned>
{
    using Type = std::uint64_t;
};

} /* namespace internal */

/*!
@brief
    Standard fixed-length integer type of length \bt_p{LenBitsV} and
    signedness \bt_p{SignednessV} (Signedness::Unsigned or
    Signedness::Signed).

Equivalence table:

<table>
  <tr>
    <th>With bt2c::StdIntT
    <th>Standard type
  <tr>
    <td><code>bt2c::StdIntT&lt;8, bt2c::Signedness::Unsigned&gt;</code>
    <td>\c std::uint8_t
  <tr>
    <td><code>bt2c::StdIntT&lt;16, bt2c::Signedness::Unsigned&gt;</code>
    <td>\c std::uint16_t
  <tr>
    <td><code>bt2c::StdIntT&lt;32, bt2c::Signedness::Unsigned&gt;</code>
    <td>\c std::uint32_t
  <tr>
    <td><code>bt2c::StdIntT&lt;64, bt2c::Signedness::Unsigned&gt;</code>
    <td>\c std::uint64_t
  <tr>
    <td><code>bt2c::StdIntT&lt;8, bt2c::Signedness::Signed&gt;</code>
    <td>\c std::int8_t
  <tr>
    <td><code>bt2c::StdIntT&lt;16, bt2c::Signedness::Signed&gt;</code>
    <td>\c std::int16_t
  <tr>
    <td><code>bt2c::StdIntT&lt;32, bt2c::Signedness::Signed&gt;</code>
    <td>\c std::int32_t
  <tr>
    <td><code>bt2c::StdIntT&lt;64, bt2c::Signedness::Signed&gt;</code>
    <td>\c std::int64_t
</table>
*/
template <std::size_t LenBitsV, Signedness SignednessV>
using StdIntT = typename internal::StdIntTBase<LenBitsV, SignednessV>::Type;

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_STD_INT_HPP */
