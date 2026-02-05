/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_MESSAGE_ARRAY_HPP
#define BABELTRACE_CPP_COMMON_BT2_MESSAGE_ARRAY_HPP

#include <algorithm>

#include <babeltrace2/babeltrace.h>

#include "common/assert.h"

#include "message.hpp"

namespace bt2 {

class ConstMessageArray;

class ConstMessageArrayIterator final
{
    friend class ConstMessageArray;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = ConstMessage;
    using pointer = value_type *;
    using reference = value_type&;
    using iterator_category = std::input_iterator_tag;

private:
    explicit ConstMessageArrayIterator(const ConstMessageArray& msgArray,
                                       const uint64_t idx) noexcept :
        _mMsgArray {&msgArray}, _mIdx {idx}
    {
    }

public:
    ConstMessageArrayIterator& operator++() noexcept
    {
        ++_mIdx;
        return *this;
    }

    ConstMessageArrayIterator operator++(int) noexcept
    {
        const auto tmp = *this;

        ++(*this);
        return tmp;
    }

    bool operator==(const ConstMessageArrayIterator& other) const noexcept
    {
        BT_ASSERT_DBG(_mMsgArray == other._mMsgArray);
        return _mIdx == other._mIdx;
    }

    bool operator!=(const ConstMessageArrayIterator& other) const noexcept
    {
        return !(*this == other);
    }

    ConstMessage operator*() noexcept;

private:
    const ConstMessageArray *_mMsgArray;
    uint64_t _mIdx;
};

/*!
@brief
    Wrapper of <code>bt_message_array_const</code>.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/message-array.hpp"
@endcode

Depending on the libbabeltrace2 message array to wrap:

<dl>
  <dt>Contains existing messages
  <dd>
    Use wrapExisting().

    Example:

    @code{.cpp}

    bt_message_array_const libMsgs;
    uint64_t count;

    if (bt_message_iterator_next(myIter, &libMsgs, &count) != BT_MESSAGE_ITERATOR_NEXT_STATUS_OK) {
        // Handle special status
    }

    const auto msgs = bt2::ConstMessageArray::wrapExisting(libMsgs, count);

    // At this point `msgs` manages `libMsgs`
    @endcode

  <dt>Is empty and you need to fill it
  <dd>
    Use wrapEmpty().

    Move the ownership of the wrapped libbabeltrace2 array to you
    with release()

    Example:

    @code{.cpp}
    bt_message_iterator_class_next_method_status myNext(
            bt_self_message_iterator * const libSelfMsgIter,
            const bt_message_array_const libMsgs,
            const uint64_t capacity, uint64_t * const count)
    {
        auto msgs = bt2::ConstMessageArray::wrapEmpty(libMsgs, capacity);

        // Create messages and append with `msgs.append(...)`

        *count = msgs.release();
        return BT_MESSAGE_ITERATOR_CLASS_NEXT_METHOD_STATUS_OK;
    }
    @endcode
</dl>

In both cases, the returned message array wrapper is always the sole
owner of the wrapped libbabeltrace2 array: it's not a simple passive view.
The destructor puts the references of the contained messages.
*/
class ConstMessageArray final
{
private:
    explicit ConstMessageArray(const bt_message_array_const libArrayPtr, const std::uint64_t length,
                               const std::uint64_t capacity) noexcept :
        _mLibArrayPtr {libArrayPtr}, _mLen {length}, _mCap {capacity}
    {
        BT_ASSERT_DBG(length <= capacity);
        BT_ASSERT_DBG(capacity > 0);
    }

public:
    /// Message array iterator.
    using Iterator = ConstMessageArrayIterator;

    ~ConstMessageArray()
    {
        this->_putMsgRefs();
    }

    /*
     * Not available because there's no underlying message array to
     * copy to.
     */
    ConstMessageArray(const ConstMessageArray&) = delete;

    /*
     * Not available because we don't need it yet.
     */
    ConstMessageArray& operator=(const ConstMessageArray&) = delete;

    ConstMessageArray(ConstMessageArray&& other) noexcept :
        ConstMessageArray {other._mLibArrayPtr, other._mLen, other._mCap}
    {
        other._reset();
    }

    ConstMessageArray& operator=(ConstMessageArray&& other) noexcept
    {
        /* Put existing message references */
        this->_putMsgRefs();

        /* Move other members to this message array */
        _mLibArrayPtr = other._mLibArrayPtr;
        _mLen = other._mLen;
        _mCap = other._mCap;

        /* Reset other message array */
        other._reset();

        return *this;
    }

