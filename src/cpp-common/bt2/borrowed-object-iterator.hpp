/*
 * Copyright (c) 2022 Francis Deslauriers <francis.deslauriers@efficios.com>
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_ITERATOR_HPP
#define BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_ITERATOR_HPP

#include <cstdint>
#include <type_traits>
#include <utility>

#include "common/assert.h"

#include "borrowed-object-proxy.hpp"

namespace bt2 {

/*!
@brief
    Wrapper container iterator.

@ingroup common-cpp-bt2

@code{.cpp}
#include "cpp-common/bt2/borrowed-object-iterator.hpp"
@endcode

An iterator class to iterate an instance of a wrapper
container of type \bt_p{ContainerT}.

@tparam ContainerT
    @parblock
    Type of the container of wrappers.

    Must implement <code>operator[]()</code> to return
    the borrowed object at the index \bt_p{i}:

    @code{.cpp}
    SomeObject operator[](std::uint64_t i) const noexcept;
    @endcode
    @endparblock
*/
template <typename ContainerT>
class BorrowedObjectIterator final
{
    friend ContainerT;

public:
    /// Type of contained wrappers.
    using Object = typename std::remove_reference<
        decltype(std::declval<ContainerT>()[std::declval<std::uint64_t>()])>::type;

private:
    explicit BorrowedObjectIterator(const ContainerT container, const uint64_t idx) :
        _mContainer {container}, _mIdx {idx}
    {
    }

public:
    /*!
    @brief
        Advances this iterator.

    @returns
        This iterator.
    */
    BorrowedObjectIterator& operator++() noexcept
    {
        ++_mIdx;
        return *this;
    }

    /*!
    @brief
        Advances this iterator.

    @returns
        This iterator.
    */
    BorrowedObjectIterator operator++(int) noexcept
    {
        const auto tmp = *this;

        ++(*this);
        return tmp;
    }

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other iterator to compare to.

    @returns
        \c true if this iterator is equal to \bt_p{other}.
    */
    bool operator==(const BorrowedObjectIterator& other) const noexcept
    {
        BT_ASSERT_DBG(_mContainer.isSame(other._mContainer));
        return _mIdx == other._mIdx;
    }

    /*!
    @brief
        Inequality operator.

    @param[in] other
        Other iterator to compare to.

    @returns
        \c true if this iterator is \em not equal to \bt_p{other}.
    */
    bool operator!=(const BorrowedObjectIterator& other) const noexcept
    {
        return !(*this == other);
    }

    /*!
    @brief
        Current wrapper access.

    @returns
        Current wrapper.
    */
    Object operator*() const noexcept
    {
        return _mContainer[_mIdx];
    }

    /*!
    @brief
        Current wrapper proxy access.

    @returns
        Proxy of current wrapper.
    */
    BorrowedObjectProxy<Object> operator->() const noexcept
    {
        return BorrowedObjectProxy<Object> {(**this).libObjPtr()};
    }

private:
    ContainerT _mContainer;
    std::uint64_t _mIdx;
};

} /* namespace bt2 */

#endif /* BABELTRACE_CPP_COMMON_BT2_BORROWED_OBJECT_ITERATOR_HPP */
