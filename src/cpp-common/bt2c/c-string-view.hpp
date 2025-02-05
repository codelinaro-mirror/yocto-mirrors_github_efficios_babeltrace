/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_C_STRING_VIEW_HPP
#define BABELTRACE_CPP_COMMON_BT2C_C_STRING_VIEW_HPP

/*!
@file

@brief
    C string view class and related functions.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/c-string-view.hpp"
@endcode

This file mainly offers the bt2c::CStringView class as well as related
functions like bt2c::format_as(const bt2c::CStringView&)
and equalOrBothNull().
*/

#include <cstddef>
#include <cstring>
#include <string>

#include "common/assert.h"
#include "cpp-common/bt2s/optional.hpp"
#include "cpp-common/bt2s/string-view.hpp"
#include "cpp-common/vendor/fmt/format.h" /* IWYU pragma: keep */

#include "type-traits.hpp"

namespace bt2c {

/*!
@brief
    C string view.

A C string view is a view of a constant null-terminated C&nbsp;string.

This is similar to bt2s::string_view, but since we know it's
null-terminated, len() and end() compute the string length on demand.

A C string view is a zero-cost way to receive and return a C&nbsp;string
while having access to common string methods as well as implicit
conversion to and from <code>const char *</code>, \c std::string, and
bt2s::string_view.

Like <code>const char *</code>, a C string view may be empty (contain
\c nullptr).

A CStringView instance is lightweight: it only contains a pointer. Pass
and return by copy.
*/
class CStringView final
{
public:
    /*!
    @brief
        Builds an empty view (data() returns \c nullptr).
    */
    constexpr CStringView() noexcept = default;

    /*!
    @brief
        Builds a view of the C string \bt_p{str}.

    Intentionally not explicit.

    @param[in] str
        @parblock
        C string to view.

        Can be \c nullptr.
        @endparblock
    */
    constexpr CStringView(const char * const str) noexcept : _mStr {str}
    {
    }

    /*!
    @brief
        Builds a view of the C string of \bt_p{str}.

    Intentionally not explicit.

    The created C string view is valid as long as \bt_p{str} isn't
    modified.

    @param[in] str
        String containing the C&nbsp;string to view.
    */
    CStringView(const std::string& str) noexcept : _mStr {str.c_str()}
    {
    }

    /*!
    @brief
        Builds a view of the C string of \bt_p{*str}, or of \c nullptr
        if \bt_p{str} doesn't have a value.

    Intentionally not explicit.

    The created C string view is valid as long as \bt_p{*str} isn't
    modified.

    @param[in] str
        If it has a value, \bt_p{*str} is the string containing the
        C&nbsp;string to view.
    */
    CStringView(const bt2s::optional<std::string>& str) noexcept :
        _mStr {str ? str->c_str() : nullptr}
    {
    }

    /*!
    @brief
        View the C string \bt_p{str}.

    @param[in] str
        @parblock
        C string to view.

        Can be \c nullptr.
        @endparblock

    @returns
        <code>*this</code>
    */
    CStringView& operator=(const char * const str) noexcept
    {
        _mStr = str;
        return *this;
    }

    /*!
    @brief
        Viewed null-terminated C string.

    @returns
        Viewed null-terminated C string, or \c nullptr if none.
    */
    const char *data() const noexcept
    {
        return _mStr;
    }

    /*!
    @brief
        Alias of data().

    @returns
        See data().
    */
    operator const char *() const noexcept
    {
        return this->data();
    }

    /*!
    @brief
        Alias of data().

    @returns
        See data().
    */
    const char *operator*() const noexcept
    {
        return this->data();
    }

    /*!
    @brief
        Alias of data().

    @returns
        See data().

    @pre
        data() doesn't return \c nullptr.
    */
    const char *begin() const noexcept
    {
        BT_ASSERT_DBG(_mStr);
        return this->data();
    }

    /*!
    @brief
        Pointer to the null character of the viewed C string.

    @returns
        Pointer to the null character of the viewed C string.

    @pre
        data() doesn't return \c nullptr.
    */
    const char *end() const noexcept
    {
        BT_ASSERT_DBG(_mStr);
        return _mStr + this->len();
    }

    /*!
    @brief
        Length of the viewed C string, excluding the null character.

    @returns
        Length of the viewed C string, excluding the null character.

    @pre
        data() doesn't return \c nullptr.
    */
    std::size_t len() const noexcept
    {
        BT_ASSERT_DBG(_mStr);
        return std::strlen(_mStr);
    }

    /*!
    @brief
        \c std::string instance containing a copy of the viewed
        C&nbsp;string.

    @returns
        \c std::string instance containing a copy of the viewed
        C&nbsp;string.

    @pre
        data() doesn't return \c nullptr.
    */
    std::string str() const
    {
        BT_ASSERT_DBG(_mStr);
        return std::string {_mStr};
    }

    /*!
    @brief
        Alias of str().

    @returns
        See str().
    */
    operator std::string() const
    {
        return this->str();
    }

    /*!
    @brief
        bt2s::string_view instance viewing the contents,
        excluding the null character, of the viewed C&nbsp;string

    @returns
        bt2s::string_view instance viewing the contents,
        excluding the null character, of the viewed C&nbsp;string
    */
    bt2s::string_view strView() const noexcept
    {
        if (_mStr) {
            return bt2s::string_view {this->begin(), this->len()};
        } else {
            return {};
        }
    }

    /*!
    @brief
        Alias of strView().

    @returns
        See strView().
    */
    operator bt2s::string_view() const noexcept
    {
        return this->strView();
    }

