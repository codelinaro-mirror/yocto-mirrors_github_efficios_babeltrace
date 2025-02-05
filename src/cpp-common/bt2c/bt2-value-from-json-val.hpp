/*
 * Copyright (c) 2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_BT2_VALUE_FROM_JSON_VAL_HPP
#define BABELTRACE_CPP_COMMON_BT2C_BT2_VALUE_FROM_JSON_VAL_HPP

#include "cpp-common/bt2/value.hpp"

#include "json-val.hpp"

namespace bt2c {

/*!
@brief
    Converts \bt_p{jsonVal} to an equivalent libbabeltrace2 value
    object and returns it.

@ingroup common-cpp-bt2c-json

The conversion is as such:

<table>
  <tr>
    <th>JSON value
    <th>Resulting libbabeltrace2 value
  <tr>
    <td>JsonNullVal
    <td>bt2::NullValue
  <tr>
    <td>JsonBoolVal
    <td>bt2::BoolValue
  <tr>
    <td>JsonSIntVal
    <td>bt2::SignedIntegerValue
  <tr>
    <td>JsonUIntVal
    <td>bt2::UnsignedIntegerValue
  <tr>
    <td>JsonRealVal
    <td>bt2::RealValue
  <tr>
    <td>JsonStrVal
    <td>bt2::StringValue
  <tr>
    <td>JsonArrayVal
    <td>bt2::ArrayValue
  <tr>
    <td>JsonObjVal
    <td>bt2::MapValue
</table>

@code{.c}
#include "cpp-common/bt2c/bt2-value-from-json-val.hpp"
@endcode

@param[in] jsonVal
    JSON value to convert.

@returns
    \bt_p{jsonVal} as a libbabeltrace2 value object.
*/
bt2::Value::Shared bt2ValueFromJsonVal(const JsonVal& jsonVal);

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_BT2_VALUE_FROM_JSON_VAL_HPP */
