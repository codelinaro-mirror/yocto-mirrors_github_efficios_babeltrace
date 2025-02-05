/*
 * Copyright (c) 2015-2024 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_STR_SCANNER_HPP
#define BABELTRACE_CPP_COMMON_BT2C_STR_SCANNER_HPP

#include <cstdlib>
#include <limits>
#include <string>

#include "common/assert.h"
#include "cpp-common/bt2c/logging.hpp"
#include "cpp-common/bt2c/regex.hpp"
#include "cpp-common/bt2s/string-view.hpp"

#include "text-loc.hpp"

namespace bt2c {

/*!
@brief
    String scanner.

@ingroup common-cpp-bt2c

A string scanner (lexer) wraps an input string view and scans specific
characters and sequences of characters, managing a current position.

When you call the various <code>tryScan*()</code> methods to try to scan
some contents, the methods advance the current position on success. They
also automatically skip initial whitespaces.

The supported constructs are:

<table>
  <tr>
    <th>Construct
    <th>Scanning method
  <tr>
    <td>Double-quoted literal string with custom escape sequences
    <td>tryScanLitStr()
  <tr>
    <td>Constant integer (templated for the signedness)
    <td>tryScanConstInt()
  <tr>
    <td>Constant unsigned decimal integer (up to 18,446,744,073,709,551,615)
    <td>tryScanConstUInt()
  <tr>
    <td>
      Constant signed decimal integer (-9,223,372,036,854,775,808 to
      9,223,372,036,854,775,807)
    <td>tryScanConstSInt()
  <tr>
    <td>
      <a href="https://www.json.org/">JSON</a> number \em with a
      fraction or exponent part
    <td>tryScanConstReal()
  <tr>
    <td>Exact string
    <td>tryScanToken()
  <tr>
    <td>Whitespaces
    <td>skipWhitespaces()
</table>

@note
    You must use this class in libbabeltrace2 context because it
    appends causes to the error of the current thread and throws
    on error.

@code{.cpp}
#include "cpp-common/bt2c/str-scanner.hpp"
@endcode
*/
class StrScanner final
{
public:
    /*! @brief String view iterator. */
    using Iter = bt2s::string_view::const_iterator;

    /*!
    @brief
        Builds a string scanner, wrapping the string \bt_p{str}.

    When the created string scanner logs or appends a cause to the
    error of the current thread, it uses \bt_p{baseOffset} to format
    the \link TextLoc text location\endlink part of the error message.

    The created string scanner remains valid as long as \bt_p{str}
    isn't modified.

    @param[in] str
        String to wrap.
    @param[in] baseOffset
        Base offset to use to format a text location for an
        error message.
    @param[in] logger
        Logger to use on error.
    */
    explicit StrScanner(bt2s::string_view str, std::size_t baseOffset, const Logger& logger);

    /*!
    @brief
        Like StrScanner(bt2s::string_view, std::size_t, const Logger&),
        but with \bt_p{baseOffset} set to&nbsp;0.

    @param[in] str
        See StrScanner(bt2s::string_view, std::size_t, const Logger&).
    @param[in] logger
        See StrScanner(bt2s::string_view, std::size_t, const Logger&).
    */
    explicit StrScanner(bt2s::string_view str, const Logger& logger);

    /*!
    @brief
        Current position within the wrapped string.

    @returns
        Current position within the wrapped string.
    */
    Iter at() const noexcept
    {
        return _mAt;
    }

    /*!
    @brief
        Sets the current position within the wrapped string
        to \bt_p{at}.

    @warning
        This may corrupt the current text location (loc()) if the
        string between at() and \bt_p{at} includes one or more
        newline characters.

    @param[in] at
        New position.
    */
    void at(const Iter at) noexcept
    {
        BT_ASSERT_DBG(at >= _mStr.begin() && at <= _mStr.end());
        _mAt = at;
    }

    /*!
    @brief
        Wrapped string.

    @returns
        Wrapped string.
    */
    bt2s::string_view str() const noexcept
    {
        return _mStr;
    }

    /*!
    @brief
        Number of characters left until <code>str().end()</code>.

    @returns
        Number of characters left until <code>str().end()</code>.
    */
    std::size_t charsLeft() const noexcept
    {
        return _mStr.end() - _mAt;
    }

    /*
     * Returns the current text location considering `_mBaseOffset`.
     */

    /*!
    @brief
        Current text location.

    This method uses the value of the \bt_p{baseOffset} parameter of
    StrScanner(bt2s::string_view, std::size_t, const Logger&)
    when you built this string scanner as the base offset of the
    text location to build.

    @returns
        Current text location.
    */
    TextLoc loc() const noexcept
    {
        return TextLoc {_mBaseOffset + static_cast<std::size_t>(_mAt - _mStr.begin()), _mNbLines,
                        static_cast<std::size_t>(_mAt - _mLineBegin)};
    }

    /*!
    @brief
        Whether or not the end of the wrapped string is reached.

    @returns
        \c true if the end of the wrapped string is reached.
    */
    bool isDone() const noexcept
    {
        return _mAt == _mStr.end();
    }