    /*!
    @brief
        Wraps an existing libbabeltrace2 array \bt_p{libArrayPtr}, known
        to contain \bt_p{length} messages.

    @attention
        The ownership of the existing messages contained in
        \bt_p{libArrayPtr} is \em moved to the returned
        ConstMessageArray instance.

    This is similar to what the constructor of
    <code>std::shared_ptr</code> does. Do \em not wrap the same
    libbabeltrace2 array twice.

    @param[in] libArrayPtr
        libbabeltrace2 message array to wrap.
    @param[in] length
        Number of existing messages in \bt_p{libArrayPtr}.

    @returns
        Wrapper of \bt_p{libArrayPtr}.
    */
    static ConstMessageArray wrapExisting(const bt_message_array_const libArrayPtr,
                                          const std::uint64_t length) noexcept
    {
        return ConstMessageArray {libArrayPtr, length, length};
    }

    /*
     * Wraps an existing library array `libArrayPtr`, known to be empty,
     * with a capacity of `capacity` messages.
     */

    /*!
    @brief
        Wraps an existing libbabeltrace2 array \bt_p{libArrayPtr},
        known to be empty, with a capacity of \bt_p{capacity}
        messages.

    @attention
        The ownership of the existing messages contained in
        \bt_p{libArrayPtr} is \em moved_to the returned
        ConstMessageArray instance.

    @param[in] libArrayPtr
        libbabeltrace2 message array to wrap.
    @param[in] capacity
        Capacity of \bt_p{libArrayPtr}.

    @returns
        Wrapper of \bt_p{libArrayPtr}.
    */
    static ConstMessageArray wrapEmpty(const bt_message_array_const libArrayPtr,
                                       const std::uint64_t capacity) noexcept
    {
        return ConstMessageArray {libArrayPtr, 0, capacity};
    }

    /*!
    @brief
        Number of messages in this array.

    @returns
        Number of messages in this array.
    */
    std::uint64_t length() const noexcept
    {
        return _mLen;
    }

    /*!
    @brief
        Capacity of this array.

    @returns
        Capacity of this array.
    */
    std::uint64_t capacity() const noexcept
    {
        return _mCap;
    }

    /*!
    @brief
        Whether or not this array is empty.

    @returns
        \c true if this array is empty.
    */
    bool isEmpty() const noexcept
    {
        return _mLen == 0;
    }

    /*!
    @brief
        Whether or not this array is full.

    @returns
        \c true if this array is full.
    */
    bool isFull() const noexcept
    {
        return _mLen == _mCap;
    }

    /*!
    @brief
        Appends the message \bt_p{message} to this array.

    @param[in] message
        Message to append to this array.

    @returns
        This array.

    @pre
        This array isn't full (isFull() returns \c false).
    */
    ConstMessageArray& append(ConstMessage::Shared message) noexcept
    {
        BT_ASSERT_DBG(!this->isFull());

        /* Move reference to underlying array */
        _mLibArrayPtr[_mLen] = message.release().libObjPtr();
        ++_mLen;
        return *this;
    }

    /*!
    @brief
        Transfers the ownership of the wrapped libbabeltrace2 array to
        the caller, returning the number of contained messages (array
        length).

    @returns
        Array length.
    */
    std::uint64_t release() noexcept
    {
        const auto len = _mLen;

        this->_reset();
        return len;
    }

    /*!
    @brief
        Returns the message at the index \bt_p{index} of this array.

    @param[in] index
        Index of the message to borrow.

    @returns
        Borrowed message at the index \bt_p{index}.

    @pre
        \bt_p{index} is less than what length() returns.
    */
    ConstMessage operator[](const std::uint64_t index) const noexcept
    {
        BT_ASSERT_DBG(index < _mLen);
        return ConstMessage {_mLibArrayPtr[index]};
    }

    /*!
    @brief
        Iterator at the beginning of this array.

    @returns
        Iterator at the beginning of this array.
    */
    Iterator begin() const noexcept
    {
        return Iterator {*this, 0};
    }

    /*!
    @brief
        Iterator after the end of this array.

    @returns
        Iterator after the end of this array.
    */
    Iterator end() const noexcept
    {
        return Iterator {*this, this->length()};
    }

private:
    void _reset() noexcept
    {
        /*
         * This means this array is pretty much dead, and any call to
         * append() or operator[]() will make assertions fail.
         *
         * That being said, you may still move another array to this
         * one.
         */
        _mLen = 0;
        _mCap = 0;
    }

    /*
     * Decrements the reference count of all the contained messages.
     */
    void _putMsgRefs() noexcept
    {
        std::for_each(&_mLibArrayPtr[0], &_mLibArrayPtr[_mLen], [](const auto msg) {
            bt_message_put_ref(msg);
        });
    }

    /* Underlying array which is generally owned by the library */
    bt_message_array_const _mLibArrayPtr;

    /* Length (count of contained messages) */
    std::uint64_t _mLen;

    /* Capacity (maximum length) */
    std::uint64_t _mCap;
};

inline ConstMessage ConstMessageArrayIterator::operator*() noexcept
{
    return (*_mMsgArray)[_mIdx];
}

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_MESSAGE_ARRAY_HPP */
