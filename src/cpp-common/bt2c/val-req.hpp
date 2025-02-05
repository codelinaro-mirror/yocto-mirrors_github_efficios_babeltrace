/*
 * Copyright (c) 2022-2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_VAL_REQ_HPP
#define BABELTRACE_CPP_COMMON_BT2C_VAL_REQ_HPP

/*!
@file

@brief
    Value requirement classes.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/val-req.hpp"
@endcode

The classes of this file are the foundation of any \bt_name value
requirement system.

Currently, the component parameter validation and
\link cpp-common/bt2c/json-val-req.hpp JSON value requirement\endlink
systems use it.

A value requirement is a schema validator for a JSON-like object,
that is, a null, boolean, unsigned/signed integer, real, string,
array, or object/map value.

All the class templates accept a \bt_p{ValT} template parameter which
is the base type of the objects to validate, as well as \bt_p{ValOpsT},
a structure which defines specific value operations.

@note
    You must use those classes in libbabeltrace2 context because the
    bt2c::ValReq::validate() method
    appends causes to the error of the current thread and throws
    bt2c::Error on error.

@section common-cpp-bt2c-val-req-ops \bt_p{ValOpsT} operations requirements

The requirements of a \bt_p{ValOpsT} structure are:

- @code{.cpp}
  static ValType valType(const ValT& val);
  @endcode

  Returns the type of \bt_p{val} as a bt2c::ValType value.

- @code{.cpp}
  static const char *typeDetStr(ValType type);
  @endcode

  Returns the determiner (lowercase) to use for the value type
  \bt_p{type}.

  For example, in "an object", the determiner is "an".

  This is required to generate an error message.

- @code{.cpp}
  static const char *typeStr(ValType type);
  @endcode

  Returns the name (lowercase) of the value type \bt_p{type}.

  This is required to generate an error message.

- @code{.cpp}
  static constexpr const char *objValPropName:
  @endcode

  Name (lowercase) of an object value object property.

- @code{.cpp}
  static const TextLoc& valLoc(const ValT& val);
  @endcode

  Returns the location of the value \bt_p{val}.

  This is required to generate an error message.

- @code{.cpp}
  static const MeowUInt& asUInt(const ValT& val);
  @endcode

  Returns \bt_p{val} as an unsigned integer value object.

- @code{.cpp}
  static const MeowStr& asStr(const ValT& val);
  @endcode

  Returns \bt_p{val} as a string value object.

- @code{.cpp}
  static const MeowArray& asArray(const ValT& val);
  @endcode

  Returns \bt_p{val} as an array value object.

- @code{.cpp}
  static const MeowObj& asObj(const ValT& val);
  @endcode

  Returns \bt_p{val} as an object value object.

- @code{.cpp}
  template <typename ScalarValT> using ScalarValRawValT = ...;
  @endcode

  Raw value type of the scalar value object type \bt_p{ScalarValT}.

- @code{.cpp}
  static unsigned long long scalarValRawVal(const MeowUInt& val);
  @endcode

  Returns the raw value of the unsigned value object \bt_p{val}.

- @code{.cpp}
  static long long scalarValRawVal(const MeowSInt& val);
  @endcode

  Returns the raw value of the signed value object \bt_p{val}.

- @code{.cpp}
  static double scalarValRawVal(const MeowReal& val);
  @endcode

  Returns the raw value of the real value object \bt_p{val}.

- @code{.cpp}
  static const std::string& scalarValRawVal(const MeowStr& val);
  @endcode

  Returns the raw value of the string value object \bt_p{val}.

- @code{.cpp}
  static std::size_t arrayValSize(const MeowArray& val);
  @endcode

  Returns the size of the array value object \bt_p{val}.

- @code{.cpp}
  static const ValT& arrayValElem(const MeowArray& val, std::size_t index);
  @endcode

  Returns the element of the array value object \bt_p{val} at the index
  \bt_p{index}.

- @code{.cpp}
  static const ValT *objValVal(const MeowObj& val, const std::string& key);
  @endcode

  Returns the value of the object value object \bt_p{val} having the key
  \bt_p{key}, or \c nullptr if there's none.

- @code{.cpp}
  static MeowObjIterator objValBegin(const MeowObj& val);
  @endcode

  Returns an iterator at the first element of the object value object
  \bt_p{val}.

- @code{.cpp}
  static MeowObjIterator objValEnd(const MeowObj& val);
  @endcode

  Returns an iterator \em after the last element of the object value
  object \bt_p{val}.

- @code{.cpp}
  static const std::string& objValItKey(const MeowObjIterator& it);
  @endcode

  Returns the key of the object value object iterator \bt_p{it}.

- @code{.cpp}
  static const ValT& objValItVal(const MeowObjIterator& it);
  @endcode

  Returns the value object of the object value object iterator
  \bt_p{it}.

@section common-cpp-bt2c-val-req-aliases Type aliases

You'll want to create your own type aliases as such to have your
specific value requirement system:

@code{.cpp}
using MeowReq = bt2c::ValReq<Meow, internal::MeowOps>;
using MeowHasTypeReq = bt2c::ValHasTypeReq<Meow, internal::MeowOps>;
using MeowAnyIntReq = bt2c::AnyIntValReq<Meow, internal::MeowOps>;
using MeowUIntReq = bt2c::UIntValReq<Meow, internal::MeowOps>;
using MeowSIntReq = bt2c::SIntValReq<Meow, internal::MeowOps>;

using MeowUIntInRangeReq =
    bt2c::IntValInRangeReq<Meow, internal::MeowOps,
                           MeowUInt, bt2c::ValType::UInt>;

using MeowSIntInRangeReq =
    bt2c::IntValInRangeReq<Meow, internal::MeowOps,
                           MeowSInt, bt2c::ValType::SInt>;

using MeowBoolInSetReq =
    bt2c::ScalarValInSetReq<Meow, internal::MeowOps,
                            MeowBool, bt2c::ValType::Bool>;

using MeowUIntInSetReq =
    bt2c::ScalarValInSetReq<Meow, internal::MeowOps,
                            MeowUInt, bt2c::ValType::UInt>;

using MeowSIntInSetReq =
    bt2c::ScalarValInSetReq<Meow, internal::MeowOps,
                            MeowSInt, bt2c::ValType::SInt>;

using MeowStrInSetReq =
    bt2c::ScalarValInSetReq<Meow, internal::MeowOps,
                            MeowStr, bt2c::ValType::Str>;

using MeowArrayReq = bt2c::ArrayValReq<Meow, internal::MeowOps>;
using MeowObjPropReq = bt2c::ObjValPropReq<Meow, internal::MeowOps>;
using MeowObjReq = bt2c::ObjValReq<Meow, internal::MeowOps>;
@endcode

@section common-cpp-bt2c-val-req-usage Basic usage

You can build a tree of value requirements using your specific value
requirement aliases:

@code{.cpp}
MeowObjReq introReq {{
    {"system", {MeowStrInSetReq::shared({"linux", "windows"}, logger), true}},
    {"version", MeowObjReq::shared({{
        {"major", {MeowUIntInRangeReq::shared(2, bt2s::nullopt, logger), true}},
        {"minor", {MeowHasTypeReq::shared(bt2c::ValType::UInt, logger), true}},
        {"patch", {MeowHasTypeReq::shared(bt2c::ValType::UInt, logger)}},
    }})},
    {"uuid", {MeowArrayReq::shared(bt2c::Uuid::size(),
                                   MeowUIntInRangeReq::shared(0, 255, logger),
                                   logger)}},
}};
@endcode

Then, use it to validate a value of your own type:

@code{.cpp}
void validateIntro(const Meow& meow)
{
    introReq.validate(meow);
}
@endcode

On validation error, the \c validate() method appends causes to the
error of the current thread, logs, and throws bt2c::Error.

@section common-cpp-bt2c-val-req-ext Extend

You may create a class which inherits any of your specific value
requirement classes. Implement

@code{.cpp}
virtual void _validate(const ValT&) const;
@endcode

to add more validation, possibly calling the parent \c validate() to
benefit from its validation.

Example:

@code{.cpp}
class MeowUuidReq final : public MeowArrayReq
{
public:
    explicit MeowUuidReq(const bt2c::Logger& parentLogger) :
        MeowArrayReq {
            bt2c::Uuid::size(),
            MeowUIntInRangeReq::shared(0, 255, parentLogger),
            parentLogger
        }
    {
    }

    static SP shared(const bt2c::Logger& parentLogger)
    {
        return std::make_shared<MeowUuidReq>(parentLogger);
    }

private:
    void _validate(const Meow& meow) const override
    {
        try {
            MeowArrayReq::_validate(meow);
        } catch (const bt2c::Error&) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_RETHROW_SPEC(this->_logger(), meow.loc(),
                                                              "Invalid UUID.");
        }
    }
};

class MeowVersionReq final : public MeowObjReq
{
public:
    explicit MeowVersionReq(const bt2c::Logger& parentLogger) :
        MeowObjReq {{
            {"major", {MeowUIntInRangeReq::shared(2, bt2s::nullopt, parentLogger), true}},
            {"minor", {MeowHasTypeReq::shared(bt2c::ValType::UInt, parentLogger), true}},
            {"patch", {MeowHasTypeReq::shared(bt2c::ValType::UInt, parentLogger)}},
        }}
    {
    }

    static SP shared(const bt2c::Logger& parentLogger)
    {
        return std::make_shared<MeowVersionReq>(parentLogger);
    }

private:
    void _validate(const Meow& meow) const override
    {
        try {
            MeowObjReq::_validate(meow);
        } catch (const bt2c::Error&) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_RETHROW_SPEC(this->_logger(), meow.loc(),
                                                              "Invalid version.");
        }
    }
};
@endcode

Then you may rewrite the example above as such:

@code{.cpp}
MeowObjReq introReq {{
    {"system", {MeowStrInSetReq::shared({"linux", "windows"}, logger), true}},
    {"version", MeowVersionReq::shared(logger)},
    {"uuid", MeowUuidReq::shared(logger)},
}};
@endcode
*/