    /*!
    @brief
        Resets this string scanner, setting the current position
        to <code>str().begin()</code>.
    */
    void reset();

    /*!
    @brief
        Tries to scan a double-quoted literal string, considering the
        characters of \bt_p{escapeSeqStartList}, <code>\\</code>,
        and <code>&quot;</code> as escape sequence starting characters.

    If \bt_p{escapeSeqStartList} includes \c u, then a <code>\\u</code>
    escape sequence is interpreted as in
    <a href="https://www.json.org/">JSON</a>: four hexadecimal
    characters which represent the value of a single Unicode codepoint.

    Valid examples:

    - <code>&quot;salut!&quot;</code>
    - <code>&quot;en circulation\\nYves?&quot;</code>
    - <code>&quot;\\u03c9 often represents angular velocity in physics&quot;</code>

    Calls skipWhitespaces() before scanning.

    Sets the current position to \em after the closing double
    quote on success.

    Logs and appends a cause to the error of the current thread,
    throwing bt2c::Error, if the scanning method finds an invalid escape
    sequence or an illegal control character.

    @param[in] escapeSeqStartList
        List of characters to consider as escape sequence
        starting characters.

    @returns
        @parblock
        View of the escaped string, \em without beginning/end
        double quotes, on success, or an empty view if there's no
        double-quoted literal string (or if the method reaches
        <code>str().end()</code> before a closing <code>&quot;</code>).

        The returned string view remains valid as long as you don't call
        any method of this string scanner.
        @endparblock

    @pre
        \bt_p{escapeSeqStartList} only contains characters amongst
        \c a, \c b, \c f, \c n, \c r, \c t, \c u, and \c v.
    */
    bt2s::string_view tryScanLitStr(bt2s::string_view escapeSeqStartList);

    /*!
    @brief
        Tries to scan and decode a constant integer string, possibly
        negative if \bt_p{ValT} (either <code>unsigned long long</code>
        or <code>long long</code>) is signed.

    Valid examples:

    - <code>9283</code>
    - <code>-42</code>
    - <code>0</code>

    Calls skipWhitespaces() before scanning.

    Sets the current position to \em after this constant integer string
    on success.

    @returns
        Decoded constant integer on success, or bt2s::nullopt
        if the method couldn't scan a constant integer.

    @sa tryScanConstUInt()
    @sa tryScanConstSInt()
    */
    template <typename ValT>
    bt2s::optional<ValT> tryScanConstInt() noexcept;

    /*!
    @brief
        Alias of tryScanConstInt() with <code>unsigned long long</code>.

    @returns
        See tryScanConstInt().

    @sa tryScanConstSInt()
    */
    bt2s::optional<unsigned long long> tryScanConstUInt() noexcept
    {
        return this->tryScanConstInt<unsigned long long>();
    }

    /*!
    @brief
        Alias of tryScanConstInt() with <code>long long</code>.

    @returns
        See tryScanConstInt().

    @sa tryScanConstUInt()
    */
    bt2s::optional<long long> tryScanConstSInt() noexcept
    {
        return this->tryScanConstInt<long long>();
    }

    /*!
    @brief
        Tries to scan and decode a constant real number string,
        returning bt2s::nullopt if not possible.

    The format of the real number string to scan is the
    <a href="https://www.json.org/">JSON</a> number one, \em with
    a fraction or an exponent part. Without a fraction/exponent part,
    this method returns bt2s::nullopt: use tryScanConstInt() to
    try scanning a constant integer instead.

    Valid examples:

    - <code>17.2</code>
    - <code>-42.192</code>
    - <code>8e9</code>
    - <code>17E12</code>
    - <code>9.14e+6</code>
    - <code>-13.2777E-4</code>
    - <code>0.0</code>
    - <code>-0.0</code>

    Calls skipWhitespaces() before scanning.

    Sets the current position to \em after this constant real number
    string on success.

    @returns
        Decoded constant real number on success, or bt2s::nullopt
        if the method couldn't scan a constant real number.
    */
    bt2s::optional<double> tryScanConstReal() noexcept;

    /*!
    @brief
        Tries to scan the exact string \bt_p{token}.

    Calls skipWhitespaces() before scanning.

    Sets the current position to \em after the token
    on success.

    @param[in] token
        Token to scan.

    @retval false
        Couldn't scan \bt_p{token}.
    @retval true
        Scanned \bt_p{token}.
    */
    bool tryScanToken(bt2s::string_view token) noexcept;

    /*!
    @brief
        Skips all the following whitespaces, updating the
        current position.
    */
    void skipWhitespaces() noexcept;

private:
    /*
     * Tries to negate `ullVal` as a signed integer value if `ValT` is
     * signed and `negate` is true, returning `bt2s::nullopt` if it
     * can't.
     *
     * Always succeeds when `ValT` is unsigned.
     */
    template <typename ValT>
    static bt2s::optional<ValT> _tryNegateConstInt(unsigned long long ullVal, bool negate) noexcept;

