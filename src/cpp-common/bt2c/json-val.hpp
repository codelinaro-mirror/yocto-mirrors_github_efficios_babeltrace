/*
 * Copyright (c) 2022-2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_HPP
#define BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_HPP

#include <cstdlib>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/assert.h"

#include "text-loc.hpp"

namespace bt2c {

/*!
@addtogroup common-cpp-bt2c-json
@{
*/

/*! @brief JSON value type. */
enum class JsonValType
{
    /*!
    @brief
        Null value (#JsonNullVal).
    */
    Null,

    /*!
    @brief
        Boolean value (#JsonBoolVal).
    */
    Bool,

    /*!
    @brief
        Signed integer value (#JsonSIntVal).
     */
    SInt,

    /*!
    @brief
        Unsigned integer value (#JsonUIntVal).
     */
    UInt,

    /*!
    @brief
        Real value (#JsonRealVal).
    */
    Real,

    /*!
    @brief
        String value (#JsonStrVal).
    */
    Str,

    /*!
    @brief
        Array value (#JsonArrayVal).
    */
    Array,

    /*!
    @brief
        Object value (#JsonObjVal).
    */
    Obj,
};

class JsonNullVal;

template <typename, JsonValType>
class JsonScalarVal;

/*!
@brief
    JSON boolean value.

#JsonScalarVal with \c bool and JsonValType::Bool.
*/
using JsonBoolVal = JsonScalarVal<bool, JsonValType::Bool>;

/*!
@brief
    JSON signed integer value.

#JsonScalarVal with <code>long long</code> and JsonValType::SInt.
*/
using JsonSIntVal = JsonScalarVal<long long, JsonValType::SInt>;

/*!
@brief
    JSON unsigned integer value.

#JsonScalarVal with <code>unsigned long long</code> and
JsonValType::UInt.
*/
using JsonUIntVal = JsonScalarVal<unsigned long long, JsonValType::UInt>;

/*!
@brief
    JSON real value.

#JsonScalarVal with \c double and JsonValType::Real.
*/
using JsonRealVal = JsonScalarVal<double, JsonValType::Real>;

/*!
@brief
    JSON string value.

#JsonScalarVal with \c std::string and JsonValType::Str.
*/
using JsonStrVal = JsonScalarVal<std::string, JsonValType::Str>;

class JsonArrayVal;
class JsonObjVal;

/*!
@brief
    Visitor of JSON value.

Inherit this class and override the virtual
<code>%visit()</code> methods.

Then, visit a JSON value as such:

@code{.cpp}
MyVisitor visitor;

myJsonVal.accept(visitor);
@endcode
*/
class JsonValVisitor
{
protected:
    explicit JsonValVisitor() = default;

public:
    virtual ~JsonValVisitor() = default;

    /*!
    @brief
        Visits a JSON null value.
    */
    virtual void visit(const JsonNullVal&)
    {
    }

    /*!
    @brief
        Visits a JSON boolean value.
    */
    virtual void visit(const JsonBoolVal&)
    {
    }

    /*!
    @brief
        Visits a JSON signed integer value.
    */
    virtual void visit(const JsonSIntVal&)
    {
    }

    /*!
    @brief
        Visits a JSON unsigned integer value.
    */
    virtual void visit(const JsonUIntVal&)
    {
    }

    /*!
    @brief
        Visits a JSON real value.
    */
    virtual void visit(const JsonRealVal&)
    {
    }

    /*!
    @brief
        Visits a JSON string value.
    */
    virtual void visit(const JsonStrVal&)
    {
    }

    /*!
    @brief
        Visits a JSON array value.
    */
    virtual void visit(const JsonArrayVal&)
    {
    }

    /*!
    @brief
        Visits a JSON object value.
    */
    virtual void visit(const JsonObjVal&)
    {
    }
};

/*!
@brief
    JSON value abstract base class.

Check the specific type with the type() or with the various
<code>is*()</code> methods.

Cast to a concrete JSON value object with the various <code>as*()</code>
methods.

Check the original text location of a JSON value object with loc().

Accept a visitor with accept().

@note
    The copy/move constructors/operators are deleted to simplify the
    interface.
*/
class JsonVal
{
public:
    /*! @brief Useful JSON type alias. */
    using Type = JsonValType;

