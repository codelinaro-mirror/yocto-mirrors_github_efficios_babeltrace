/*
 * Copyright (c) 2024 EfficiOS, Inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_UNICODE_CONV_HPP
#define BABELTRACE_CPP_COMMON_BT2C_UNICODE_CONV_HPP

#include <cstddef>
#include <vector>

#include <glib.h>

#include "logging.hpp"

#include "aliases.hpp"

namespace bt2c {

/*!
@brief
    Unicode string converter.

@ingroup common-cpp-bt2c

A Unicode string converter offers the <code>utf8FromUtf*()</code>
methods to convert UTF-16 and UTF-32 data to UTF-8.

@warning
    The conversion methods aren't thread-safe: a UnicodeConv instance
    keeps an internal buffer where it writes the resulting UTF-8 data.

The available methods to convert to UTF-8 are:

<table>
  <tr>
    <th>Code unit length (bits)
    <th>Byte order
    <th>Conversion method
  <tr>
    <td>16
    <td>Big-endian
    <td>utf8FromUtf16Be()
  <tr>
    <td>16
    <td>Little-endian
    <td>utf8FromUtf16Le()
  <tr>
    <td>32
    <td>Big-endian
    <td>utf8FromUtf32Be()
  <tr>
    <td>32
    <td>Little-endian
    <td>utf8FromUtf32Le()
</table>

@note
    You must use this class in libbabeltrace2 context because it
    appends causes to the error of the current thread and throws
    bt2c::Error on error.

@code{.cpp}
#include "cpp-common/bt2c/unicode-conv.hpp"
@endcode
*/
class UnicodeConv final
{
public:
    /*!
    @brief
        Builds a Unicode string converter using the parent logger
        \bt_p{parentLogger}.

    @param[in] parentLogger
        Parent logger to use on error.
    */
    explicit UnicodeConv(const bt2c::Logger& parentLogger);

    ~UnicodeConv();

    /*!
    @brief
        Converts the UTF-16BE data \bt_p{data} to UTF-8 and returns it.

    Logs a message, appends a cause to the error of the current
    thread, and throws bt2c::Error if any conversion error occurs,
    including incomplete data in \bt_p{data}.

    @param[in] data
        UTF-16BE data to convert.

    @returns
        @parblock
        UTF-8 version of \bt_p{data}.

        The returned data belongs to this Unicode string converter
        and remains valid as long as you don't call another method
        of this.
        @endparblock

    @pre
        \bt_p{data.data()} doesn't return \c nullptr.
    */
    ConstBytes utf8FromUtf16Be(ConstBytes data);

    /*!
    @brief
        Converts the UTF-16LE data \bt_p{data} to UTF-8 and returns it.

    Logs a message, appends a cause to the error of the current
    thread, and throws bt2c::Error if any conversion error occurs,
    including incomplete data in \bt_p{data}.

    @param[in] data
        UTF-16LE data to convert.

    @returns
        @parblock
        UTF-8 version of \bt_p{data}.

        The returned data belongs to this Unicode string converter
        and remains valid as long as you don't call another method
        of this.
        @endparblock

    @pre
        \bt_p{data.data()} doesn't return \c nullptr.
    */
    ConstBytes utf8FromUtf16Le(ConstBytes data);

    /*!
    @brief
        Converts the UTF-32BE data \bt_p{data} to UTF-8 and returns it.

    Logs a message, appends a cause to the error of the current
    thread, and throws bt2c::Error if any conversion error occurs,
    including incomplete data in \bt_p{data}.

    @param[in] data
        UTF-32BE data to convert.

    @returns
        @parblock
        UTF-8 version of \bt_p{data}.

        The returned data belongs to this Unicode string converter
        and remains valid as long as you don't call another method
        of this.
        @endparblock

    @pre
        \bt_p{data.data()} doesn't return \c nullptr.
    */
    ConstBytes utf8FromUtf32Be(ConstBytes data);

    /*!
    @brief
        Converts the UTF-32LE data \bt_p{data} to UTF-8 and returns it.

    Logs a message, appends a cause to the error of the current
    thread, and throws bt2c::Error if any conversion error occurs,
    including incomplete data in \bt_p{data}.

    @param[in] data
        UTF-32LE data to convert.

    @returns
        @parblock
        UTF-8 version of \bt_p{data}.

        The returned data belongs to this Unicode string converter
        and remains valid as long as you don't call another method
        of this.
        @endparblock

    @pre
        \bt_p{data.data()} doesn't return \c nullptr.
    */
    ConstBytes utf8FromUtf32Le(ConstBytes data);

private:
    ConstBytes _justDoIt(const char *sourceEncoding, GIConv& converter, const ConstBytes data,
                         std::size_t codeUnitSize);

    bt2c::Logger _mLogger;
    GIConv _mUtf16BeToUtf8IConv;
    GIConv _mUtf16LeToUtf8IConv;
    GIConv _mUtf32BeToUtf8IConv;
    GIConv _mUtf32LeToUtf8IConv;
    std::vector<std::uint8_t> _mBuf;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_UNICODE_CONV_HPP */
