/*
 * Copyright (c) 2019-2020 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_SHARED_OBJECT_HPP
#define BABELTRACE_CPP_COMMON_BT2_SHARED_OBJECT_HPP

#include <utility>

#include "optional-borrowed-object.hpp"

namespace bt2 {

/*!
@brief
    Shared version of wrapper of libbabeltrace2 borrowed object pointer.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/shared-object.hpp"
@endcode

An instance of this class wraps an optional instance of \bt_p{ObjT} and
manages the reference counting of the underlying libbabeltrace2 object.

When you move a shared object, it becomes empty, in that operator*() and
operator->() will either fail to assert in debug mode or trigger a
segmentation fault. You may call the reset() method to make a shared
object empty. Check whether or not a shared object is empty with
operator bool().

The public ways to build a shared object are:

<dl>
  <dt>SharedObject()
  <dd>Builds an empty shared object.

  <dt>createWithoutRef()
  <dd>Builds a shared object without getting an initial reference.

  <dt>createWithRef()
  <dd>Builds a shared object, getting an initial reference.
</dl>

@tparam ObjT
    Wrapper type.
@tparam LibObjT
    libbabeltrace2 object type, for example
    \c bt_stream_class or <code>const bt_value</code>.
@tparam RefFuncsT
    @parblock
    Reference counting functions.

    This must be a structure with the following static methods:

    <dl>
      <dt><code>static void get(const LibObjT *libObjPtr) noexcept</code>
      <dd>Increment the reference count of \bt_p{libObjPtr}.

      <dt><code>static void put(const LibObjT *libObjPtr) noexcept</code>
      <dd>Decrement the reference count of \bt_p{libObjPtr}.
    </dl>
    @endparblock
*/
template <typename ObjT, typename LibObjT, typename RefFuncsT>
class SharedObject final
{
    /*
     * This makes it possible for a
     * `SharedObject<Something, bt_something, ...>` instance to get
     * assigned an instance of
     * `SharedObject<SpecificSomething, bt_something, ...>` (copy/move
     * constructors and assignment operators), given that
     * `SpecificSomething` inherits `Something`.
     */
    template <typename, typename, typename>
    friend class SharedObject;

public:
    /*!
    @brief
        Builds an empty shared object.
    */
    explicit SharedObject() noexcept
    {
    }

private:
    /*
     * Builds a shared object from `obj` without getting a reference.
     */
    explicit SharedObject(const ObjT& obj) noexcept
        : _mObj {obj}
    {
    }

    /*
     * Common generic "copy" constructor.
     *
     * This constructor is meant to be delegated to by the copy
     * constructor and the generic "copy" constructor.
     *
     * The second parameter, of type `int`, makes it possible to
     * delegate by deduction as you can't explicit the template
     * parameters when delegating to a constructor template.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject(const SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>& other, int) noexcept
        : _mObj {other._mObj}
    {
        this->_getRef();
    }

    /*
     * Common generic "move" constructor.
     *
     * See the comment of the common generic "copy" constructor above.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject(SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>&& other, int) noexcept
        : _mObj {other._mObj}
    {
        /* Reset moved-from object */
        other._reset();
    }

