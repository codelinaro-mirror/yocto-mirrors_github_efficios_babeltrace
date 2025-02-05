/*
 * Copyright (c) 2016-2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_HPP
#define BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_HPP

namespace bt2c {

/*!
@brief
    Text location.

@ingroup common-cpp-bt2c

A text location is a tuple of offset (bytes), line number, and
column number within some text.

Format a text location with textLocStr().

@code{.cpp}
#include "cpp-common/bt2c/text-loc.hpp"
@endcode
*/
class TextLoc final
{
public:
    /*!
    @brief
        Builds a text location which targets offset \bt_p{offset} bytes,
        zero-based line number \bt_p{lineNo}, and zero-based
        column number \bt_p{colNo}.

    @param[in] offset
        Offset (bytes).
    @param[in] lineNo
        Zero-based line number (bytes).
    @param[in] colNo
        Zero-based column number (bytes).
    */
    explicit TextLoc(unsigned long long offset = 0, unsigned long long lineNo = 0,
                     unsigned long long colNo = 0) noexcept;

    /*!
    @brief
        Offset (bytes).

    @returns
        Offset (bytes).
    */
    unsigned long long offset() const noexcept
    {
        return _mOffset;
    }

    /*!
    @brief
        Zero-based line number.

    @returns
        Zero-based line number.
    */
    unsigned long long lineNo() const noexcept
    {
        return _mLineNo;
    }

    /*!
    @brief
        Zero-based column number.

    @returns
        Zero-based column number.
    */
    unsigned long long colNo() const noexcept
    {
        return _mColNo;
    }

    /*!
    @brief
        One-based line number.

    @returns
        One-based line number.
    */
    unsigned long long naturalLineNo() const noexcept
    {
        return _mLineNo + 1;
    }

    /*!
    @brief
        One-based column number.

    @returns
        One-based column number.
    */
    unsigned long long naturalColNo() const noexcept
    {
        return _mColNo + 1;
    }

private:
    unsigned long long _mOffset = 0;
    unsigned long long _mLineNo = 0;
    unsigned long long _mColNo = 0;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_TEXT_LOC_HPP */
