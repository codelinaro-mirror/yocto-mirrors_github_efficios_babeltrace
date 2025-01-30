/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2012 (c) Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * memstream compatibility layer.
 */

#ifndef BABELTRACE_COMPAT_MEMSTREAM_H
#define BABELTRACE_COMPAT_MEMSTREAM_H

/*!
@file

@brief
    Memory stream functions (compatibility layer).

@ingroup compat

@code{.c}
#include "compat/memstream.h"
@endcode
*/

#ifdef BABELTRACE_HAVE_FMEMOPEN
#include <stdio.h>

static inline
FILE *bt_fmemopen(void *buf, size_t size, const char *mode)
{
	return fmemopen(buf, size, mode);
}

#else /* BABELTRACE_HAVE_FMEMOPEN */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "compat/endian.h"

#ifdef __MINGW32__

#include <io.h>
#include <glib.h>

/*
 * Fallback for systems which don't have fmemopen. Copy buffer to a
 * temporary file, and use that file as FILE * input.
 */
static inline
FILE *bt_fmemopen(void *buf, size_t size, const char *mode)
{
	char *tmpname;
	size_t len;
	FILE *fp;
	int ret;

	/*
	 * Support reading only.
	 */
	if (strcmp(mode, "rb") != 0) {
		return NULL;
	}

	/* Build a temporary filename */
	tmpname = g_build_filename(g_get_tmp_dir(), "babeltrace-tmp-XXXXXX", NULL);
	if (!_mktemp(tmpname)) {
		goto error_free;
	}

	/*
	 * Open as a read/write binary temporary deleted on close file.
	 * Will be deleted when the last file pointer is closed.
	 */
	fp = fopen(tmpname, "w+bTD");
	if (!fp) {
		goto error_free;
	}

	/* Copy the entire buffer to the file */
	len = fwrite(buf, sizeof(char), size, fp);
	if (len != size) {
		goto error_close;
	}

	/* Set the file pointer to the start of file */
	ret = fseek(fp, 0L, SEEK_SET);
	if (ret < 0) {
		perror("fseek");
		goto error_close;
	}

	g_free(tmpname);
	return fp;

error_close:
	ret = fclose(fp);
	if (ret < 0) {
		perror("close");
	}
error_free:
	g_free(tmpname);
	return NULL;
}

#else /* __MINGW32__ */

/*!
@brief
    Wrapper of <code>fmemopen()</code>.

See \bt_ext_man{fmemopen,3,3}.

@param[in] buf
    See \bt_ext_man{fmemopen,3,3}.
@param[in] size
    See \bt_ext_man{fmemopen,3,3}.
@param[in] mode
    See \bt_ext_man{fmemopen,3,3}.

@returns
    See \bt_ext_man{fmemopen,3,3}.
*/
static inline
FILE *bt_fmemopen(void *buf, size_t size, const char *mode)
{
	char *tmpname;
	size_t len;
	FILE *fp;
	int ret;

	/*
	 * Support reading only.
	 */
	if (strcmp(mode, "rb") != 0) {
		return NULL;
	}

	tmpname = g_build_filename(g_get_tmp_dir(), "babeltrace-tmp-XXXXXX", NULL);
	ret = mkstemp(tmpname);
	if (ret < 0) {
		g_free(tmpname);
		return NULL;
	}
	/*
	 * We need to write to the file.
	 */
	fp = fdopen(ret, "wb+");
	if (!fp) {
		goto error_unlink;
	}
	/* Copy the entire buffer to the file */
	len = fwrite(buf, sizeof(char), size, fp);
	if (len != size) {
		goto error_close;
	}
	ret = fseek(fp, 0L, SEEK_SET);
	if (ret < 0) {
		perror("fseek");
		goto error_close;
	}
	/* We keep the handle open, but can unlink the file on the VFS. */
	ret = unlink(tmpname);
	if (ret < 0) {
		perror("unlink");
	}
	g_free(tmpname);
	return fp;

error_close:
	ret = fclose(fp);
	if (ret < 0) {
		perror("close");
	}
error_unlink:
	ret = unlink(tmpname);
	if (ret < 0) {
		perror("unlink");
	}
	g_free(tmpname);
	return NULL;
}

#endif /* __MINGW32__ */

#endif /* BABELTRACE_HAVE_FMEMOPEN */

#endif /* BABELTRACE_COMPAT_MEMSTREAM_H */
