/*
 * Copyright (c) 2024 EfficiOS, Inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_MIP_HPP
#define BABELTRACE_CPP_COMMON_BT2_MIP_HPP

#include <cstdint>

#include <babeltrace2/babeltrace.h>

namespace bt2 {

inline std::uint64_t getMaximalMipVersion() noexcept
{
    return bt_get_maximal_mip_version();
}

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_MIP_HPP */