#include <limits>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

#include "logging.hpp"

#include "exc.hpp"
#include "text-loc.hpp"

namespace bt2c {

/*!
@brief
    Value requirement abstract base class template.

validate() calls _validate().
*/
template <typename ValT, typename ValOpsT>
class ValReq
{
public:
    /*! @brief Shared pointer to constant value requirement. */
    using SP = std::shared_ptr<const ValReq>;

protected:
    /*!
    @brief
        Builds a value requirement, creating its own logger from
        \bt_p{parentLogger}.

    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ValReq(const Logger& parentLogger) noexcept : _mLogger {parentLogger, "VAL-REQ"}
    {
    }

public:
    /* Deleted copy/move operations to simplify */
    ValReq(const ValReq&) = delete;
    ValReq(ValReq&&) = delete;
    ValReq& operator=(const ValReq&) = delete;
    ValReq& operator=(ValReq&&) = delete;

    virtual ~ValReq() = default;

    /*!
    @brief
        Validates that \bt_p{val} satisfies this value requirement.

    Appends causes to the error of the current thread, logs, and
    throws bt2c::Error on validation error.

    @param[in] val
        Value to validate.
    */
    void validate(const ValT& val) const
    {
        this->_validate(val);
    }

protected:
    /*!
    @brief
        Returns the text location of \bt_p{val}.

    @param[in] val
        Value of which to get the text location.

    @returns
        Text location of \bt_p{val}.
    */
    static const TextLoc& _loc(const ValT& val) noexcept
    {
        return ValOpsT::valLoc(val);
    }

