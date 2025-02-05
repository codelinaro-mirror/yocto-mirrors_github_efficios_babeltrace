/*
 * Copyright (c) 2022 EfficiOS, inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_LIBC_UP_HPP
#define BABELTRACE_CPP_COMMON_BT2C_LIBC_UP_HPP

/*!
@file

@brief
    C standard library unique pointer types.

@ingroup common-cpp-bt2c-up

@code{.cpp}
#include "cpp-common/bt2c/libc-up.hpp"
@endcode
*/

#include <cstdio>
#include <memory>

namespace bt2c {
namespace internal {

struct FileCloserDeleter final
{
    void operator()(std::FILE * const f) noexcept
    {
        std::fclose(f);
    }
};

} /* namespace internal */

/*!
@brief
    Unique pointer to \c FILE (see \bt_ext_man{FILE,3,3type}).

The custom deleter closes the file with \bt_ext_man{fclose,3,3}.
*/
using FileUP = std::unique_ptr<std::FILE, internal::FileCloserDeleter>;

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_LIBC_UP_HPP */
