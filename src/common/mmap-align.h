/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2010 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#ifndef BABELTRACE_COMMON_MMAP_ALIGN_H
#define BABELTRACE_COMMON_MMAP_ALIGN_H

/*!
@file

@brief
    Aligned memory map API.

@ingroup common-c

@code{.c}
#include "common/mmap-align.h"
@endcode

This file offers wrappers of compat/mman.h to create memory maps of file
regions of which the offsets aren't necessarily multiples of the system
page size.

Call mmap_align(), instead of bt_mmap(), to create an aligned memory
map. This function returns the address of an allocated structure,
instead of the typical mapped address, which contains the actual mapped,
page-aligned address and a pointer to the requested offset within said
page.

Remove an aligned memory map with munmap_align().
*/

#include "common/align.h"
#include <stdlib.h>
#include <stdint.h>
#include "compat/mman.h"
#include "common/common.h"

/*!
@brief
    Return type of mmap_align().

As a user, you're interested in mmap_align_data::addr and
mmap_align_data::length.
*/
struct mmap_align_data {
	void *page_aligned_addr;	/* mmap address, aligned to floor */
	size_t page_aligned_length;	/* mmap length, containing range */

	/*!
	@brief
	    Virtual memory map address.

	<code>*addr</code> is the byte at the offset \bt_p{offset}
	when you called mmap_align() which returned this structure.
	*/
	void *addr;

	/*!
	@brief
	    Virtual memory map length (bytes).

	\bt_p{length} parameter when you called mmap_align() which
	returned this structure.
	*/
	size_t length;
};

static inline
off_t get_page_aligned_offset(off_t offset, int log_level)
{
       return BT_ALIGN_FLOOR(offset, bt_mmap_get_offset_align_size(log_level));
}

/*!
@brief
    Like bt_mmap(), but \bt_p{offset} doesn't need to be aligned to
    the system page size.

@param[in] length
    See bt_mmap().
@param[in] prot
    See bt_mmap().
@param[in] flags
    See bt_mmap().
@param[in] fd
    See bt_mmap().
@param[in] offset
    Offset within \bt_p{fd} which doesn't need to be aligned to
    the system page size.
@param[in] log_level
    Log level to use.

@returns
    @parblock
    An allocated #mmap_align_data structure containing the virtual
    address and length (a copy of \bt_p{length}) you're interested in
    on success, or the value \c MAP_FAILED on failure.

    Remove an aligned memory map with munmap_align().
    @endparblock
*/
static inline
struct mmap_align_data *mmap_align(size_t length, int prot,
		int flags, int fd, off_t offset, int log_level)
{
	struct mmap_align_data *mma;
	off_t page_aligned_offset;	/* mmap offset, aligned to floor */
	size_t page_size;

	page_size = bt_common_get_page_size(log_level);

	mma = (struct mmap_align_data *) malloc(sizeof(*mma));
	if (!mma)
		return (struct mmap_align_data *) MAP_FAILED;
	mma->length = length;
	page_aligned_offset = get_page_aligned_offset(offset, log_level);
	/*
	 * Page aligned length needs to contain the requested range.
	 * E.g., for a small range that fits within a single page, we might
	 * require a 2 pages page_aligned_length if the range crosses a page
	 * boundary.
	 */
	mma->page_aligned_length = BT_ALIGN(length + offset - page_aligned_offset, page_size);
	mma->page_aligned_addr = bt_mmap(mma->page_aligned_length,
		prot, flags, fd, page_aligned_offset, log_level);
	if (mma->page_aligned_addr == MAP_FAILED) {
		free(mma);
		return (struct mmap_align_data *) MAP_FAILED;
	}
	mma->addr = ((uint8_t *) mma->page_aligned_addr) + (offset - page_aligned_offset);
	return mma;
}

/*!
@brief
    Removes the aligned memory map \bt_p{mma}, as returned by
    mmap_align(), and deallocates it.

@param[in] mma
    Aligned memory map to remove and deallocate.

@returns
    See bt_munmap().

@bt_pre_not_null{mma}
*/
static inline
int munmap_align(struct mmap_align_data *mma)
{
	void *page_aligned_addr;
	size_t page_aligned_length;

	page_aligned_addr = mma->page_aligned_addr;
	page_aligned_length = mma->page_aligned_length;
	free(mma);
	return bt_munmap(page_aligned_addr, page_aligned_length);
}

static inline
void *mmap_align_addr(struct mmap_align_data *mma)
{
	return mma->addr;
}

#endif /* BABELTRACE_COMMON_MMAP_ALIGN_H */