    /*! @brief Unique pointer to constant JSON value. */
    using UP = std::unique_ptr<const JsonVal>;

protected:
    /*
     * Builds a JSON value of type `type` located at `loc`.
     */
    explicit JsonVal(Type type, TextLoc&& loc) noexcept;

public:
    /* Deleted copy/move constructors/operators to simplify */
    JsonVal(const JsonVal&) = delete;
    JsonVal(JsonVal&&) = delete;
    JsonVal& operator=(const JsonVal&) = delete;
    JsonVal& operator=(JsonVal&&) = delete;

    virtual ~JsonVal() = default;

    /*!
    @brief
        Specific type.

    @returns
        Specific type.
    */
    Type type() const noexcept
    {
        return _mType;
    }

    /*!
    @brief
        Original text location.

    @returns
        Original text location.
    */
    const TextLoc& loc() const noexcept
    {
        return _mLoc;
    }

    /*!
    @brief
        Whether or not this JSON value is a null value.

    @returns
        \c true if this JSON value is a null value.

    @sa type()
    */
    bool isNull() const noexcept
    {
        return _mType == Type::Null;
    }

    /*!
    @brief
        Whether or not this JSON value is a boolean value.

    @returns
        \c true if this JSON value is a boolean value.

    @sa type()
    */
    bool isBool() const noexcept
    {
        return _mType == Type::Bool;
    }

    /*!
    @brief
        Whether or not this JSON value is a signed integer value.

    @returns
        \c true if this JSON value is a signed integer value.

    @sa type()
    */
    bool isSInt() const noexcept
    {
        return _mType == Type::SInt;
    }

    /*!
    @brief
        Whether or not this JSON value is an unsigned integer value.

    @returns
        \c true if this JSON value is an unsigned integer value.

    @sa type()
    */
    bool isUInt() const noexcept
    {
        return _mType == Type::UInt;
    }

    /*!
    @brief
        Whether or not this JSON value is a real number.

    @returns
        \c true if this JSON value is a real number.

    @sa type()
    */
    bool isReal() const noexcept
    {
        return _mType == Type::Real;
    }

    /*!
    @brief
        Whether or not this JSON value is a string value.

    @returns
        \c true if this JSON value is a string value.

    @sa type()
    */
    bool isStr() const noexcept
    {
        return _mType == Type::Str;
    }

    /*!
    @brief
        Whether or not this JSON value is an array value.

    @returns
        \c true if this JSON value is an array value.

    @sa type()
    */
    bool isArray() const noexcept
    {
        return _mType == Type::Array;
    }

    /*!
    @brief
        Whether or not this JSON value is an object value.

    @returns
        \c true if this JSON value is an object value.

    @sa type()
    */
    bool isObj() const noexcept
    {
        return _mType == Type::Obj;
    }

    /*!
    @brief
        This JSON value as a null value.

    @returns
        This JSON value as a null value.

    @pre
        This JSON value is a null value (isNull() returns \c true).
    */
    const JsonNullVal& asNull() const noexcept;

    /*!
    @brief
        This JSON value as a boolean value.

    @returns
        This JSON value as a boolean value.

    @pre
        This JSON value is a boolean value (isBool() returns \c true).
    */
    const JsonBoolVal& asBool() const noexcept;

    /*!
    @brief
        This JSON value as a signed integer value.

    @returns
        This JSON value as a signed integer value.

    @pre
        This JSON value is a signed integer value (isSInt()
        returns \c true).
    */
    const JsonSIntVal& asSInt() const noexcept;

    /*!
    @brief
        This JSON value as an unsigned integer value.

    @returns
        This JSON value as an unsigned integer value.

    @pre
        This JSON value is an unsigned integer value (isUInt()
        returns \c true).
    */
    const JsonUIntVal& asUInt() const noexcept;

    /*!
    @brief
        This JSON value as a real value.

    @returns
        This JSON value as a real value.

    @pre
        This JSON value is a real value (isReal() returns \c true).
    */
    const JsonRealVal& asReal() const noexcept;

    /*!
    @brief
        This JSON value as a string value.

    @returns
        This JSON value as a string value.

    @pre
        This JSON value is a string value (isStr() returns \c true).
    */
    const JsonStrVal& asStr() const noexcept;

    /*!
    @brief
        This JSON value as an array value.

    @returns
        This JSON value as an array value.

    @pre
        This JSON value is an array value (isArray() returns \c true).
    */
    const JsonArrayVal& asArray() const noexcept;

    /*!
    @brief
        This JSON value as an object value.

    @returns
        This JSON value as an object value.

    @pre
        This JSON value is an object value (isObj() returns \c true).
    */
    const JsonObjVal& asObj() const noexcept;