    /*!
    @brief
        Logger of this value requirement.

    @returns
        Logger of this value requirement.
    */
    const Logger& _logger() const noexcept
    {
        return _mLogger;
    }

private:
    /*!
    @brief
        Validation method to implement to validate
        \bt_p{val} satisfies this value requirement.

    Must append causes to the error of the current thread, log, and
    throw bt2c::Error on validation error.

    @param[in] val
        Value to validate.
    */
    virtual void _validate(const ValT& val __attribute__((unused))) const
    {
    }

protected:
    Logger _mLogger;
};

/*! @brief Value type. */
enum class ValType
{
    /*! @brief Null. */
    Null,

    /*! @brief Boolean. */
    Bool,

    /*! @brief Signed integer. */
    SInt,

    /*! @brief Unsigned integer. */
    UInt,

    /*! @brief Real number. */
    Real,

    /*! @brief String. */
    Str,

    /*! @brief Array. */
    Array,

    /*! @brief Object/map. */
    Obj,
};

/*!
@brief
    "Value has type" requirement.

validate() validates that a value has a given type.
*/
template <typename ValT, typename ValOpsT>
class ValHasTypeReq : public ValReq<ValT, ValOpsT>
{
public:
    /*!
    @brief
        Builds a "value has type" requirement: validate() validates that
        the type of the value is \bt_p{type}.

    @param[in] type
        Required value type.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ValHasTypeReq(const ValType type, const Logger& parentLogger) noexcept :
        ValReq<ValT, ValOpsT> {parentLogger}, _mType {type}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to "value has type"
        requirement, forwarding the parameters to the constructor.

    @param[in] type
        Required value type.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New "value has type" requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const ValType type, const Logger& parentLogger)
    {
        return std::make_shared<ValHasTypeReq>(type, parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        if (ValOpsT::valType(val) != _mType) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(val), "Expecting {} {}.",
                ValOpsT::typeDetStr(_mType), ValOpsT::typeStr(_mType));
        }
    }

private:
    /* Required value type */
    ValType _mType;
};

/*!
@brief
    Any integer value requirement.

validate() validates that a value is an integer value
(unsigned or signed).
*/
template <typename ValT, typename ValOpsT>
class AnyIntValReq : public ValReq<ValT, ValOpsT>
{
public:
    /*!
    @brief
        Builds an any integer value requirement.

    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit AnyIntValReq(const Logger& parentLogger) noexcept :
        ValReq<ValT, ValOpsT> {parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to any integer value
        requirement, forwarding the parameters to the constructor.

    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New any integer value requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const Logger& parentLogger)
    {
        return std::make_shared<AnyIntValReq>(parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        if (!val.isUInt() && !val.isSInt()) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(this->_logger(), Error, this->_loc(val),
                                                            "Expecting an integer.");
        }
    }
};

/*!
@brief
    Unsigned integer value requirement.

validate() validates that a value is an unsigned
integer value.
*/
template <typename ValT, typename ValOpsT>
class UIntValReq : public ValHasTypeReq<ValT, ValOpsT>
{
public:
    /*!
    @brief
        Builds an unsigned integer value requirement.

    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit UIntValReq(const Logger& parentLogger) noexcept :
        ValHasTypeReq<ValT, ValOpsT> {ValType::UInt, parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to unsigned integer value
        requirement, forwarding the parameters to the constructor.

    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New unsigned integer value requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const Logger& parentLogger)
    {
        return std::make_shared<UIntValReq>(parentLogger);
    }
};

/*!
@brief
    Signed integer range value requirement.

validate() validates that a value is an integer value
(unsigned or signed) and that its raw value is between
-9,223,372,036,854,775,808 and 9,223,372,036,854,775,807.
*/
template <typename ValT, typename ValOpsT>
class SIntValReq : public AnyIntValReq<ValT, ValOpsT>
{
public:
    /*!
    @brief
        Builds a signed integer range value requirement.

    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit SIntValReq(const Logger& parentLogger) noexcept :
        AnyIntValReq<ValT, ValOpsT> {parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to signed integer range
        value requirement, forwarding the parameters to the constructor.

    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New any signed integer range value requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const Logger& parentLogger)
    {
        return std::make_shared<SIntValReq>(parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        /* Validate that it's an integer value */
        AnyIntValReq<ValT, ValOpsT>::_validate(val);

