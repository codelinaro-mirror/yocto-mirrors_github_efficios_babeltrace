/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_PROXY_HPP
#define BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_PROXY_HPP

namespace bt2 {

/*!
@brief
    Wrapper proxy.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/borrowed-object-proxy.hpp"
@endcode

A proxy containing a valid wrapper instance of \bt_p{ObjT} to
make <code>Something::operator-&gt;()</code> work when only a
libbabeltrace2 object pointer is available.

@tparam ObjT
    Type of contained wrapper.
*/
template <typename ObjT>
class BorrowedObjectProxy final
{
public:
    /*!
    @brief
        Builds a wrapper proxy containing a wrapper of \bt_p{libObjPtr}.

    @param[in] libObjPtr
        Raw libbabeltrace2 object pointer to be wrapped by the
        contained wrapper.

    @bt_pre_not_null{libObjPtr}
    */
    explicit BorrowedObjectProxy(typename ObjT::LibObjPtr libObjPtr) noexcept
        : _mObj {libObjPtr}
    {
    }

    /*!
    @brief
        Returns the contained wrapper.

    @returns
        Contained wrapper.
    */
    ObjT *operator->() noexcept
    {
        return &_mObj;
    }

    /*!
    @brief
        Returns the contained wrapper.

    @returns
        Contained wrapper.
    */
    const ObjT *operator->() const noexcept
    {
        return &_mObj;
    }

private:
    ObjT _mObj;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_PROXY_HPP */