    /*!
    @brief
        Accepts \bt_p{visitor} to visit this JSON value.

    This function calls the corresponding \c visit() virtual method of
    \bt_p{visitor} depending on the type of this JSON value.

    @param[in] visitor
        Visitor to accept.
    */
    void accept(JsonValVisitor& visitor) const;

private:
    virtual void _accept(JsonValVisitor& visitor) const = 0;

    /* JSON value type */
    Type _mType;

    /* Location of this value within some original JSON text */
    TextLoc _mLoc;
};

/*!
@brief
    JSON null value.

%Type: JsonValType::Null.
*/
class JsonNullVal : public JsonVal
{
public:
    /*! @brief Unique pointer to constant JSON null value. */
    using UP = std::unique_ptr<const JsonNullVal>;

    /*!
    @brief
        Builds a JSON null value located at \bt_p{loc}.

    @param[in] loc
        Text location of the created JSON null value.
    */
    explicit JsonNullVal(TextLoc loc) noexcept;

private:
    void _accept(JsonValVisitor& visitor) const override;
};

/*!
@brief
    JSON scalar value template.

Such a JSON value holds a raw value of type \bt_p{ValT}. Its type()
method returns \bt_p{TypeV}.

Get the raw value of a JSON scalar value with val() or operator*().
*/
template <typename ValT, JsonValType TypeV>
class JsonScalarVal : public JsonVal
{
public:
    /*! @brief Raw value. */
    using Val = ValT;

    /*! @brief Unique pointer to constant JSON scalar value. */
    using UP = std::unique_ptr<const JsonScalarVal<ValT, TypeV>>;

    /*!
    @brief
        Builds a JSON scalar value, located at \bt_p{loc}, with the
        raw value \bt_p{val}.

    @param[in] val
        Raw value of the created JSON scalar value.
    @param[in] loc
        Text location of the created JSON scalar value.
    */
    explicit JsonScalarVal(ValT val, TextLoc loc) noexcept :
        JsonVal {TypeV, std::move(loc)}, _mVal {std::move(val)}
    {
    }

    /*!
    @brief
        Raw value.

    @returns
        Raw value.

    @sa operator*()
    */
    const ValT& val() const noexcept
    {
        return _mVal;
    }

    /*!
    @brief
        Raw value.

    @returns
        Raw value.

    @sa val()
    */
    const ValT& operator*() const noexcept
    {
        return _mVal;
    }

private:
    void _accept(JsonValVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    /* Raw value */
    ValT _mVal;
};

/*!
@brief
    JSON compound value template.

Such a JSON value holds a container of JSON values of type
\bt_p{ContainerT}. Its type() method returns \bt_p{TypeV}.

Iterate a JSON compound value with begin() and end().

Get the number of elements contained in a JSON compound value with
size() and check for emptiness with isEmpty().
*/
template <typename ContainerT, JsonValType TypeV>
class JsonCompoundVal : public JsonVal
{
public:
    /*! @brief %Container. */
    using Container = ContainerT;

protected:
    /*!
    @brief
        Builds a JSON compound value, located at \bt_p{loc}, containing
        the JSON values \bt_p{vals}.

    @param[in] vals
        Contained JSON values of the created JSON compound value.
    @param[in] loc
        Text location of the created JSON compound value.
    */
    explicit JsonCompoundVal(ContainerT&& vals, TextLoc&& loc) :
        JsonVal {TypeV, std::move(loc)}, _mVals {std::move(vals)}
    {
    }

public:
    /*!
    @brief
        Constant container iterator at the first value.

    @returns
        Constant container iterator at the first value.
    */
    typename ContainerT::const_iterator begin() const noexcept
    {
        return _mVals.begin();
    }

    /*!
    @brief
        Constant container iterator after the last value.

    @returns
        Constant container iterator after the last value.
    */
    typename ContainerT::const_iterator end() const noexcept
    {
        return _mVals.end();
    }

    /*!
    @brief
        Number of contained JSON values.

    @returns
        Number of contained JSON values.
    */
    std::size_t size() const noexcept
    {
        return _mVals.size();
    }

    /*!
    @brief
        Whether or not this JSON compound value is empty.

    @retval false
        Not empty.
    @retval true
        Empty.
    */
    bool isEmpty() const noexcept
    {
        return _mVals.empty();
    }

protected:
    /* %Container of JSON values */
    ContainerT _mVals;
};

/*!
@brief
    JSON array value.

Get a contained JSON value by index with operator[]().
*/
class JsonArrayVal : public JsonCompoundVal<std::vector<JsonVal::UP>, JsonValType::Array>
{
public:
    /*! @brief Unique pointer to constant JSON array value. */
    using UP = std::unique_ptr<const JsonArrayVal>;

