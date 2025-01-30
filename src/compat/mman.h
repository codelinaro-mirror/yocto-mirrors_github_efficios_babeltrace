/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2015-2016  Michael Jeanson <mjeanson@efficios.com>
 */

#ifndef BABELTRACE_COMPAT_MMAN_H
#define BABELTRACE_COMPAT_MMAN_H

/*!
@file

@brief
    Wrappers of <code>&lt;%sys/mman.h&gt;</code> (POSIX).

@ingroup compat

@code{.c}
#include "compat/mman.h"
@endcode

Defined for Windows:

- \c MAP_ANON
- \c MAP_ANONYMOUS
- \c MAP_FAILED
- \c MAP_FILE
- \c MAP_FIXED
- \c MAP_PRIVATE
- \c MAP_SHARED
- \c MAP_TYPE
- \c PROT_EXEC
- \c PROT_NONE
- \c PROT_READ
- \c PROT_WRITE

See \bt_ext_man{sys_mman.h,0,0p}.

@sa common/mmap-align.h
*/

#ifdef __MINGW32__

#include <sys/types.h>
#include "common/macros.h"

#define PROT_NONE	0x0
#define PROT_READ	0x1
#define PROT_WRITE	0x2
#define PROT_EXEC	0x4

#define MAP_FILE	0
#define MAP_SHARED	1
#define MAP_PRIVATE	2
#define MAP_TYPE	0xF
#define MAP_FIXED	0x10
#define MAP_ANONYMOUS	0x20
#define MAP_ANON	MAP_ANONYMOUS
#define MAP_FAILED	((void *) -1)

/*
 * Note that some platforms (e.g. Windows) do not allow read-only
 * mappings to exceed the file's size (even within a page).
 */
BT_EXTERN_C void *bt_mmap(size_t length, int prot, int flags, int fd,
	off_t offset, int log_level);

BT_EXTERN_C int bt_munmap(void *addr, size_t length);

/*
 * On Windows the memory mapping offset must be aligned to the memory
 * allocator allocation granularity and not the page size.
 */
BT_EXTERN_C size_t bt_mmap_get_offset_align_size(int log_level);

#else /* __MINGW32__ */

#include <sys/mman.h>
#include "common/common.h"

/*!
@brief
    Wrapper of <code>mmap()</code>.

See \bt_ext_man{mmap,3,3p}.

@param[in] length
    See \bt_ext_man{mmap,3,3p}.
@param[in] prot
    See \bt_ext_man{mmap,3,3p}.
@param[in] flags
    See \bt_ext_man{mmap,3,3p}.
@param[in] fd
    See \bt_ext_man{mmap,3,3p}.
@param[in] offset
    See \bt_ext_man{mmap,3,3p}.
@param[in] log_level
    Log level (unused).

@returns
    See \bt_ext_man{mmap,3,3p}.

@sa mmap_align()
*/
static inline
void *bt_mmap(size_t length, int prot, int flags, int fd,
	off_t offset, int log_level __attribute__((unused)))
{
	return (void *) mmap(NULL, length, prot, flags, fd, offset);
}

/*!
@brief
    Wrapper of <code>munmap()</code>.

See \bt_ext_man{munmap,3,3p}.

@param[in] addr
    See \bt_ext_man{munmap,3,3p}.
@param[in] length
    See \bt_ext_man{munmap,3,3p}.

@returns
    See \bt_ext_man{munmap,3,3p}.
*/
static inline
int bt_munmap(void *addr, size_t length)
{
	return munmap(addr, length);
}

/*!
@brief
    Returns the system page size.

@param[in] log_level
    Log level to use.

@returns
    System page size.
*/
static inline
size_t bt_mmap_get_offset_align_size(int log_level)
{
	return bt_common_get_page_size(log_level);
}
#endif /* __MINGW32__ */

#ifndef MAP_ANONYMOUS
# ifdef MAP_ANON
#   define MAP_ANONYMOUS MAP_ANON
# endif
#endif

#endif /* BABELTRACE_COMPAT_MMAN_H */
