/*
 * Copyright (c) 2024 EfficiOS Inc.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_REGEX_HPP
#define BABELTRACE_CPP_COMMON_BT2C_REGEX_HPP

#include <string_view>

#include <glib.h>

#include "cpp-common/bt2c/logging.hpp"

namespace bt2c {

/*!
@brief
    Regular expression.

@ingroup common-cpp-bt2c

This is a simple regex class of which an instance compiles a single
pattern.

The regex language is currently the one of
<a href="https://docs.gtk.org/glib/struct.Regex.html"><code>GLib.Regex</code></a>
which is similar to
<a href="https://www.pcre.org/">PCRE</a>.

Match a string with match().

@code{.cpp}
#include "cpp-common/bt2c/regex.hpp"
@endcode
*/
class Regex final
{
public:
    /*!
    @brief
        Builds a regex object, compiling the pattern \bt_p{pattern}.

    @param[in] pattern
        %Regex pattern to compile.

    @pre
        \bt_p{pattern} is a valid
        <a href="https://docs.gtk.org/glib/struct.Regex.html"><code>GLib.Regex</code></a>
        regex.
    */
    explicit Regex(const char * const pattern) noexcept
    {
        GError *error = nullptr;

        _mRegex = g_regex_new(pattern, G_REGEX_OPTIMIZE, static_cast<GRegexMatchFlags>(0), &error);

        if (!_mRegex) {
            BT_CPPLOGF_SPEC((bt2c::Logger {"BT2C", "REGEX", bt2c::Logger::Level::Fatal}),
                            "g_regex_new() failed: {}", error->message);
            bt_common_abort();
        }
    }

    Regex(const Regex&) = delete;
    Regex& operator=(const Regex&) = delete;

    ~Regex()
    {
        g_regex_unref(_mRegex);
    }

    /*!
    @brief
        Returns whether or not this regex
        matches \bt_p{str}.

    See
    <a href="https://docs.gtk.org/glib/method.Regex.match_full.html"><code>GLib.Regex.match_full</code></a>.

    @param[in] str
        String to match.

    @retval false
        This regex doesn't match \bt_p{str}.
    @retval true
        This regex matches \bt_p{str}.
    */
    bool match(const std::string_view str) const noexcept
    {
        return g_regex_match_full(_mRegex, str.data(), str.size(), 0,
                                  static_cast<GRegexMatchFlags>(0), nullptr, nullptr);
    }

private:
    GRegex *_mRegex;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_REGEX_HPP */