    /*!
    @brief
        Builds a JSON array value, located at \bt_p{loc}, containing
        the JSON values \bt_p{vals}.

    @param[in] vals
        Contained JSON values of the created JSON array value.
    @param[in] loc
        Text location of the created JSON array value.
    */
    explicit JsonArrayVal(Container&& vals, TextLoc loc);

    /*!
    @brief
        Contained JSON value at index \bt_p{index}.

    @param[in] index
        Index of the contained JSON value to get.

    @returns
        JSON value contained at index \bt_p{index}.

    @pre
        \bt_p{index}&nbsp;&lt;&nbsp;size().
    */
    const JsonVal& operator[](const std::size_t index) const noexcept
    {
        BT_ASSERT_DBG(index < this->_mVals.size());
        return *_mVals[index];
    }

private:
    void _accept(JsonValVisitor& visitor) const override;
};

/*!
@brief
    JSON object value.

Get a contained JSON value by key with one of:

- operator[]()
- val(const std::string&) const
- val(const std::string&, const JsonValT&) const

Get the raw value of a contained JSON scalar value by key with
one of:

- rawBoolVal()
- rawUIntVal()
- rawSIntVal()
- rawRealVal()
- rawStrVal()
- rawVal(const std::string&, bool) const
- rawVal(const std::string&, unsigned long long) const
- rawVal(const std::string&, const long long) const
- rawVal(const std::string&, const double) const
- rawVal(const std::string&, const char * const) const
- rawVal(const std::string&, const typename JsonValT::Val) const

Check if a JSON object value contains a JSON value with a specific key
with hasValue().
*/
class JsonObjVal :
    public JsonCompoundVal<std::unordered_map<std::string, JsonVal::UP>, JsonValType::Obj>
{
public:
    /*! @brief Unique pointer to constant JSON object value. */
    using UP = std::unique_ptr<const JsonObjVal>;

    /*!
    @brief
        Builds a JSON object value, located at \bt_p{loc}, containing
        the JSON values \bt_p{vals}.

    @param[in] vals
        Contained JSON values of the created JSON object value.
    @param[in] loc
        Text location of the created JSON object value.
    */
    explicit JsonObjVal(Container&& vals, TextLoc loc);

    /*!
    @brief
        Contained JSON value having the key \bt_p{key}, or \c nullptr
        if not found.

    @param[in] key
        Key of the contained JSON value to try to get.

    @returns
        JSON value having the key \bt_p{key}, or \c nullptr if not
        found.
    */
    const JsonVal *operator[](const std::string& key) const noexcept
    {
        const auto it = _mVals.find(key);

        if (it == _mVals.end()) {
            return nullptr;
        }

        return it->second.get();
    }

    /*!
    @brief
        Contained JSON value having the key \bt_p{key}.

    @param[in] key
        Key of the contained JSON value to get.

    @returns
        JSON value having the key \bt_p{key}.

    @pre
        hasValue() with \bt_p{key} returns \c true.
    */
    template <typename JsonValT>
    const JsonValT& val(const std::string& key) const noexcept
    {
        const auto val = (*this)[key];

        BT_ASSERT(val);
        return static_cast<const JsonValT&>(*val);
    }

    /*!
    @brief
        Raw value of the contained JSON boolean value having the
        key \bt_p{key}.

    @param[in] key
        Key of the contained JSON boolean value of which to get
        the raw value.

    @returns
        Raw value of JSON boolean value having the key \bt_p{key}.

    @pre
        - hasValue() with \bt_p{key} returns \c true.
        - val() with \bt_p{key} returns a JSON boolean value.
    */
    bool rawBoolVal(const std::string& key) const noexcept
    {
        return *this->val<JsonBoolVal>(key);
    }

    /*!
    @brief
        Raw value of the contained JSON unsigned integer value having
        the key \bt_p{key}.

    @param[in] key
        Key of the contained JSON unsigned integer value of which to get
        the raw value.

    @returns
        Raw value of JSON unsigned integer value having the key
        \bt_p{key}.

    @pre
        - hasValue() with \bt_p{key} returns \c true.
        - val() with \bt_p{key} returns a JSON unsigned integer value.
    */
    unsigned long long rawUIntVal(const std::string& key) const noexcept
    {
        return *this->val<JsonUIntVal>(key);
    }

    /*!
    @brief
        Raw value of the contained JSON signed integer value having the
        key \bt_p{key}.

    @param[in] key
        Key of the contained JSON signed integer value of which to get
        the raw value.

    @returns
        Raw value of JSON signed integer value having the key
        \bt_p{key}.

    @pre
        - hasValue() with \bt_p{key} returns \c true.
        - val() with \bt_p{key} returns a JSON signed integer value.
    */
    long long rawSIntVal(const std::string& key) const noexcept
    {
        return *this->val<JsonSIntVal>(key);
    }

    /*!
    @brief
        Raw value of the contained JSON real value having the
        key \bt_p{key}.

    @param[in] key
        Key of the contained JSON real value of which to get
        the raw value.

    @returns
        Raw value of JSON real value having the key \bt_p{key}.

    @pre
        - hasValue() with \bt_p{key} returns \c true.
        - val() with \bt_p{key} returns a JSON real value.
    */
    double rawRealVal(const std::string& key) const noexcept
    {
        return *this->val<JsonRealVal>(key);
    }

    /*!
    @brief
        Raw value of the contained JSON string value having the
        key \bt_p{key}.

    @param[in] key
        Key of the contained JSON string value of which to get
        the raw value.

    @returns
        Raw value of JSON string value having the key \bt_p{key}.

    @pre
        - hasValue() with \bt_p{key} returns \c true.
        - val() with \bt_p{key} returns a JSON string value.
    */
    const std::string& rawStrVal(const std::string& key) const noexcept
    {
        return *this->val<JsonStrVal>(key);
    }

    /*!
    @brief
        Contained JSON value of type \bt_p{JsonValT} having the
        key \bt_p{key}, or \bt_p{defJsonVal} if not found.

    @param[in] key
        Key of the contained JSON value to try to get.
    @param[in] defJsonVal
        Default JSON value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Contained JSON value having the key \bt_p{key}, or
        \bt_p{defJsonVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON value of type
        \bt_p{JsonValT}.
    */
    template <typename JsonValT>
    const JsonValT& val(const std::string& key, const JsonValT& defJsonVal) const noexcept
    {
        const auto jsonVal = (*this)[key];

        return jsonVal ? static_cast<const JsonValT&>(*jsonVal) : defJsonVal;
    }

    /*!
    @brief
        Raw value of the contained JSON scalar value of type
        \bt_p{JsonValT} having the key \bt_p{key}, or \bt_p{defVal} if
        not found.

    @param[in] key
        Key of the contained JSON scalar value of which to try to get
        the raw value.
    @param[in] defVal
        Default value to return when no JSON scalar value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON scalar value having the key
        \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON value of type
        \bt_p{JsonValT}.
    */
    template <typename JsonValT>
    typename JsonValT::Val rawVal(const std::string& key,
                                  const typename JsonValT::Val defVal) const noexcept
    {
        const auto jsonVal = (*this)[key];

        return jsonVal ? *static_cast<const JsonValT&>(*jsonVal) : defVal;
    }

    /*!
    @brief
        Raw value of the contained JSON boolean value
        having the key \bt_p{key}, or \bt_p{defVal} if not found.

    @param[in] key
        Key of the contained JSON boolean value of which
        to try to get the raw value.
    @param[in] defVal
        Default value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON boolean value having the
        key \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON boolean value.
    */
    bool rawVal(const std::string& key, const bool defVal) const noexcept
    {
        return this->rawVal<JsonBoolVal>(key, defVal);
    }

    /*!
    @brief
        Raw value of the contained JSON unsigned integer value
        having the key \bt_p{key}, or \bt_p{defVal} if not found.

    @param[in] key
        Key of the contained JSON unsigned integer value of which
        to try to get the raw value.
    @param[in] defVal
        Default value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON unsigned integer value having
        the key \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON unsigned integer value.
    */
    unsigned long long rawVal(const std::string& key,
                              const unsigned long long defVal) const noexcept
    {
        return this->rawVal<JsonUIntVal>(key, defVal);
    }

    /*!
    @brief
        Raw value of the contained JSON signed integer value
        having the key \bt_p{key}, or \bt_p{defVal} if not found.

    @param[in] key
        Key of the contained JSON signed integer value of which
        to try to get the raw value.
    @param[in] defVal
        Default value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON signed integer value having
        the key \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON signed integer value.
    */
    long long rawVal(const std::string& key, const long long defVal) const noexcept
    {
        return this->rawVal<JsonSIntVal>(key, defVal);
    }

    /*!
    @brief
        Raw value of the contained JSON real value
        having the key \bt_p{key}, or \bt_p{defVal} if not found.

    @param[in] key
        Key of the contained JSON real value of which
        to try to get the raw value.
    @param[in] defVal
        Default value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON real value having
        the key \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON real value.
    */
    double rawVal(const std::string& key, const double defVal) const noexcept
    {
        return this->rawVal<JsonRealVal>(key, defVal);
    }

    /*!
    @brief
        Raw value of the contained JSON string value
        having the key \bt_p{key}, or \bt_p{defVal} if not found.

    @param[in] key
        Key of the contained JSON string value of which
        to try to get the raw value.
    @param[in] defVal
        Default value to return when no JSON value having the key
        \bt_p{key} exists.

    @returns
        Raw value of the contained JSON string value having
        the key \bt_p{key}, or \bt_p{defVal} if not found.

    @pre
        If hasValue() with \bt_p{key} is \c true, then
        operator[]() with \bt_p{key} returns a JSON string value.
    */
    const char *rawVal(const std::string& key, const char * const defVal) const noexcept
    {
        const auto jsonVal = (*this)[key];

        return jsonVal ? (*jsonVal->asStr()).c_str() : defVal;
    }

    /*!
    @brief
        Whether or not this JSON object value has a value with the
        key \bt_p{key}.

    @param[in] key
        Key to check.

    @retval false
        Not found.
    @retval true
        Found.
    */
    bool hasValue(const std::string& key) const noexcept
    {
        return _mVals.find(key) != _mVals.end();
    }

private:
    void _accept(JsonValVisitor& visitor) const override;
};

/*!
@brief
    Creates and returns a new JSON null value located at \bt_p{loc}.

@param[in] loc
    Text location of the created JSON null value.

@returns
    Created JSON null value.
*/
JsonNullVal::UP createJsonVal(TextLoc loc);

/*!
@brief
    Creates and returns a new JSON boolean value, located at \bt_p{loc},
    with the raw value \bt_p{val}.

@param[in] val
    Raw value of the created JSON boolean value.
@param[in] loc
    Text location of the created JSON boolean value.

@returns
    Created JSON boolean value.
*/
JsonBoolVal::UP createJsonVal(bool val, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON signed integer value, located at
    \bt_p{loc}, with the raw value \bt_p{val}.

@param[in] val
    Raw value of the created JSON signed integer value.
@param[in] loc
    Text location of the created JSON signed integer value.

@returns
    Created JSON signed integer value.
*/
JsonSIntVal::UP createJsonVal(long long val, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON unsigned integer value, located at
    \bt_p{loc}, with the raw value \bt_p{val}.

@param[in] val
    Raw value of the created JSON unsigned integer value.
@param[in] loc
    Text location of the created JSON unsigned integer value.

@returns
    Created JSON unsigned integer value.
*/
JsonUIntVal::UP createJsonVal(unsigned long long val, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON real value, located at \bt_p{loc},
    with the raw value \bt_p{val}.

@param[in] val
    Raw value of the created JSON real value.
@param[in] loc
    Text location of the created JSON real value.

@returns
    Created JSON real value.
*/
JsonRealVal::UP createJsonVal(double val, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON string value, located at \bt_p{loc},
    with the raw value \bt_p{val}.

@param[in] val
    Raw value of the created JSON string value.
@param[in] loc
    Text location of the created JSON string value.

@returns
    Created JSON string value.
*/
JsonStrVal::UP createJsonVal(std::string val, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON array value, located at \bt_p{loc},
    containing the JSON values \bt_p{vals}.

@param[in] vals
    Contained JSON values of the created JSON array value.
@param[in] loc
    Text location of the created JSON array value.

@returns
    Created JSON array value.
*/
JsonArrayVal::UP createJsonVal(JsonArrayVal::Container&& vals, TextLoc loc);

/*!
@brief
    Creates and returns a new JSON object value, located at \bt_p{loc},
    containing the JSON values \bt_p{vals}.

@param[in] vals
    Contained JSON values of the created JSON object value.
@param[in] loc
    Text location of the created JSON object value.

@returns
    Created JSON object value.
*/
JsonObjVal::UP createJsonVal(JsonObjVal::Container&& vals, TextLoc loc);

/*!
@}
*/

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_JSON_VAL_HPP */
