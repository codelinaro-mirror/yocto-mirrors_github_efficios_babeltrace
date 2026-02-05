/*
 * Copyright (c) 2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_JOIN_HPP
#define BABELTRACE_CPP_COMMON_BT2C_JOIN_HPP

#include <sstream>
#include <string>
#include <string_view>

namespace bt2c {
namespace internal {

template <typename StrT>
void appendStrToSs(std::ostringstream& ss, const StrT& str)
{
    ss.write(str.data(), str.size());
}

} /* namespace internal */

/*!
@brief
    Joins the strings of \bt_p{container} with the delimiter
    \bt_p{delim} and returns the result.

@ingroup common-cpp-bt2c

Some valid value types of \bt_p{ContainerT} are \c std::string,
CStringView, and `std::string_view`.

Example:

@code{.cpp}
const std::vector<std::string> meow {"allo", "bobo", "rhume", "cerveau"};

std::cout << bt2c::join(meow, ", ") << '\n';
@endcode

prints

@code{.undefined}
allo, bobo, rhume, cerveau
@endcode

@code{.cpp}
#include "cpp-common/bt2c/join.hpp"
@endcode

@param[in] container
    @parblock
    Container of which to join the strings.

    Can be empty.
    @endparblock
@param[in] delim
    Delimiter to join the strings to \bt_p{container}.

@returns
    Strings of \bt_p{container} joined with \bt_p{delim}.

@pre
    - \bt_p{ContainerT} features a forward iterator.
    - \bt_p{ContainerT::value_type} has the \c data() method.
    - \bt_p{ContainerT::value_type} has the \c size() method.
*/
template <typename ContainerT>
std::string join(const ContainerT& container, const std::string_view delim)
{
    if (container.empty()) {
        /* No elements */
        return {};
    }

    if (container.size() == 1) {
        /* Single element */
        return std::string {container.begin()->data(), container.begin()->size()};
    }

    /* Two or more elements */
    std::ostringstream ss;
    auto it = container.begin();

    internal::appendStrToSs(ss, *it);
    ++it;

    for (; it != container.end(); ++it) {
        internal::appendStrToSs(ss, delim);
        internal::appendStrToSs(ss, *it);
    }

    return ss.str();
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_JOIN_HPP */
