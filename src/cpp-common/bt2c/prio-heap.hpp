/*
 * Copyright (c) 2011 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_PRIO_HEAP_HPP
#define BABELTRACE_CPP_COMMON_BT2C_PRIO_HEAP_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

#include "common/assert.h"

namespace bt2c {

/*!
@brief
    Priority heap.

@ingroup common-cpp-bt2c

A templated C++ version of what used to be the \c bt_heap_ C API,
written by Mathieu Desnoyers, which implements an efficient heap data
structure.

This implements a static-sized priority heap based on
<a href="https://en.wikipedia.org/wiki/Introduction_to_Algorithms">CLRS</a>,
chapter&nbsp;6.

This version copies instances of \bt_p{T} during its operations, so it's
best to use with small objects such as pointers, integers, and
small PODs.

\bt_p{CompT} is the type of the callable comparator. It must be possible
to call an instance \c comp of \bt_p{CompT} as such:

@code{.cpp}
comp(a, b)
@endcode

\c comp accepts two different <code>const T&</code> values and returns a value
contextually convertible to \c bool which must be true if \c a appears
\em after \c b.

The benefit of this version over \c std::priority_queue is the
replaceTop() method which you can call to remove the top (greatest)
element and then insert a new one immediately afterwards with a
single heap rebalance.

@code{.cpp}
#include "cpp-common/bt2c/text-loc.hpp"
@endcode

@pre
    - \bt_p{T} is default-constructible.
    - \bt_p{T} is copy-constructible.
    - \bt_p{T} is copy-assignable.
*/
template <typename T, typename CompT = std::greater<T>>
class PrioHeap final
{
    static_assert(std::is_default_constructible_v<T>, "`T` is default-constructible.");
    static_assert(std::is_copy_constructible_v<T>, "`T` is copy-constructible.");
    static_assert(std::is_copy_assignable_v<T>, "`T` is copy-assignable.");

public:
    /*!
    @brief
        Builds a priority heap using the comparator \bt_p{comp} and with
        an initial capacity of \bt_p{cap} elements.

    @param[in] comp
        Comparator to use to compare elements during a heap rebalance.
    @param[in] cap
        Initial capacity of the heap.
    */
    explicit PrioHeap(CompT comp, const std::size_t cap)
        : _mComp {std::move(comp)}
    {
        _mElems.reserve(cap);
    }

    /*!
    @brief
        Builds a priority heap using the comparator \bt_p{comp} and with
        an initial capacity of zero.

    @param[in] comp
        Comparator to use to compare elements during a heap rebalance.
    */
    explicit PrioHeap(CompT comp)
        : PrioHeap {std::move(comp), 0}
    {
    }

    /*!
    @brief
        Builds a priority heap using a default comparator and with an
        initial capacity of zero.
    */
    explicit PrioHeap()
        : PrioHeap {CompT {}, 0}
    {
    }

    /*!
    @brief
        Number of contained elements.

    @returns
        Number of contained elements.
    */
    std::size_t len() const noexcept
    {
        return _mElems.size();
    }

    /*!
    @brief
        Whether or not this heap is empty.

    @retval false
        Not empty.
    @retval true
        Empty.
    */
    bool isEmpty() const noexcept
    {
        return _mElems.empty();
    }

    /*!
    @brief
        Removes all the elements.
    */
    void clear()
    {
        _mElems.clear();
    }

    /*!
    @brief
        Current top (greatest) element.

    @returns
        Current top (greatest) element.
    */
    const T& top() const noexcept
    {
        BT_ASSERT_DBG(!this->isEmpty());
        this->_validate();
        return _mElems.front();
    }

    /*!
    @brief
        Current top (greatest) element.

    @returns
        Current top (greatest) element.
    */
    T& top() noexcept
    {
        BT_ASSERT_DBG(!this->isEmpty());
        this->_validate();
        return _mElems.front();
    }

    /*!
    @brief
        Inserts a copy of \bt_p{elem}.

    @param[in] elem
        Element to insert.
    */
    void insert(const T& elem)
    {
        /* Default-construct the new one */
        _mElems.resize(_mElems.size() + 1);

        auto pos = this->len() - 1;

        while (pos > 0 && this->_gt(elem, this->_parentElem(pos))) {
            /* Move parent down until we find the right spot */
            _mElems[pos] = this->_parentElem(pos);
            pos = this->_parentPos(pos);
        }

        _mElems[pos] = elem;
        this->_validate();
    }

    /*!
    @brief
        Removes the top (greatest) element.

    @pre
        isEmpty() returns \c false.
    */
    void removeTop()
    {
        BT_ASSERT_DBG(!this->isEmpty());

        if (_mElems.size() == 1) {
            /* Fast path for a single element */
            _mElems.clear();
            return;
        }

        /*
         * Shrink, replace the current top by the previous last element,
         * and heapify.
         */
        const auto lastElem = _mElems.back();

        _mElems.resize(_mElems.size() - 1);
        return this->replaceTop(lastElem);
    }

    /*!
    @brief
        Removes the top (greatest) element, and inserts a copy
        of \bt_p{elem}.

    This is equivalent to using removeTop() and then insert(), but more
    efficient (single rebalance).

    @param[in] elem
        Element to insert.

    @pre
        isEmpty() returns \c false.
    */
    void replaceTop(const T& elem)
    {
        BT_ASSERT_DBG(!this->isEmpty());

        /* Replace the current top and heapify */
        _mElems[0] = elem;
        this->_heapify(0);
    }

private:
    static std::size_t _parentPos(const std::size_t pos) noexcept
    {
        return (pos - 1) >> 1;
    }

    void _heapify(std::size_t pos)
    {
        while (true) {
            std::size_t largestPos;

            if (const auto leftPos = (pos << 1) + 1;
                leftPos < this->len() && this->_gt(_mElems[leftPos], _mElems[pos])) {
                largestPos = leftPos;
            } else {
                largestPos = pos;
            }

            if (const auto rightPos = (pos << 1) + 2;
                rightPos < this->len() && this->_gt(_mElems[rightPos], _mElems[largestPos])) {
                largestPos = rightPos;
            }

            if (G_UNLIKELY(largestPos == pos)) {
                break;
            }

            const auto tmpElem = _mElems[pos];

            _mElems[pos] = _mElems[largestPos];
            _mElems[largestPos] = tmpElem;
            pos = largestPos;
        }

        this->_validate();
    }

    T& _parentElem(const std::size_t pos) noexcept
    {
        return _mElems[this->_parentPos(pos)];
    }

    bool _gt(const T& a, const T& b) const
    {
        /* Forward to user comparator */
        return _mComp(a, b);
    }

    void _validate() const noexcept
    {
#ifdef BT_DEBUG_MODE
        if (_mElems.empty()) {
            return;
        }

        for (std::size_t i = 1; i < _mElems.size(); ++i) {
            BT_ASSERT_DBG(!this->_gt(_mElems[i], _mElems.front()));
        }
#endif /* BT_DEBUG_MODE */
    }

    CompT _mComp;
    std::vector<T> _mElems;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_PRIO_HEAP_HPP */