        if (ValOpsT::valType(val) == ValType::SInt) {
            /* Always correct */
            return;
        }

        /* Validate the raw value */
        static constexpr auto llMaxAsUll =
            static_cast<unsigned long long>(std::numeric_limits<long long>::max());

        const auto rawVal = ValOpsT::scalarValRawVal(ValOpsT::asUInt(val));

        if (rawVal > llMaxAsUll) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(val),
                "Expecting a signed integer: {} is greater than {}.", rawVal, llMaxAsUll);
        }
    }
};

/*!
@brief
    "Integer value in range" requirement template.

validate() validates that, given a value <strong><em>V</em></strong>
of type \bt_p{IntValT}:

- <strong><em>V</em></strong> has the type enumerator \bt_p{TypeV}.

- The raw value of <strong><em>V</em></strong> is within a given range.
*/
template <typename ValT, typename ValOpsT, typename IntValT, ValType TypeV>
class IntValInRangeReq : public ValHasTypeReq<ValT, ValOpsT>
{
private:
    /* Raw value type */
    using _RawVal = typename ValOpsT::template ScalarValRawValT<IntValT>;

public:
    /*!
    @brief
        Builds an "integer value in range" requirement.

    validate() validates that, given an integer value
    <strong><em>V</em></strong>:

    - If \bt_p{minVal} is set, then
      the raw value of <strong><em>V</em></strong> is greater than
      or equal to \bt_p{*minVal}.

    - If \bt_p{maxVal} is set,
      then the raw value of <strong><em>V</em></strong> is less
      than or equal to \bt_p{*maxVal}.

    @param[in] minVal
        If set, \bt_p{*minVal} is the required minimal value; otherwise,
        there's no required minimal value.
    @param[in] maxVal
        If set, \bt_p{*maxVal} is the required maximal value; otherwise,
        there's no required maximal value.
    @param[in] parentLogger
        Parent of the logger to create.

    @pre
        If both \bt_p{minVal} and \bt_p{maxVal} are set, then
        \bt_p{*minVal}&nbsp;&le;&nbsp;\bt_p{*maxVal}.
    */
    explicit IntValInRangeReq(const bt2s::optional<_RawVal>& minVal,
                              const bt2s::optional<_RawVal>& maxVal,
                              const Logger& parentLogger) noexcept :
        ValHasTypeReq<ValT, ValOpsT> {TypeV, parentLogger},
        _mMinVal {minVal ? *minVal : std::numeric_limits<_RawVal>::min()},
        _mMaxVal {maxVal ? *maxVal : std::numeric_limits<_RawVal>::max()}
    {
    }

    /*!
    @brief
        Builds an "integer value in range" requirement: validate()
        validates that the raw value of the integer value is
        exactly \bt_p{exactVal}.

    @param[in] exactVal
        Required raw integer value.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit IntValInRangeReq(const _RawVal exactVal, const Logger& parentLogger) noexcept :
        IntValInRangeReq {exactVal, exactVal, parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to "integer value in range"
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] minVal
        If set, \bt_p{*minVal} is the required minimal value; otherwise,
        there's no required minimal value.
    @param[in] maxVal
        If set, \bt_p{*maxVal} is the required maximal value; otherwise,
        there's no required maximal value.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New "integer value in range" requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const bt2s::optional<_RawVal>& minVal,
                                                     const bt2s::optional<_RawVal>& maxVal,
                                                     const Logger& parentLogger)
    {
        return std::make_shared<IntValInRangeReq>(minVal, maxVal, parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to "integer value in range"
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] exactVal
        Required raw integer value.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New "integer value in range" requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(const _RawVal exactVal,
                                                     const Logger& parentLogger)
    {
        return std::make_shared<IntValInRangeReq>(exactVal, parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        ValHasTypeReq<ValT, ValOpsT>::_validate(val);

        auto& intVal = static_cast<const IntValT&>(val);
        const auto rawVal = ValOpsT::scalarValRawVal(intVal);

        if (rawVal < _mMinVal) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(intVal),
                "Integer {} is too small: expecting at least {}.", rawVal, _mMinVal);
        }

        if (rawVal > _mMaxVal) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(intVal),
                "Integer {} is too large: expecting at most {}.", rawVal, _mMaxVal);
        }
    }

private:
    /* Minimum raw value */
    _RawVal _mMinVal;

