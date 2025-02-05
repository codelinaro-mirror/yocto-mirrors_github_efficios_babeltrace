/*
 * SPDX-FileCopyrightText: 2022 Simon Marchi <simon.marchi@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_VECTOR_HPP
#define BABELTRACE_CPP_COMMON_BT2C_VECTOR_HPP

#include <vector>

#include "common/assert.h"

namespace bt2c {

/*!
@brief
    Moves the last element of \bt_p{vec} to the index \bt_p{idx}, and
    then removes the last element.

@ingroup common-cpp-bt2c

This is like
<a href="https://docs.gtk.org/glib/type_func.PtrArray.remove_index_fast.html"><code>GLib.PtrArray.remove_index_fast</code></a>,
but for \c std::vector.

@code{.cpp}
#include "cpp-common/bt2c/vector.hpp"
@endcode

@param[in] vec
    Vector of which to remove the last element.
@param[in] idx
    Index of the element to remove.

@pre
    \bt_p{idx}&nbsp;&lt;&nbsp;<code>vec.size()</code>.
*/
template <typename T, typename AllocatorT>
void vectorFastRemove(std::vector<T, AllocatorT>& vec,
                      const typename std::vector<T, AllocatorT>::size_type idx)
{
    BT_ASSERT_DBG(idx < vec.size());

    if (idx < vec.size() - 1) {
        vec[idx] = std::move(vec.back());
    }

    vec.pop_back();
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_VECTOR_HPP */
