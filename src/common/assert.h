/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2018-2019 EfficiOS Inc. and Linux Foundation
 * Copyright (c) 2018-2019 Philippe Proulx <pproulx@efficios.com>
 */

#ifndef BABELTRACE_COMMON_ASSERT_H
#define BABELTRACE_COMMON_ASSERT_H

/*!
@file

@brief
    Assertion macros.

@ingroup common-c

@code{.c}
#include "common/assert.h"
@endcode

Use the assertion macros of this header instead of
\bt_ext_man{assert,3,3}.

The main advantages are:

- The macros don't rely on <code>NDEBUG</code>, therefore we control
  their existence even for a default build (which doesn't define
  <code>NDEBUG</code>).

- There's an always-enabled version (BT_ASSERT()) as well as a
  debug-mode version (BT_ASSERT_DBG()) for fast paths.

- The output of a failed assertion is custom, with terminal colours if
  possible, to be more readable and the failure ends with a call to
  bt_common_abort().
*/

#include <assert.h>
#include <glib.h>

#include "common/macros.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void bt_common_assert_failed(const char *file, int line,
		const char *func, const char *assertion)
		__attribute__((noreturn));

/*!
@brief
    Asserts that the expression \bt_p{_cond} is true, printing the
    expression and calling bt_common_abort() otherwise.

The printed message looks like this:

@code{.undefined}
 (╯°□°)╯︵ ┻━┻  my-file.cpp:2677: myFunction(): Assertion `x < 8` failed.
@endcode

In a terminal, parts of the message are colourized.

This version is always built: use it in slow or occasional code paths.

@sa BT_ASSERT_DBG()
*/
#define BT_ASSERT(_cond)                                                       \
	do {                                                                   \
		if (!(_cond)) {                                                \
			bt_common_assert_failed(__FILE__, __LINE__, __func__,  \
				G_STRINGIFY(_cond));                           \
		}                                                              \
	} while (0)

/*
 * Marks a function as being only used within a BT_ASSERT() context.
 */
#define BT_ASSERT_FUNC

#if (defined(BT_DEBUG_MODE) || defined(BT_DOXY))

/*!
@brief
    Like BT_ASSERT(), but only enabled when you configured the project
    with <code>BABELTRACE_DEBUG_MODE=1</code>.

Use this version in fast or frequent code paths.

@sa #BT_ASSERT_DBG_FUNC
*/
#define BT_ASSERT_DBG(_cond)	BT_ASSERT(_cond)

/*!
@brief
    Marks a function as being only used by a BT_ASSERT_DBG()
    condition.

Example:

@code{.c}
BT_ASSERT_DBG_FUNC
static inline bool check_complex_cond(...)
{
    // ...
}
@endcode

@code{.c}
BT_ASSERT_DBG(check_complex_cond(...));
@endcode
*/
#define BT_ASSERT_DBG_FUNC

#else /* BT_DEBUG_MODE */
# define BT_ASSERT_DBG(_cond)	BT_USE_EXPR(_cond)
# define BT_ASSERT_DBG_FUNC	__attribute__((unused))
#endif /* BT_DEBUG_MODE */

#ifdef __cplusplus
}
#endif

#endif /* BABELTRACE_COMMON_ASSERT_H */