    /* Maximum raw value */
    _RawVal _mMaxVal;
};

namespace internal {

template <typename RawValT>
std::string rawValStr(const RawValT& rawVal)
{
    return fmt::to_string(rawVal);
}

template <>
inline std::string rawValStr<std::string>(const std::string& val)
{
    return fmt::format("`{}`", val);
}

template <>
inline std::string rawValStr<bool>(const bool& val)
{
    return val ? "true" : "false";
}

} /* namespace internal */

/*!
@brief
    "Scalar value in set" requirement template.

validate() validates that, given a value <strong><em>V</em></strong>
of type \bt_p{ScalarValT}:

- <strong><em>V</em></strong> has the type enumerator \bt_p{TypeV}.

- The raw value of <strong><em>V</em></strong> is an element
  of a given set.
*/
template <typename ValT, typename ValOpsT, typename ScalarValT, ValType TypeV>
class ScalarValInSetReq : public ValHasTypeReq<ValT, ValOpsT>
{
private:
    /* Raw value type */
    using _RawVal = typename ValOpsT::template ScalarValRawValT<ScalarValT>;

public:
    /*
     * Using `std::set` instead of `std::unordered_set` because
     * _setStr() needs the elements in order.
     */

    /*!
    @brief
        Raw value set type.
    */
    using Set = std::set<_RawVal>;

    /*!
    @brief
        Builds a "scalar value in set" requirement: validate() validates
        that the raw value of the scalar value is an element of
        \bt_p{set}.

    @param[in] set
        Set of allowed raw values.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ScalarValInSetReq(Set set, const Logger& parentLogger) :
        ValHasTypeReq<ValT, ValOpsT> {TypeV, parentLogger}, _mSet {std::move(set)}
    {
    }

    /*!
    @brief
        Builds a "scalar value in set" requirement: validate() validates
        that the raw value of the scalar value is exactly \bt_p{rawVal}.

    This is effectively equivalent to using a set of one element
    (\bt_p{rawVal}).

    @param[in] rawVal
        Required raw value.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ScalarValInSetReq(_RawVal rawVal, const Logger& parentLogger) :
        ScalarValInSetReq {Set {std::move(rawVal)}, parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to "scalar value in set"
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] set
        Set of allowed raw values.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New "scalar value in set" requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(Set set, const Logger& parentLogger)
    {
        return std::make_shared<ScalarValInSetReq>(std::move(set), parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to "scalar value in set"
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] rawVal
        Required raw value.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New "scalar value in set" requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(_RawVal rawVal, const Logger& parentLogger)
    {
        return std::make_shared<ScalarValInSetReq>(std::move(rawVal), parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        ValHasTypeReq<ValT, ValOpsT>::_validate(val);

        auto& scalarVal = static_cast<const ScalarValT&>(val);
        const auto& rawVal = ValOpsT::scalarValRawVal(scalarVal);

        if (_mSet.find(rawVal) == _mSet.end()) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(val), "Unexpected value {}: expecting {}.",
                internal::rawValStr(rawVal), this->_setStr());
        }
    }

private:
    /*
     * Serializes the raw values of `_mSet` and returns the resulting
     * string.
     */
    std::string _setStr() const
    {
        if (_mSet.size() == 1) {
            /* Special case: direct value */
            return internal::rawValStr(*_mSet.begin());
        } else if (_mSet.size() == 2) {
            /* Special case: "or" word without any comma */
            return fmt::format("{} or {}", internal::rawValStr(*_mSet.begin()),
                               internal::rawValStr(*std::next(_mSet.begin())));
        }

        /* Enumeration with at least one comma */
        std::ostringstream ss;

        {
            const auto lastIt = std::prev(_mSet.end());

            for (auto it = _mSet.begin(); it != lastIt; ++it) {
                ss << internal::rawValStr(*it) << ", ";
            }

            ss << "or " << internal::rawValStr(*lastIt);
        }

        return ss.str();
    }

    /* Set of expected raw values */
    Set _mSet;
};

/*!
@brief
    Array value requirement.

validate() validates that, given a value <strong><em>V</em></strong>:

- <strong><em>V</em></strong> is an array value.

- The length of <strong><em>V</em></strong> is within a given range.

- \em All the elements of <strong><em>V</em></strong>
  satisfy a given value requirement.
*/
template <typename ValT, typename ValOpsT>
class ArrayValReq : public ValHasTypeReq<ValT, ValOpsT>
{
public:
    using SP = typename ValReq<ValT, ValOpsT>::SP;

