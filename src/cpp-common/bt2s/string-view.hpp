/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2S_STRING_VIEW_HPP
#define BABELTRACE_CPP_COMMON_BT2S_STRING_VIEW_HPP

/* Force `nonstd::string_view` during the transition to C++17 */
#define nssv_CONFIG_SELECT_STRING_VIEW 1

#include "cpp-common/vendor/string-view-lite/string_view.hpp"

namespace bt2s {

using nonstd::basic_string_view;
using nonstd::string_view;
using nonstd::wstring_view;
using nonstd::u16string_view;
using nonstd::u32string_view;

} /* namespace bt2s */

#endif /* BABELTRACE_CPP_COMMON_BT2S_STRING_VIEW_HPP */
