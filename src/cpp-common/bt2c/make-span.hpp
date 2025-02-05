/*
 * Copyright (c) 2024 EfficiOS Inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_MAKE_SPAN_HPP
#define BABELTRACE_CPP_COMMON_BT2C_MAKE_SPAN_HPP

#include "cpp-common/bt2s/span.hpp"

namespace bt2c {

/*!
@brief
    Builds a span from \bt_p{ptr} and \bt_p{count} (utility to help
    with type deduction in C++11).

@ingroup common-cpp-bt2c

This helper exists because C++11 doesn't have
<a href="https://en.cppreference.com/w/cpp/language/class_template_argument_deduction">class
template argument deduction</a>, therefore building a bt2s::span from
constructor needs an explicit template argument:

@code{.cpp}
// Without makeSpan()
const bt2s::span<int> mySpan {ptr, 32};

// With makeSpan()
const auto mySpace = bt2c::makeSpan(ptr, 32);
@endcode

@code{.cpp}
#include "cpp-common/bt2c/make-span.hpp"
@endcode

@param[in] ptr
    See corresponding bt2s::span constructor.
@param[in] count
    See corresponding bt2s::span constructor.

@returns
    Span built from \bt_p{ptr} and \bt_p{count}.

@sa makeSpan(T *, T *)
*/
template <class T>
inline constexpr bt2s::span<T> makeSpan(T * const ptr, const size_t count) noexcept
{
    return nonstd::make_span(ptr, count);
}

/*!
@brief
    Builds a span from \bt_p{first} and \bt_p{last} (utility to help
    with type deduction in C++11).

@ingroup common-cpp-bt2c

This helper exists because C++11 doesn't have
<a href="https://en.cppreference.com/w/cpp/language/class_template_argument_deduction">class
template argument deduction</a>, therefore building a bt2s::span from
constructor needs an explicit template argument:

@code{.cpp}
// Without makeSpan()
const bt2s::span<int> mySpan {begin, end};

// With makeSpan()
const auto mySpace = bt2c::makeSpan(begin, end);
@endcode

@code{.cpp}
#include "cpp-common/bt2c/make-span.hpp"
@endcode

@param[in] first
    See corresponding bt2s::span constructor.
@param[in] last
    See corresponding bt2s::span constructor.

@returns
    Span built from \bt_p{first} and \bt_p{last}.

@sa makeSpan(T * const, size_t)
*/
template <class T>
inline constexpr bt2s::span<T> makeSpan(T *first, T *last) noexcept
{
    return nonstd::make_span(first, last);
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_MAKE_SPAN_HPP */
