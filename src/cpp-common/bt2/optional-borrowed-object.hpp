/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_OPTIONAL_BORROWED_OBJECT_HPP
#define BABELTRACE_CPP_COMMON_BT2_OPTIONAL_BORROWED_OBJECT_HPP

#include <type_traits>

#include "borrowed-object-proxy.hpp"

namespace bt2 {

/*!
@brief
    Wrapper of optional libbabeltrace2 borrowed object pointer.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/optional-borrowed-object.hpp"
@endcode

An instance of this class template manages an optional contained
borrowed object of type \bt_p{ObjT}, that is, a borrowed object that may
or may not exist.

Such an object considers that a \c nullptr libbabeltrace2 object pointer
means <em>none</em>. Therefore, using an #OptionalBorrowedObject isn't
more costly, in time and space, as using a libbabeltrace2 object pointer
in&nbsp;C, but offers the typical C++ optional interface.

There's no <code>std::nullopt</code> equivalent: just use
OptionalBorrowedObject() or call reset().

There are a constructors an assignment operators which accept an
instance of another wrapper object or of another optional borrowed
object. For those, static assertions make sure that the assignment would
work with borrowed objects, for example:

@code{.cpp}
auto sharedIntVal = bt2::createValue(23L);

bt2::OptionalBorrowedObject<Value> myVal {*sharedIntVal};
@endcode

This is needed because #OptionalBorrowedObject only keeps a
libbabeltrace2 pointer (<code>_mLibObjPtr</code>), therefore it doesn't
automatically know the relation between wrapper classes.

@tparam ObjT
    Type of wrapper to make optional.
*/
template <typename ObjT>
class OptionalBorrowedObject final
{
public:
    /// Wrapper type.
    using Obj = ObjT;

    /// libbabeltrace2 raw object pointer type.
    using LibObjPtr = typename ObjT::LibObjPtr;

    /*!
    @brief
        Builds an optional borrowed object without an object.

    Intentionally not explicit.
    */
    OptionalBorrowedObject() noexcept = default;

    /*!
    @brief
        Builds an optional borrowed object with an instance of
        \bt_p{ObjT} wrapping the libbabeltrace2 pointer
        \bt_p{libObjPtr}.

    Intentionally not explicit.

    @param[in] libObjPtr
        libbabeltrace2 object pointer to wrap.
    */
    OptionalBorrowedObject(const LibObjPtr libObjPtr) noexcept : _mLibObjPtr {libObjPtr}
    {
    }

    /*!
    @brief
        Builds an optional borrowed object with an instance of
        \bt_p{ObjT} constructed from \bt_p{obj}.

    It must be possible to construct an instance of \bt_p{ObjT} with an
    instance of \bt_p{OtherObjT}.

    Intentionally not explicit.

    @param[in] obj
        Other wrapper.
    */
    template <typename OtherObjT>
    OptionalBorrowedObject(const OtherObjT obj) noexcept : _mLibObjPtr {obj.libObjPtr()}
    {
        static_assert(std::is_constructible<ObjT, OtherObjT>::value,
                      "`ObjT` is constructible with an instance of `OtherObjT`.");
    }

    /*!
    @brief
        Builds an optional borrowed object from \bt_p{optObj}, with or
        without an object.

    It must be possible to construct an instance of \bt_p{ObjT} with an
    instance of \bt_p{OtherObjT}.

    Intentionally not explicit.

    @param[in] optObj
        Other optional borrowed object.
    */
    template <typename OtherObjT>
    OptionalBorrowedObject(const OptionalBorrowedObject<OtherObjT> optObj) noexcept :
        _mLibObjPtr {optObj.libObjPtr()}
    {
        static_assert(std::is_constructible<ObjT, OtherObjT>::value,
                      "`ObjT` is constructible with an instance of `OtherObjT`.");
    }

    /*!
    @brief
        Makes this optional borrowed object have an instance of
        \bt_p{ObjT} wrapping the libbabeltrace2 pointer
        \bt_p{libObjPtr}.

    @param[in] libObjPtr
        libbabeltrace2 object pointer to wrap.

    @returns
        This optional borrowed object.
    */
    OptionalBorrowedObject& operator=(const LibObjPtr libObjPtr) noexcept
    {
        _mLibObjPtr = libObjPtr;
        return *this;
    }

    /*!
    @brief
        Makes this optional borrowed object have an instance of
        \bt_p{ObjT} constructed from \bt_p{obj}.

    It must be possible to construct an instance of \bt_p{ObjT} with an
    instance of \bt_p{OtherObjT}.

    @param[in] obj
        Other wrapper.

    @returns
        This optional borrowed object.
    */
    template <typename OtherObjT>
    OptionalBorrowedObject& operator=(const ObjT obj) noexcept
    {
        static_assert(std::is_constructible<ObjT, OtherObjT>::value,
                      "`ObjT` is constructible with an instance of `OtherObjT`.");
        _mLibObjPtr = obj.libObjPtr();
        return *this;
    }

    /*!
    @brief
        Sets this optional borrowed object to \bt_p{optObj}.

    It must be possible to construct an instance of \bt_p{ObjT} with an
    instance of \bt_p{OtherObjT}.

    @param[in] optObj
        Other optional borrowed object.

    @returns
        This optional borrowed object.
    */
    template <typename OtherObjT>
    OptionalBorrowedObject& operator=(const OptionalBorrowedObject<ObjT> optObj) noexcept
    {
        static_assert(std::is_constructible<ObjT, OtherObjT>::value,
                      "`ObjT` is constructible with an instance of `OtherObjT`.");
        _mLibObjPtr = optObj.libObjPtr();
        return *this;
    }

    /*!
    @brief
        Wrapped libbabeltrace2 object pointer
        (may be <code>nullptr</code>).

    @returns
        Wrapped libbabeltrace2 object pointer
        (may be <code>nullptr</code>).
    */
    LibObjPtr libObjPtr() const noexcept
    {
        return _mLibObjPtr;
    }

    /*!
    @brief
        Instance of \bt_p{ObjT} constructed from the wrapped
        libbabeltrace2 object pointer.

    @returns
        Instance of \bt_p{ObjT} constructed from the wrapped
        libbabeltrace2 object pointer.
    */
    ObjT object() const noexcept
    {
        return ObjT {_mLibObjPtr};
    }

    /*!
    @brief
        Alias of object().

    @returns
        See object().
    */
    ObjT operator*() const noexcept
    {
        return this->object();
    }

    /*!
    @brief
        Proxy of an instance of \bt_p{ObjT} constructed from the wrapped
        libbabeltrace2 object pointer.

    @returns
        Proxy of an instance of \bt_p{ObjT} constructed from the wrapped
        libbabeltrace2 object pointer.
    */
    BorrowedObjectProxy<ObjT> operator->() const noexcept
    {
        return BorrowedObjectProxy<ObjT> {_mLibObjPtr};
    }

    /*!
    @brief
        Whether or not this optional borrowed object contains
        a wrapped object.

    @returns
        \c true if this optional borrowed object does \em not contain
        a wrapped object.
    */
    bool hasObject() const noexcept
    {
        return _mLibObjPtr;
    }

    /*!
    @brief
        Alias of hasObject().

    @returns
        See hasObject().
    */
    explicit operator bool() const noexcept
    {
        return this->hasObject();
    }

    /*!
    @brief
        Makes this optional borrowed object empty.
    */
    void reset() noexcept
    {
        _mLibObjPtr = nullptr;
    }

private:
    typename ObjT::LibObjPtr _mLibObjPtr = nullptr;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_OPTIONAL_BORROWED_OBJECT_HPP */
