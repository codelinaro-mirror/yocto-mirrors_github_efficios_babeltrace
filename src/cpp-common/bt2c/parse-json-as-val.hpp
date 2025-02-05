/*
 * Copyright (c) 2022-2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_PARSE_JSON_AS_VAL_HPP
#define BABELTRACE_CPP_COMMON_BT2C_PARSE_JSON_AS_VAL_HPP

#include <cstdlib>

#include "logging.hpp"

#include "cpp-common/bt2s/string-view.hpp"

#include "json-val.hpp"

namespace bt2c {

/*!
@brief
    Parses the JSON text \bt_p{str} encoding a single JSON value and
    returns its corresponding JSON value.

@ingroup common-cpp-bt2c-json

This function uses
parseJson(bt2s::string_view, ListenerT&, std::size_t, const Logger&)
behind the scenes, therefore see its documentation to learn more about
JSON parsing specifics.

@note
    You must use this function in libbabeltrace2 context because it
    appends causes to the error of the current thread and throws
    bt2c::Error on error.

@param[in] str
    JSON text to parse, encoding a single JSON value.
@param[in] baseOffset
    Value to add to the offset of any created text location during
    parsing.
@param[in] logger
    Logger to use on error.

@returns
    Decoded JSON value.

@sa parseJson(bt2s::string_view, ListenerT&, std::size_t, const Logger&)
*/
JsonVal::UP parseJson(bt2s::string_view str, std::size_t baseOffset, const Logger& logger);

/*!
@brief
    Overload of
    parseJson(bt2s::string_view, std::size_t, const Logger&)
    with \bt_p{baseOffset} set to&nbsp;0.

@ingroup common-cpp-bt2c-json

@param[in] str
    See parseJson(bt2s::string_view, std::size_t, const Logger&).
@param[in] logger
    See parseJson(bt2s::string_view, std::size_t, const Logger&).

@returns
    See parseJson(bt2s::string_view, std::size_t, const Logger&).

@sa parseJson(bt2s::string_view, ListenerT&, const Logger&)
*/
inline JsonVal::UP parseJson(const bt2s::string_view str, const Logger& logger)
{
    return parseJson(str, 0, logger);
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_PARSE_JSON_AS_VAL_HPP */
