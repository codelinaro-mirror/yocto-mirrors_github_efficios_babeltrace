/*
 * Copyright 2019-2020 (c) Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_HPP
#define BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_HPP

#include <functional>
#include <type_traits>

#include "common/assert.h"

namespace bt2 {

/*!
@brief
    Wrapper of libbabeltrace2 borrowed object pointer.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/borrowed-object.hpp"
@endcode

An instance of this class wraps a pointer to a libbabeltrace2 object
of type \bt_p{LibObjT} \em without managing any reference counting.

This is an abstract base class for any libbabeltrace2 object wrapper.

The user of a wrapper, including methods of a derived class,
can call libObjPtr() to access the raw libbabeltrace2 object pointer.

You may only build a wrapper with a pointer which isn't
<code>nullptr</code>.

See OptionalBorrowedObject for an optional version.

@tparam LibObjT
    The direct libbabeltrace2 object type, for example
    \c bt_stream_class or <code>const bt_value</code>.
*/
template <typename LibObjT>
class BorrowedObject
{
    static_assert(!std::is_pointer<LibObjT>::value, "`LibObjT` must not be a pointer");

    /*
     * This makes it possible for a `BorrowedObject<const bt_something>`
     * instance to get assigned an instance of
     * `BorrowedObject<bt_something>` ("copy" constructor and
     * "assignment" operator).
     *
     * C++ forbids the other way around.
     */
    template <typename>
    friend class BorrowedObject;

private:
    /*
     * Provides `val` which indicates whether or not you can assign this
     * object from a borrowed object of type `OtherLibObjT`.
     */
    template <typename OtherLibObjT>
    struct _AssignableFromConst final
    {
        /*
         * If `LibObjT` is const (for example, `const bt_value`), then
         * you may always assign from its non-const equivalent (for
         * example, `bt_value`). In C (correct):
         *
         *     bt_value * const meow = bt_value_bool_create_init(BT_TRUE);
         *     const bt_value * const mix = meow;
         *
         * If `LibObjT` is non-const, then you may not assign from its
         * const equivalent. In C (not correct):
         *
         *     const bt_value * const meow =
         *         bt_value_array_borrow_element_by_index_const(some_val, 17);
         *     bt_value * const mix = meow;
         */
        static constexpr bool val =
            std::is_const<LibObjT>::value || !std::is_const<OtherLibObjT>::value;
    };

protected:
    /// The type of this complete wrapper.
    using _ThisBorrowedObject = BorrowedObject<LibObjT>;

public:
    /// libbabeltrace2 object type.
    using LibObj = LibObjT;

    /// libbabeltrace2 raw object pointer type.
    using LibObjPtr = LibObjT *;

protected:
    /*!
    @brief
        Builds a borrowed object to wrap the libbabeltrace2 object
        pointer \bt_p{libObjPtr}.

    @param[in] libObjPtr
        libbabeltrace2 object pointer to wrap.

    @bt_pre_not_null{libObjPtr}
    */
    explicit BorrowedObject(const LibObjPtr libObjPtr) noexcept : _mLibObjPtr {libObjPtr}
    {
        BT_ASSERT_DBG(libObjPtr);
    }

    /*!
    @brief
        Generic "copy" constructor.

    This converting constructor accepts both an instance of
    #_ThisBorrowedObject and an instance (\bt_p{other}) of
    <code>BorrowedObject&lt;ConstLibObjT&gt;</code>, where
    \c ConstLibObjT is the \c const version of
    \bt_p{LibObjT}, if applicable.

    This makes it possible for a
    <code>BorrowedObject&lt;const bt_something&gt;</code>
    instance to be built from an instance of
    <code>BorrowedObject&lt;bt_something&gt;</code>.
    C++ forbids the other way around.

    @tparam OtherLibObjT
        Type of the other libbabeltrace2 object.

    @param[in] other
        Other wrapper to copy.
    */
    template <typename OtherLibObjT>
    BorrowedObject(const BorrowedObject<OtherLibObjT>& other) noexcept :
        BorrowedObject {other._mLibObjPtr}
    {
        static_assert(_AssignableFromConst<OtherLibObjT>::val,
                      "Don't assign a non-const wrapper from a const wrapper.");
    }

    /*!
    @brief
        Generic "assignment" operator.

    This operator accepts both an instance of
    #_ThisBorrowedObject and an instance (\bt_p{other}) of
    <code>BorrowedObject&lt;ConstLibObjT&gt;</code>,
    where \c ConstLibObjT is the \c const version of
    \bt_p{LibObjT}, if applicable.

    This makes it possible for a
    <code>BorrowedObject&lt;const bt_something&gt;</code>
    instance to get assigned an instance of
    <code>BorrowedObject&lt;bt_something&gt;</code>.
    C++ forbids the other way around,
    therefore we use a static assertion to show a more relevant
    context in the compiler error message.

    @tparam OtherLibObjT
        Type of the other libbabeltrace2 object.

    @param[in] other
        Other wrapper to copy.

    @returns
        This wrapper.
    */
    template <typename OtherLibObjT>
    _ThisBorrowedObject operator=(const BorrowedObject<OtherLibObjT>& other) noexcept
    {
        static_assert(_AssignableFromConst<OtherLibObjT>::val,
                      "Don't assign a non-const wrapper from a const wrapper.");

        _mLibObjPtr = other._mLibObjPtr;
        return *this;
    }

public:
    /*!
    @brief
        Hash of this object, solely based on its raw
        libbabeltrace2 pointer.

    @returns
        Hash of this object.
    */
    std::size_t hash() const noexcept
    {
        return std::hash<LibObjPtr> {}(_mLibObjPtr);
    }

    /*!
    @brief
        Returns whether or not this object is the exact same as
        \bt_p{other}, solely based on the
        raw libbabeltrace2 pointers.

    @param[in] other
        Other wrapper to compare to.

    @returns
        \c true if this object is the exact same as \bt_p{other}.
    */
    bool isSame(const _ThisBorrowedObject& other) const noexcept
    {
        return _mLibObjPtr == other._mLibObjPtr;
    }

    /*!
    @brief
        Wrapped libbabeltrace2 object pointer.

    @returns
        Wrapped libbabeltrace2 object pointer.
    */
    LibObjPtr libObjPtr() const noexcept
    {
        return _mLibObjPtr;
    }

private:
    LibObjPtr _mLibObjPtr;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_HPP */