    /*!
    @brief
        Character of the viewed C&nbsp;string at index \bt_p{i}.

    @param[in] i
        Index of the character to get.

    @returns
        Character of the viewed C&nbsp;string at index \bt_p{i}.

    @pre
        - data() doesn't return \c nullptr.
        - \bt_p{i}&nbsp;&lt;&nbsp;len().
    */
    char operator[](const std::size_t i) const noexcept
    {
        BT_ASSERT_DBG(_mStr);
        BT_ASSERT_DBG(i < this->len());
        return _mStr[i];
    }

    /*!
    @brief
        Returns whether or not the viewed C&nbsp;string starts with
        the substring \bt_p{prefix}.

    @param[in] prefix
        Prefix to check.

    @retval false
        The viewed C string doesn't start with \bt_p{prefix}.
    @retval true
        The viewed C string starts with \bt_p{prefix}.

    @pre
        - data() doesn't return \c nullptr.
        - <code>prefix.data()</code> doesn't return \c nullptr.
    */
    bool startsWith(const CStringView prefix) const noexcept
    {
        BT_ASSERT_DBG(_mStr);
        BT_ASSERT_DBG(prefix);
        return std::strncmp(_mStr, prefix, prefix.len()) == 0;
    }

private:
    const char *_mStr = nullptr;
};

/*!
@brief
    {fmt} formatter for CStringView (handles \c nullptr).

@param[in] str
    C string view to format.

@returns
    Formatted \bt_p{str}.
*/
inline const char *format_as(const CStringView& str)
{
    return str ? *str : "(null)";
}

namespace internal {

template <typename StrT>
const char *asConstCharPtr(StrT&& val) noexcept
{
    return val.data();
}

inline const char *asConstCharPtr(const char * const val) noexcept
{
    return val;
}

template <typename StrT>
using ComparableWithCStringView =
    IsOneOf<typename std::decay<StrT>::type, CStringView, std::string, const char *>;

} /* namespace internal */

/*!
@brief
    Returns whether or not \bt_p{lhs} is equal to \bt_p{rhs}.

\bt_p{LhsT} and \bt_p{RhsT} may be any of:

- <code>const char *</code>
- \c std::string
- bt2c::CStringView

@param[in] lhs
    First string to compare.
@param[in] rhs
    Second string to compare.

@retval false
    \bt_p{lhs} and \bt_p{rhs} aren't equal.
@retval true
    \bt_p{lhs} and \bt_p{rhs} are equal.

@pre
    - If \bt_p{LhsT} is <code>const char *</code> or bt2c::CStringView,
      then \bt_p{lhs} does \em not contain \c nullptr.
    - If \bt_p{RhsT} is <code>const char *</code> or bt2c::CStringView,
      then \bt_p{rhs} does \em not contain \c nullptr.
*/
template <
    typename LhsT, typename RhsT,
    typename = typename std::enable_if<internal::ComparableWithCStringView<LhsT>::value>::type,
    typename = typename std::enable_if<internal::ComparableWithCStringView<RhsT>::value>::type>
bool operator==(LhsT&& lhs, RhsT&& rhs) noexcept
{
    const auto rawLhs = internal::asConstCharPtr(lhs);
    const auto rawRhs = internal::asConstCharPtr(rhs);

    BT_ASSERT_DBG(rawLhs);
    BT_ASSERT_DBG(rawRhs);
    return std::strcmp(rawLhs, rawRhs) == 0;
}

/*!
@brief
    Returns whether or not \bt_p{lhs} is \em not equal to \bt_p{rhs}.

\bt_p{LhsT} and \bt_p{RhsT} may be any of:

- <code>const char *</code>
- \c std::string
- bt2c::CStringView

@param[in] lhs
    First string to compare.
@param[in] rhs
    Second string to compare.

@retval false
    \bt_p{lhs} and \bt_p{rhs} are equal.
@retval true
    \bt_p{lhs} and \bt_p{rhs} aren't equal.

@pre
    - If \bt_p{LhsT} is <code>const char *</code> or bt2c::CStringView,
      then \bt_p{lhs} does \em not contain \c nullptr.
    - If \bt_p{RhsT} is <code>const char *</code> or bt2c::CStringView
      then \bt_p{rhs} does \em not contain \c nullptr.
*/
template <
    typename LhsT, typename RhsT,
    typename = typename std::enable_if<internal::ComparableWithCStringView<LhsT>::value>::type,
    typename = typename std::enable_if<internal::ComparableWithCStringView<RhsT>::value>::type>
bool operator!=(LhsT&& lhs, RhsT&& rhs) noexcept
{
    return !(std::forward<LhsT>(lhs) == std::forward<RhsT>(rhs));
}

} /* namespace bt2c */

/*!
@brief
    Appends \bt_p{rhs} to \bt_p{lhs}.

@param[in] lhs
    Base string.
@param[in] rhs
    String to append to \bt_p{lhs}.

@pre
    <code>rhs.data()</code> doesn't return \c nullptr.
*/
inline void operator+=(std::string& lhs, bt2c::CStringView rhs)
{
    lhs += rhs.data();
}

/*!
@brief
    Returns whether or not two C string views are equal or both
    contain \c nullptr.

@param[in] a
    First C string view.
@param[in] b
    Second C string view.

@returns
    @parblock
    \c true if one of:

    - \bt_p{a} and \bt_p{b} are both non-<code>nullptr</code> and equal.
    - \bt_p{a} and \bt_p{b} are both <code>nullptr</code>.
    @endparblock
*/
inline bool equalOrBothNull(const bt2c::CStringView a, const bt2c::CStringView b)
{
    if (a && b) {
        return a == b;
    } else {
        return static_cast<bool>(a) == static_cast<bool>(b);
    }
}

#endif /* BABELTRACE_CPP_COMMON_BT2C_C_STRING_VIEW_HPP */
