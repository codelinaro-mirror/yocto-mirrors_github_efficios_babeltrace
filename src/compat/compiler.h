/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2010 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#ifndef BABELTRACE_COMPAT_COMPILER_H
#define BABELTRACE_COMPAT_COMPILER_H

/*!
@file

@brief
    Compiler specifics (compatibility layer).

@ingroup compat

@code{.c}
#include "compat/compiler.h"
@endcode
*/

#include <stddef.h>	/* for offsetof */

/*!
@brief
    Returns the pointer to the parent structure of type \bt_p{type}
    from the pointer \bt_p{ptr} to its member named \bt_p{member}.
*/
#ifndef container_of
#define container_of(ptr, type, member)					\
	({								\
		const __typeof__(((type *)NULL)->member) * __ptr = (ptr);	\
		(type *)((char *)__ptr - offsetof(type, member));	\
	})
#endif

#endif /* BABELTRACE_COMPAT_COMPILER_H */