    /*!
    @brief
        Builds an array value requirement.

    validate() validates that, for a given array value
    <strong><em>V</em></strong>:

    - If \bt_p{minSize} is set, then the length of
      <strong><em>V</em></strong> is greater than or
      equal to \bt_p{*minSize}.

    - If \bt_p{maxSize} is set, then the length of
      <strong><em>V</em></strong>
      is less than or equal to \bt_p{*maxSize}.

    - If \bt_p{elemValReq} is set, then \em all the elements of
      <strong><em>V</em></strong> satisfy \bt_p{*elemValReq}.

    @param[in] minSize
        If set, \bt_p{*minSize} is the required minimal array value
        length; otherwise, there's no required minimal length.
    @param[in] maxSize
        If set, \bt_p{*maxSize} is the required maximal array value
        size; otherwise, there's no required maximal length.
    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.

    @pre
        If both \bt_p{minSize} and \bt_p{maxSize} are set, then
        \bt_p{*minSize}&nbsp;&le;&nbsp;\bt_p{*maxSize}.
    */
    explicit ArrayValReq(const bt2s::optional<std::size_t>& minSize,
                         const bt2s::optional<std::size_t>& maxSize, SP elemValReq,
                         const Logger& parentLogger) :
        ValHasTypeReq<ValT, ValOpsT> {ValType::Array, parentLogger},
        _mMinSize {minSize ? *minSize : std::numeric_limits<std::size_t>::min()},
        _mMaxSize {maxSize ? *maxSize : std::numeric_limits<std::size_t>::max()},
        _mElemValReq {std::move(elemValReq)}
    {
    }

    /*!
    @brief
        Builds an array value requirement.

    validate() validates that, for a given array value
    <strong><em>V</em></strong>:

    - If \bt_p{minSize} is set, then the length of
      <strong><em>V</em></strong>
      is greater than or equal to \bt_p{*minSize}.

    - If \bt_p{maxSize} is set, then
      the length of <strong><em>V</em></strong>
      is less than or equal to \bt_p{*maxSize}.

    @param[in] minSize
        If set, \bt_p{*minSize} is the required minimal array value
        length; otherwise, there's no required minimal length.
    @param[in] maxSize
        If set, \bt_p{*maxSize} is the required maximal array value
        size; otherwise, there's no required maximal length.
    @param[in] parentLogger
        Parent of the logger to create.

    @pre
        If both \bt_p{minSize} and \bt_p{maxSize} are set, then
        \bt_p{*minSize}&nbsp;&le;&nbsp;\bt_p{*maxSize}.
    */
    explicit ArrayValReq(const bt2s::optional<std::size_t>& minSize,
                         const bt2s::optional<std::size_t>& maxSize, const Logger& parentLogger) :
        ArrayValReq {minSize, maxSize, nullptr, parentLogger}
    {
    }

    /*!
    @brief
        Builds an array value requirement.

    validate() validates that, for a given array value
    <strong><em>V</em></strong>:

    - The length of
      <strong><em>V</em></strong> is exactly \bt_p{exactSize}.

    - If \bt_p{elemValReq} is set, then \em all the elements of
      <strong><em>V</em></strong> satisfy \bt_p{*elemValReq}.

    @param[in] exactSize
        Required array value length.
    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ArrayValReq(const std::size_t exactSize, SP elemValReq, const Logger& parentLogger) :
        ArrayValReq {exactSize, exactSize, std::move(elemValReq), parentLogger}
    {
    }

    /*!
    @brief
        Builds an array value requirement: validate() validates that
        the length of the array value is exactly \bt_p{exactSize}.

    @param[in] exactSize
        Required array value length.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ArrayValReq(const std::size_t exactSize, const Logger& parentLogger) :
        ArrayValReq {exactSize, exactSize, nullptr, parentLogger}
    {
    }

    /*!
    @brief
        Builds an array value requirement: validate() validates that,
        if \bt_p{elemValReq} is set, then \em all the elements of
        the array value satisfy \bt_p{*elemValReq}.

    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ArrayValReq(SP elemValReq, const Logger& parentLogger) :
        ArrayValReq {bt2s::nullopt, bt2s::nullopt, std::move(elemValReq), parentLogger}
    {
    }

    /*!
    @brief
        Builds an array value requirement: validate() validates that
        the value is an array value.

    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ArrayValReq(const Logger& parentLogger) :
        ArrayValReq {bt2s::nullopt, bt2s::nullopt, parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] minSize
        If set, \bt_p{*minSize} is the required minimal array value
        length; otherwise, there's no required minimal length.
    @param[in] maxSize
        If set, \bt_p{*maxSize} is the required maximal array value
        size; otherwise, there's no required maximal length.
    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(const bt2s::optional<std::size_t>& minSize,
                     const bt2s::optional<std::size_t>& maxSize, SP elemValReq,
                     const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(minSize, maxSize, std::move(elemValReq), parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] minSize
        If set, \bt_p{*minSize} is the required minimal array value
        length; otherwise, there's no required minimal length.
    @param[in] maxSize
        If set, \bt_p{*maxSize} is the required maximal array value
        size; otherwise, there's no required maximal length.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(const bt2s::optional<std::size_t>& minSize,
                     const bt2s::optional<std::size_t>& maxSize, const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(minSize, maxSize, parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] exactSize
        Required array value length.
    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(const std::size_t exactSize, SP elemValReq, const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(exactSize, std::move(elemValReq), parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] exactSize
        Required array value length.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(const std::size_t exactSize, const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(exactSize, parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] elemValReq
        If set, \bt_p{*elemValReq} is the element value requirement;
        otherwise, there's no element value requirement.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(SP elemValReq, const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(std::move(elemValReq), parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to array value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New array value requirement shared pointer.
    */
    static SP shared(const Logger& parentLogger)
    {
        return std::make_shared<ArrayValReq>(parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        ValHasTypeReq<ValT, ValOpsT>::_validate(val);

        auto& arrayVal = ValOpsT::asArray(val);
        const auto size = ValOpsT::arrayValSize(arrayVal);

        if (size < _mMinSize) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(val),
                "Size of array ({}) is too small: expecting at least {} elements.", size,
                _mMinSize);
        }