public:
    /*!
    @brief
        Builds a shared object from \bt_p{obj} \em without
        getting a reference.

    @param[in] obj
        Borrowed object to wrap.

    @returns
        Shared object wrapping \bt_p{obj}.
    */
    static SharedObject createWithoutRef(const ObjT& obj) noexcept
    {
        return SharedObject {obj};
    }

    /*!
    @brief
        Builds a wrapper with \bt_p{libObjPtr} and calls
        createWithoutRef(const ObjT&).

    @param[in] libObjPtr
        libbabeltrace2 raw pointer to wrap.

    @returns
        Shared object wrapping \bt_p{libObjPtr}.
    */
    static SharedObject createWithoutRef(LibObjT * const libObjPtr) noexcept
    {
        return SharedObject::createWithoutRef(ObjT {libObjPtr});
    }

    /*!
    @brief
        Builds a shared object from \bt_p{obj}, immediately getting
        a new reference.

    @param[in] obj
        Borrowed object to wrap.

    @returns
        Shared object wrapping \bt_p{obj}.
    */
    static SharedObject createWithRef(const ObjT& obj) noexcept
    {
        SharedObject sharedObj {obj};

        sharedObj._getRefNoNullCheck();
        return sharedObj;
    }

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Other shared object to copy (keeps its current reference
        count).
    */
    SharedObject(const SharedObject& other) noexcept
        : SharedObject {other, 0}
    {
    }

    /*!
    @brief
        Move constructor.

    @param[in] other
        Other shared object to move.
    */
    SharedObject(SharedObject&& other) noexcept
        : SharedObject {std::move(other), 0}
    {
    }

    /*!
    @brief
        Copy assignment operator.

    @param[in] other
        Other shared object to copy (keeps its current reference
        count).

    @returns
        This shared object.
    */
    SharedObject& operator=(const SharedObject& other) noexcept
    {
        /* Use generic "copy" assignment operator */
        return this->operator= <ObjT, LibObjT>(other);
    }

    /*!
    @brief
        Move assignment operator.

    @param[in] other
        Other shared object to move.

    @returns
        This shared object.
    */
    SharedObject& operator=(SharedObject&& other) noexcept
    {
        /* Use generic "move" assignment operator */
        return this->operator= <ObjT, LibObjT>(std::move(other));
    }

    /*
     * Generic "copy" constructor.
     *
     * See the `friend class SharedObject` comment above.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject(const SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>& other) noexcept
        : SharedObject {other, 0}
    {
    }

    /*
     * Generic "move" constructor.
     *
     * See the `friend class SharedObject` comment above.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject(SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>&& other) noexcept
        : SharedObject {std::move(other), 0}
    {
    }

    /*
     * Generic "copy" assignment operator.
     *
     * See the `friend class SharedObject` comment above.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject& operator=(const SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>& other) noexcept
    {
        /* Put current object's reference */
        this->_putRef();

        /* Set new current object and get a reference */
        _mObj = other._mObj;
        this->_getRef();

        return *this;
    }

    /*
     * Generic "move" assignment operator.
     *
     * See the `friend class SharedObject` comment above.
     */
    template <typename OtherObjT, typename OtherLibObjT>
    SharedObject& operator=(SharedObject<OtherObjT, OtherLibObjT, RefFuncsT>&& other) noexcept
    {
        /* Put current object's reference */
        this->_putRef();

        /* Set new current object */
        _mObj = other._mObj;

        /* Reset moved-from object */
        other._reset();

        return *this;
    }

    ~SharedObject()
    {
        this->_putRef();
    }

    /*!
    @brief
        Wrapped borrowed object access.

    @returns
        Wrapped borrowed object.
    */
    ObjT operator*() const noexcept
    {
        return *_mObj;
    }

    /*!
    @brief
        Wrapped borrowed object access.

    @returns
        Proxy of wrapped borrowed object.
    */
    BorrowedObjectProxy<ObjT> operator->() const noexcept
    {
        return _mObj.operator->();
    }

    /*!
    @brief
        Whether or not this shared object is empty.

    @returns
        \c true if this shared object is \em not empty.
    */
    explicit operator bool() const noexcept
    {
        return _mObj.hasObject();
    }

    /*!
    @brief
        Makes this shared object empty.
    */
    void reset() noexcept
    {
        this->_putRef();
        this->_reset();
    }

    /*!
    @brief
        Transfers the reference of the object which this shared object
        wrapper manages and returns it, making the caller become an
        active owner.

    This method makes this object empty.

    @returns
        Managed borrowed object.
    */
    ObjT release() noexcept
    {
        const auto obj = *_mObj;

        this->_reset();
        return obj;
    }

private:
    /*
     * Resets this shared object.
     *
     * To be used when moving it.
     */
    void _reset() noexcept
    {
        _mObj.reset();
    }

    /*
     * Gets a new reference using the configured libbabeltrace2
     * reference incrementation function, only if `_mObj` isn't null.
     */
    void _getRef() const noexcept
    {
        if (_mObj) {
            this->_getRefNoNullCheck();
        }
    }

    /*
     * Gets a new reference using the configured libbabeltrace2
     * reference incrementation function without any null check.
     */
    void _getRefNoNullCheck() const noexcept
    {
        RefFuncsT::get(_mObj.libObjPtr());
    }

    /*
     * Puts a reference using the configured libbabeltrace2 reference
     * decrementation function, only if `_mObj` isn't null.
     */
    void _putRef() const noexcept
    {
        if (_mObj) {
            RefFuncsT::put(_mObj.libObjPtr());
        }
    }

    OptionalBorrowedObject<ObjT> _mObj;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_SHARED_OBJECT_HPP */
