/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2014 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 */

#ifndef BABELTRACE_COMPAT_LIMITS_H
#define BABELTRACE_COMPAT_LIMITS_H

/*!
@file

@brief
    Common limits (compatibility layer).

@ingroup compat

@code{.c}
#include "compat/limits.h"
@endcode

This file also defines \c PATH_MAX to a sane default on systems missing
this definition.
*/

#include <limits.h>

#ifdef __linux__

#define BABELTRACE_HOST_NAME_MAX HOST_NAME_MAX

#elif defined(__FreeBSD__)

#include <sys/param.h>

#define BABELTRACE_HOST_NAME_MAX MAXHOSTNAMELEN

#elif defined(_POSIX_HOST_NAME_MAX)

#define BABELTRACE_HOST_NAME_MAX _POSIX_HOST_NAME_MAX

#else

/*!
@brief
    Maximum length of a host name.
*/
#define BABELTRACE_HOST_NAME_MAX 256

#endif /* __linux__, __FreeBSD__, _POSIX_HOST_NAME_MAX */

/* GNU Hurd has no PATH_MAX, use a sensible default */
#ifdef __GNU__
#define PATH_MAX 4096
#endif /* __GNU__ */

#endif /* BABELTRACE_COMPAT_LIMITS_H */