        if (size > _mMaxSize) {
            BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                this->_logger(), Error, this->_loc(val),
                "Size of array ({}) is too large: expecting at most {} elements.", size, _mMaxSize);
        }

        if (_mElemValReq) {
            for (std::size_t i = 0; i < size; ++i) {
                auto& elemVal = ValOpsT::arrayValElem(arrayVal, i);

                try {
                    _mElemValReq->validate(elemVal);
                } catch (const Error&) {
                    BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_RETHROW_SPEC(
                        this->_logger(), this->_loc(elemVal), "Invalid array element #{}.", i + 1);
                }
            }
        }
    }

private:
    std::size_t _mMinSize;
    std::size_t _mMaxSize;
    SP _mElemValReq;
};

/*!
@brief
    Object/map value property requirement.

An instance of this class isn't a value requirement itself: an ObjValReq
instance contains zero or more ObjValPropReq instances which hold:

- The value requirement of the property.
- Whether or not the property is required.
*/
template <typename ValT, typename ValOpsT>
class ObjValPropReq final
{
public:
    /*!
    @brief
        Builds an object/map value property requirement, required if
        \bt_p{isRequired} is <code>true</code>: if \bt_p{valReq} is set, then
        validate() validates that a value satisfies \bt_p{*valReq}.

    Not \c explicit to make the construction of ObjValReq lighter.

    @param[in] valReq
        If set, \bt_p{*valReq} is the value requirement of the property;
        otherwise, there's no value requirement.
    @param[in] isRequired
        \c true if this property is required.
    */
    ObjValPropReq(typename ValReq<ValT, ValOpsT>::SP valReq = nullptr,
                  const bool isRequired = false) :
        _mIsRequired {isRequired},
        _mValReq {std::move(valReq)}
    {
    }

    /*!
    @brief
        Whether or not the property is required.

    @returns
        \c true if this property is required.
    */
    bool isRequired() const noexcept
    {
        return _mIsRequired;
    }

    /*!
    @brief
        Validates that \bt_p{val} satisfies the value requirement
        of this property, if any.

    @param[in] val
        Value to validate.
    */
    void validate(const ValT& val) const
    {
        if (_mValReq) {
            _mValReq->validate(val);
        }
    }

private:
    /* Whether or not this property is required */
    bool _mIsRequired = false;

    /* Requirement of the value */
    typename ValReq<ValT, ValOpsT>::SP _mValReq;
};

/*!
@brief
    Object/map value requirement.

validate() validates that, given a value <strong><em>V</em></strong>:

- <strong><em>V</em></strong> is an object/map value.

- The properties of <strong><em>V</em></strong> satisfy a given set of
  object value property requirements.
*/
template <typename ValT, typename ValOpsT>
class ObjValReq : public ValHasTypeReq<ValT, ValOpsT>
{
public:
    /*! @brief Map of property name to property requirement. */
    using PropReqs = std::unordered_map<std::string, ObjValPropReq<ValT, ValOpsT>>;

