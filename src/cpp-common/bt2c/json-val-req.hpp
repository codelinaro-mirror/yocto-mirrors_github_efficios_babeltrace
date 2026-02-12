/*
 * Copyright (c) 2022 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_REQ_HPP
#define BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_REQ_HPP

/*!
@file

@brief
    JSON value requirement classes.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/json-val-req.hpp"
@endcode

This file offers type aliases of template instantiations of
cpp-common/bt2c/val-req.hpp classes for bt2c::JsonVal objects.
*/

#include <memory>
#include <string>
#include <unordered_map>

#include "common/common.h"

#include "json-val.hpp"
#include "val-req.hpp"

namespace bt2c {
namespace internal {

struct JsonValOps final
{
    static ValType valType(const JsonVal& jsonVal) noexcept
    {
        switch (jsonVal.type()) {
        case JsonVal::Type::Null:
            return ValType::Null;
        case JsonVal::Type::Bool:
            return ValType::Bool;
        case JsonVal::Type::SInt:
            return ValType::SInt;
        case JsonVal::Type::UInt:
            return ValType::UInt;
        case JsonVal::Type::Real:
            return ValType::Real;
        case JsonVal::Type::Str:
            return ValType::Str;
        case JsonVal::Type::Array:
            return ValType::Array;
        case JsonVal::Type::Obj:
            return ValType::Obj;
        default:
            bt_common_abort();
        }
    }

    static const char *typeDetStr(const ValType type) noexcept
    {
        switch (type) {
        case ValType::Null:
            return "";
        case ValType::Bool:
        case ValType::SInt:
        case ValType::Real:
        case ValType::Str:
            return "a";
        case ValType::UInt:
        case ValType::Array:
        case ValType::Obj:
            return "an";
        default:
            bt_common_abort();
        }
    }

    static const char *typeStr(const ValType type) noexcept
    {
        switch (type) {
        case ValType::Null:
            return "`null`";
        case ValType::Bool:
            return "boolean";
        case ValType::SInt:
            return "signed integer";
        case ValType::UInt:
            return "unsigned integer";
        case ValType::Real:
            return "real";
        case ValType::Str:
            return "string";
        case ValType::Array:
            return "array";
        case ValType::Obj:
            return "object";
        default:
            bt_common_abort();
        }
    }

    static constexpr auto objValPropName = "property";

    static const TextLoc& valLoc(const JsonVal& jsonVal) noexcept
    {
        return jsonVal.loc();
    }

    static const JsonUIntVal& asUInt(const JsonVal& jsonVal) noexcept
    {
        return jsonVal.asUInt();
    }

    static const JsonStrVal& asStr(const JsonVal& jsonVal) noexcept
    {
        return jsonVal.asStr();
    }

    static const JsonArrayVal& asArray(const JsonVal& jsonVal) noexcept
    {
        return jsonVal.asArray();
    }

    static const JsonObjVal& asObj(const JsonVal& jsonVal) noexcept
    {
        return jsonVal.asObj();
    }

    template <typename JsonScalarValT>
    using ScalarValRawValT = typename JsonScalarValT::Val;

    template <typename JsonScalarValT>
    static typename JsonScalarValT::Val scalarValRawVal(const JsonScalarValT& jsonVal) noexcept
    {
        return *jsonVal;
    }

    static const std::string& scalarValRawVal(const JsonStrVal& jsonVal) noexcept
    {
        return *jsonVal;
    }

    static std::size_t arrayValSize(const JsonArrayVal& jsonVal) noexcept
    {
        return jsonVal.size();
    }

    static const JsonVal& arrayValElem(const JsonArrayVal& jsonVal,
                                       const std::size_t index) noexcept
    {
        return jsonVal[index];
    }

    static const JsonVal *objValVal(const JsonObjVal& jsonVal, const std::string& key) noexcept
    {
        return jsonVal[key];
    }

    static JsonObjVal::Container::const_iterator objValBegin(const JsonObjVal& jsonVal) noexcept
    {
        return jsonVal.begin();
    }

    static JsonObjVal::Container::const_iterator objValEnd(const JsonObjVal& jsonVal) noexcept
    {
        return jsonVal.end();
    }

    static const std::string& objValItKey(const JsonObjVal::Container::const_iterator& it) noexcept
    {
        return it->first;
    }

    static const JsonVal& objValItVal(const JsonObjVal::Container::const_iterator& it) noexcept
    {
        return *it->second;
    }
};

} /* namespace internal */

/*! @brief JSON value requirement. */
using JsonValReq = ValReq<JsonVal, internal::JsonValOps>;

/*! @brief "JSON value has type" requirement. */
using JsonValHasTypeReq = ValHasTypeReq<JsonVal, internal::JsonValOps>;

/*! @brief Any JSON integer value requirement. */
using JsonAnyIntValReq = AnyIntValReq<JsonVal, internal::JsonValOps>;

/*! @brief JSON unsigned integer value requirement. */
using JsonUIntValReq = UIntValReq<JsonVal, internal::JsonValOps>;

/*! @brief JSON signed integer range value requirement. */
using JsonSIntValReq = SIntValReq<JsonVal, internal::JsonValOps>;

/*! @brief "JSON unsigned integer value in range" requirement. */
using JsonUIntValInRangeReq =
    IntValInRangeReq<JsonVal, internal::JsonValOps, JsonUIntVal, ValType::UInt>;

/*! @brief "JSON signed integer value in range" requirement. */
using JsonSIntValInRangeReq =
    IntValInRangeReq<JsonVal, internal::JsonValOps, JsonSIntVal, ValType::SInt>;

/*! @brief "JSON boolean value in set" requirement. */
using JsonBoolValInSetReq =
    ScalarValInSetReq<JsonVal, internal::JsonValOps, JsonBoolVal, ValType::Bool>;

/*! @brief "JSON unsigned integer value in set" requirement. */
using JsonUIntValInSetReq =
    ScalarValInSetReq<JsonVal, internal::JsonValOps, JsonUIntVal, ValType::UInt>;

/*! @brief "JSON signed integer value in set" requirement. */
using JsonSIntValInSetReq =
    ScalarValInSetReq<JsonVal, internal::JsonValOps, JsonSIntVal, ValType::SInt>;

/*! @brief "JSON string value in set" requirement. */
using JsonStrValInSetReq =
    ScalarValInSetReq<JsonVal, internal::JsonValOps, JsonStrVal, ValType::Str>;

/*! @brief JSON array value requirement. */
using JsonArrayValReq = ArrayValReq<JsonVal, internal::JsonValOps>;

/*! @brief JSON object value property requirement. */
using JsonObjValPropReq = ObjValPropReq<JsonVal, internal::JsonValOps>;

/*! @brief JSON object value requirement. */
using JsonObjValReq = ObjValReq<JsonVal, internal::JsonValOps>;

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_REQ_HPP */
