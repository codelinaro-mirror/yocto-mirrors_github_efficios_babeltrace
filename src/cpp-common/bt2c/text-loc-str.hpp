/*
 * Copyright (c) 2016-2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_STR_HPP
#define BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_STR_HPP

#include <string>

#include "text-loc.hpp"

namespace bt2c {

/*!
@brief
    Text location string format.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/text-loc-str.hpp"
@endcode

To be used with textLocStr().
*/
enum class TextLocStrFmt
{
    /*! Show offset only. */
    Offset,

    /*! Show line/column numbers and offset. */
    LineColNosAndOffset,

    /*! Show line/column numbers only. */
    LineColNos,
};

/*!
@brief
    Returns the string of the text location \bt_p{loc}, honouring the
    format \bt_p{fmt}.

@ingroup common-cpp-bt2c

@code{.c}
#include "cpp-common/bt2c/text-loc-str.hpp"
@endcode

@param[in] loc
    Text location to format.
@param[in] fmt
    Format to use.

@returns
    String of \bt_p{loc}.
*/
std::string textLocStr(const TextLoc& loc, TextLocStrFmt fmt);

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_STR_HPP */
