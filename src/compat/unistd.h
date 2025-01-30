/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2016 Michael Jeanson <mjeanson@efficios.com>
 */

#ifndef BABELTRACE_COMPAT_UNISTD_H
#define BABELTRACE_COMPAT_UNISTD_H

/*!
@file

@brief
    Wrappers of <code>&lt;%unistd.h&gt;</code> (POSIX).

@ingroup compat

@code{.c}
#include "compat/unistd.h"
@endcode

See \bt_ext_man{unistd.h,0,0p}.
*/

#include <unistd.h>

#ifdef __MINGW32__
#include <windows.h>
#include <errno.h>

#define _SC_PAGESIZE 30

static inline
long bt_sysconf(int name)
{
	SYSTEM_INFO si;

	switch(name) {
	case _SC_PAGESIZE:
		GetNativeSystemInfo(&si);
		return si.dwPageSize;
	default:
		errno = EINVAL;
		return -1;
	}
}

#else

/*!
@brief
    Wrapper of <code>sysconf()</code>.

See \bt_ext_man{sysconf,3,3}.

@param[in] name
    See \bt_ext_man{sysconf,3,3}.

@returns
    See \bt_ext_man{sysconf,3,3}.
*/
static inline
long bt_sysconf(int name)
{
	return sysconf(name);
}

#endif

#endif /* BABELTRACE_COMPAT_UNISTD_H */