    /*! @brief Single entry (pair) within PropReqs. */
    using PropReqsEntry = typename PropReqs::value_type;

public:
    /*!
    @brief
        Builds an object value requirement.

    validate() validates that, for a given object/map value
    <strong><em>V</em></strong>:

    - If \bt_p{allowUnknownProps} is false, then
      <strong><em>V</em></strong> has no value of which
      the key isn't an element of the keys of \bt_p{propReqs}.

    - For each property requirement <strong><em>PR</em></strong>
      having the key <strong><em>K</em></strong> in
      \bt_p{propReqs}: if isRequired() returns \c true for with
      <strong><em>PR</em></strong>, then a value having the key
      <strong><em>K</em></strong> exists in
      <strong><em>V</em></strong>.

    - For each value <strong><em>VV</em></strong> having the key
      <strong><em>K</em></strong> in <strong><em>V</em></strong>:
      <strong><em>VV</em></strong> satisfies the value
      requirement, if any, of \bt_p{propReqs[K]}.

    @param[in] propReqs
        Map of property requirements.
    @param[in] allowUnknownProps
        \c true to allow unknown properties.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ObjValReq(PropReqs propReqs, const bool allowUnknownProps,
                       const Logger& parentLogger) :
        ValHasTypeReq<ValT, ValOpsT> {ValType::Obj, parentLogger},
        _mPropReqs {std::move(propReqs)}, _mAllowUnknownProps {allowUnknownProps}
    {
    }

    /*!
    @brief
        Builds an object value requirement.

    validate() validates that, for a given object/map value
    <strong><em>V</em></strong>:

    - <strong><em>V</em></strong> has no value of which the key isn't
      an element of the keys \bt_p{propReqs}.

    - For each property requirement <strong><em>PR</em></strong>
      having the key <strong><em>K</em></strong> in
      \bt_p{propReqs}: if isRequired() returns \c true for with
      <strong><em>PR</em></strong>, then a value having the key
      <strong><em>K</em></strong> exists in
      <strong><em>V</em></strong>.

    - For each value <strong><em>VV</em></strong> having the key
      <strong><em>K</em></strong> in <strong><em>V</em></strong>:
      <strong><em>VV</em></strong> satisfies the value
      requirement, if any, of \bt_p{propReqs[K]}.

    @param[in] propReqs
        Map of property requirements.
    @param[in] parentLogger
        Parent of the logger to create.
    */
    explicit ObjValReq(PropReqs propReqs, const Logger& parentLogger) :
        ObjValReq {std::move(propReqs), false, parentLogger}
    {
    }

    /*!
    @brief
        Creates and returns a shared pointer to object/map value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] propReqs
        Map of property requirements.
    @param[in] allowUnknownProps
        \c true to allow unknown properties.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New object/map value requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP
    shared(PropReqs propReqs, const bool allowUnknownProps, const Logger& parentLogger)
    {
        return std::make_shared<ObjValReq>(std::move(propReqs), allowUnknownProps, parentLogger);
    }

    /*!
    @brief
        Creates and returns a shared pointer to object/map value
        requirement, forwarding the parameters to the corresponding
        constructor.

    @param[in] propReqs
        Map of property requirements.
    @param[in] parentLogger
        Parent of the logger to create.

    @returns
        New object/map value requirement shared pointer.
    */
    static typename ValReq<ValT, ValOpsT>::SP shared(PropReqs propReqs, const Logger& parentLogger)
    {
        return std::make_shared<ObjValReq>(std::move(propReqs), parentLogger);
    }

protected:
    void _validate(const ValT& val) const override
    {
        ValHasTypeReq<ValT, ValOpsT>::_validate(val);

        auto& objVal = ValOpsT::asObj(val);
        const auto objValTypeStr = ValOpsT::typeStr(ValType::Obj);

        for (auto& keyPropReqPair : _mPropReqs) {
            auto& key = keyPropReqPair.first;

            if (keyPropReqPair.second.isRequired() && !ValOpsT::objValVal(objVal, key)) {
                BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                    this->_logger(), Error, this->_loc(objVal), "Missing mandatory {} {} `{}`.",
                    objValTypeStr, ValOpsT::objValPropName, key);
            }
        }

        for (auto it = ValOpsT::objValBegin(objVal); it != ValOpsT::objValEnd(objVal); ++it) {
            auto& key = ValOpsT::objValItKey(it);
            auto& propVal = ValOpsT::objValItVal(it);
            const auto keyPropReqPairIt = _mPropReqs.find(key);

            if (keyPropReqPairIt == _mPropReqs.end()) {
                /* No property requirement found */
                if (_mAllowUnknownProps) {
                    continue;
                } else {
                    BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_THROW_SPEC(
                        this->_logger(), Error, this->_loc(propVal), "Unknown {} {} `{}`.",
                        objValTypeStr, ValOpsT::objValPropName, key);
                }
            }

            try {
                keyPropReqPairIt->second.validate(propVal);
            } catch (const Error&) {
                BT_CPPLOGE_TEXT_LOC_APPEND_CAUSE_AND_RETHROW_SPEC(
                    this->_logger(), this->_loc(propVal), "Invalid {} {} `{}`.", objValTypeStr,
                    ValOpsT::objValPropName, key);
            }
        }
    }

private:
    PropReqs _mPropReqs;
    bool _mAllowUnknownProps;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_VAL_REQ_HPP */