    /*
     * Handles a `\u` escape sequence, appending the UTF-8-encoded
     * Unicode character to `_mStrBuf` on success, or throwing `Error`
     * on error.
     *
     * `at` is the position of the first hexadecimal character
     * after `\u`.
     */
    void _appendEscapedUnicodeChar(Iter at);

    /*
     * Tries to append an escaped character to `_mStrBuf` from the
     * escape sequence characters at the current positin, considering
     * the characters of `escapeSeqStartList`, `\`, and `"` as escape
     * sequence starting characters.
     */
    bool _tryAppendEscapedChar(bt2s::string_view escapeSeqStartList);

    /*
     * Tries to scan any character, returning it and advancing the
     * current position on success, or returning -1 if the current
     * position is `str().end()`.
     */
    int _tryScanAnyChar() noexcept
    {
        if (this->isDone()) {
            return -1;
        }

        const auto c = *_mAt;

        this->_incrAt();
        return c;
    }

    /*
     * Checks if the character at the current position is a newline,
     * updating the line count and line beginning position if so.
     */
    void _checkNewline() noexcept
    {
        if (*_mAt == '\n') {
            ++_mNbLines;
            _mLineBegin = _mAt + 1;
        }
    }

    /*
     * Increments `_mAt` by `count`.
     */
    void _incrAt(const std::size_t count = 1) noexcept
    {
        _mAt += count;
        BT_ASSERT_DBG(_mAt <= _mStr.end());
    }

    /*
     * Decrements `_mAt` by `count`.
     */
    void _decrAt(const std::size_t count = 1) noexcept
    {
        _mAt -= count;
        BT_ASSERT_DBG(_mAt >= _mStr.begin());
    }

private:
    /* Viewed string, given by user */
    bt2s::string_view _mStr;

    /* Current position within `_mStr` */
    Iter _mAt;

    /* Beginning of the current line */
    Iter _mLineBegin;

    /* Number of lines scanned so far */
    std::size_t _mNbLines = 0;

    /* String buffer, used by tryScanToken() and tryScanLitStr() */
    std::string _mStrBuf;

    /* Real number string regex */
    static const bt2c::Regex _realRegex;

    /* Base offset for error messages */
    std::size_t _mBaseOffset;

    /* Logging configuration */
    Logger _mLogger;
};

template <typename ValT>
bt2s::optional<ValT> StrScanner::_tryNegateConstInt(const unsigned long long ullVal,
                                                    const bool negate) noexcept
{
    /* Check for overflow */
    if (std::is_signed<ValT>::value) {
        constexpr auto llMaxAsUll =
            static_cast<unsigned long long>(std::numeric_limits<long long>::max());

        if (negate) {
            if (ullVal > llMaxAsUll + 1) {
                return bt2s::nullopt;
            }
        } else {
            if (ullVal > llMaxAsUll) {
                return bt2s::nullopt;
            }
        }
    }

    /* Success: cast and negate if needed */
    auto val = static_cast<ValT>(ullVal);

    if (negate) {
        val *= static_cast<ValT>(-1);
    }

    return val;
}

template <typename ValT>
bt2s::optional<ValT> StrScanner::tryScanConstInt() noexcept
{
    static_assert(std::is_same<ValT, long long>::value ||
                      std::is_same<ValT, unsigned long long>::value,
                  "`ValT` is `long long` or `unsigned long long`.");

    this->skipWhitespaces();

    /* Backup if we can't scan completely */
    const auto initAt = _mAt;

    /* Scan initial character */
    const auto c = this->_tryScanAnyChar();

    if (c < 0) {
        /* Nothing left */
        return bt2s::nullopt;
    }

    /* Check for negation */
    const bool negate = (c == '-');

    if (negate && !std::is_signed<ValT>::value) {
        /* Can't negate an unsigned integer */
        this->at(initAt);
        return bt2s::nullopt;
    }

    if (!negate) {
        /* No negation: rewind */
        this->_decrAt();
    }

    /*
     * Only allow a digit at this point: std::strtoull() below supports
     * an initial `+`, but this scanner doesn't.
     */
    if (this->isDone() || !std::isdigit(*_mAt)) {
        this->at(initAt);
        return bt2s::nullopt;
    }

    /* Parse */
    char *strEnd = nullptr;
    const auto ullVal = std::strtoull(&(*_mAt), &strEnd, 10);

    if ((ullVal == 0 && &(*_mAt) == strEnd) || errno == ERANGE) {
        /* Couldn't parse */
        errno = 0;
        this->at(initAt);
        return bt2s::nullopt;
    }

    /* Negate if needed */
    const auto val = this->_tryNegateConstInt<ValT>(ullVal, negate);

    if (!val) {
        /* Couldn't negate */
        this->at(initAt);
        return bt2s::nullopt;
    }

    /* Success: update current position and return value */
    this->at(_mStr.begin() + (strEnd - _mStr.data()));
    return val;
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_STR_SCANNER_HPP */
