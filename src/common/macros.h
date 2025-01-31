/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2012 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#ifndef BABELTRACE_COMMON_MACROS_H
#define BABELTRACE_COMMON_MACROS_H

/*!
@file

@brief
    Miscellaneous macros and definitions.

@ingroup common-c

@code{.c}
#include "common/macros.h"
@endcode
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define BT_EXTERN_C extern "C"
#else

/*!
@brief
    <code>extern "C"</code> only in C++ mode.
*/
#define BT_EXTERN_C
#endif

/*!
@brief
    Returns the maximum between the values \bt_p{a} and \bt_p{b},
    both casted to \bt_p{type}.
*/
#define bt_max_t(type, a, b)	\
	((type) (a) > (type) (b) ? (type) (a) : (type) (b))

/*
 * BT_EXPORT: set the visibility for exported functions.
 */
#if defined(_WIN32) || defined(__CYGWIN__)
#define BT_EXPORT
#else

/*!
@brief
    Portable symbol exportation.

Example:

@code{.c}
BT_EXPORT
void bt_port_get_ref(const struct bt_port *port)
{
    bt_object_get_ref(port);
}
@endcode
*/
#define BT_EXPORT __attribute__((visibility("default")))
#endif

/*
 * BT_NOEXCEPT: defined to `noexcept` if compiling as C++, else empty.
 */
#if defined(__cplusplus)
#define BT_NOEXCEPT noexcept
#else

/*!
@brief
    \c noexcept only in C++ mode.
*/
#define BT_NOEXCEPT
#endif

/* Enable `txt` if developer mode is enabled. */
#ifdef BT_DEV_MODE
#define BT_IF_DEV_MODE(txt) txt
#else

/*!
@brief
    Expands to \bt_p{txt} in developer mode (when you configured the
    project with <code>BABELTRACE_DEV_MODE=1</code>), or to nothing
    otherwise.
*/
#define BT_IF_DEV_MODE(txt)
#endif

/* Wrapper for g_array_index that adds bound checking.  */
#define bt_g_array_index(a, t, i)		\
	g_array_index((a), t, ({ BT_ASSERT_DBG((i) < (a)->len); (i); }))

/*
 * About BT_USE_EXPR() below:
 *
 * Copied from:
 * <https://stackoverflow.com/questions/37411809/how-to-elegantly-fix-this-unused-variable-warning/37412551#37412551>:
 *
 * * sizeof() ensures that the expression is not evaluated at all, so
 *   its side-effects don't happen. That is to be consistent with the
 *   usual behaviour of debug-only constructs, such as assert().
 *
 * * `((_expr), 0)` uses the comma operator to swallow the actual type
 *   of `(_expr)`. This is to prevent VLAs from triggering evaluation.
 *
 * * `(void)` explicitly ignores the result of `(_expr)` and sizeof() so
 *   no "unused value" warning appears.
 */

/*!
@brief
    "Uses" the expression \bt_p{_expr} so that the compiler doesn't
    complain about unused variables and more.
*/
#define BT_USE_EXPR(_expr)		((void) sizeof((void) (_expr), 0))

/*!
@brief
    "Uses" the expressions \bt_p{_expr1} and \bt_p{_expr2} so that the
    compiler doesn't complain about unused variables and more.
*/
#define BT_USE_EXPR2(_expr1, _expr2)					\
	((void) sizeof((void) (_expr1), (void) (_expr2), 0))

/*!
@brief
    "Uses" the expressions \bt_p{_expr1}, \bt_p{_expr2}, and
    \bt_p{_expr3} so that the compiler doesn't complain about unused
    variables and more.
*/
#define BT_USE_EXPR3(_expr1, _expr2, _expr3)				\
	((void) sizeof((void) (_expr1), (void) (_expr2), (void) (_expr3), 0))

/*!
@brief
    "Uses" the expressions \bt_p{_expr1}, \bt_p{_expr2}, \bt_p{_expr3},
    and \bt_p{_expr4} so that the compiler doesn't complain about unused
    variables and more.
*/
#define BT_USE_EXPR4(_expr1, _expr2, _expr3, _expr4)			\
	((void) sizeof((void) (_expr1), (void) (_expr2),		\
		(void) (_expr3), (void) (_expr4), 0))

/*!
@brief
    "Uses" the expressions \bt_p{_expr1}, \bt_p{_expr2}, \bt_p{_expr3},
    \bt_p{_expr4}, and \bt_p{_expr5} so that the compiler doesn't
    complain about unused variables and more.
*/
#define BT_USE_EXPR5(_expr1, _expr2, _expr3, _expr4, _expr5)		\
	((void) sizeof((void) (_expr1), (void) (_expr2),		\
		(void) (_expr3), (void) (_expr4), (void) (_expr5), 0))

/*!
@brief
    Pushes a compiler diagnostic frame.

You may use #BT_DIAG_IGNORE_SHADOW, #BT_DIAG_IGNORE_NULL_DEREFERENCE,
or #BT_DIAG_IGNORE_UNUSED_BUT_SET_VARIABLE between #BT_DIAG_PUSH
and #BT_DIAG_POP.

Example:

@code{.c}
BT_DIAG_PUSH
BT_DIAG_IGNORE_SHADOW

// some code

BT_DIAG_POP
@endcode

@sa #BT_DIAG_POP
*/
#define BT_DIAG_PUSH _Pragma ("GCC diagnostic push")

/*!
@brief
    Pops a compiler diagnostic frame.

@sa #BT_DIAG_PUSH
*/
#define BT_DIAG_POP _Pragma ("GCC diagnostic pop")

/*!
@brief
    Ignores the <code>-Wshadow</code> compiler warning within the
    current diagnostic frame.

@sa #BT_DIAG_PUSH
@sa #BT_DIAG_POP
*/
#define BT_DIAG_IGNORE_SHADOW _Pragma("GCC diagnostic ignored \"-Wshadow\"")

/*!
@brief
    Ignores the <code>-Wnull-dereference</code> compiler warning within
    the current diagnostic frame.

@sa #BT_DIAG_PUSH
@sa #BT_DIAG_POP
*/
#define BT_DIAG_IGNORE_NULL_DEREFERENCE _Pragma("GCC diagnostic ignored \"-Wnull-dereference\"")

#if defined __clang__
#  if __has_warning("-Wunused-but-set-variable")
#    define BT_DIAG_IGNORE_UNUSED_BUT_SET_VARIABLE \
	_Pragma("GCC diagnostic ignored \"-Wunused-but-set-variable\"")
#  endif
#endif

#if !defined BT_DIAG_IGNORE_UNUSED_BUT_SET_VARIABLE

/*!
@brief
    Ignores the <code>-Wunused-but-set-variable</code> compiler warning,
    if available, within the current diagnostic frame.

@sa #BT_DIAG_PUSH
@sa #BT_DIAG_POP
*/
#  define BT_DIAG_IGNORE_UNUSED_BUT_SET_VARIABLE
#endif

#ifdef __cplusplus
}
#endif

#endif /* BABELTRACE_COMMON_MACROS_H */
