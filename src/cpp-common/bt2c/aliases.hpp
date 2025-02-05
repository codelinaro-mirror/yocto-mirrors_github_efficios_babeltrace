/*
 * Copyright (c) 2024 EfficiOS, Inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_ALIASES_HPP
#define BABELTRACE_CPP_COMMON_BT2C_ALIASES_HPP

#include <cstdint>

#include "cpp-common/bt2s/span.hpp"

namespace bt2c {

/*!
@brief
    A span of constant bytes.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/aliases.hpp"
@endcode
*/
using ConstBytes = bt2s::span<const std::uint8_t>;

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_ALIASES_HPP */
