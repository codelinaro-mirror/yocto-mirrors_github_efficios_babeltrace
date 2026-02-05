/*
 * SPDX-FileCopyrightText: 2020-2023 Philippe Proulx <pproulx@efficios.com>
 * SPDX-FileCopyrightText: 2022 Francis Deslauriers <francis.deslauriers@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_UUID_HPP
#define BABELTRACE_CPP_COMMON_BT2C_UUID_HPP

/*!
@file

@brief
    C++
    <a href="https://en.wikipedia.org/wiki/Universally_unique_identifier">UUID</a>
    classes.

@ingroup common-cpp-bt2c

@code{.cpp}
#include "cpp-common/bt2c/uuid.hpp"
@endcode

This file offers two classes:

<dl>
  <dt>bt2c::Uuid
  <dd>
    An instance contains a UUID, therefore its size is 16&nbsp;bytes.

  <dt>bt2c::UuidView
  <dd>
    An instance only views the bytes of an existing UUID without
    containing it.
</dl>

You can convert from an instance of bt2c::Uuid to bt2c::UuidView and
vice versa implicitly.

This file also contains the {fmt} formatting function for bt2c::Uuid.
*/

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

#include "common/assert.h"
#include "common/uuid.h"

namespace bt2c {

class Uuid;

/*!
@brief
    UUID view.

A UUID view is a view of existing UUID data.

A UuidView object doesn't contain its UUID data: see #Uuid for a
UUID data container.

Get the viewed bytes of a UUID view with data().

Get a single viewed byte by index with operator[]().

Iterate the viewed bytes with begin() and end().

Create a textual representation of the viewed UUID with str().

Check whether or not the viewed UUID is the nil UUID with isNil().
*/
class UuidView final
{
public:
    /*! @brief UUID byte. */
    using Val = std::uint8_t;

    /*! @brief Constant data iterator. */
    using ConstIter = const Val *;

public:
    /*!
    @brief
        Builds a view of the 16 UUID bytes \bt_p{uuid}.

    @param[in] uuid
        16 UUID bytes to view.

    @pre
        \bt_p{uuid} has at least 16&nbsp;bytes available.
    */
    explicit UuidView(const Val * const uuid) noexcept : _mUuid {uuid}
    {
        BT_ASSERT_DBG(uuid);
    }

    /*!
    @brief
        Builds a view of the UUID \bt_p{uuid}.

    @param[in] uuid
        UUID to view.
    */
    explicit UuidView(const Uuid& uuid) noexcept;

    UuidView(const UuidView&) noexcept = default;
    UuidView& operator=(const UuidView&) noexcept = default;

    /*!
    @brief
        Makes this view view the 16 UUID bytes \bt_p{uuid}.

    @param[in] uuid
        UUID bytes to view.

    @returns
        <code>*this</code>

    @pre
        \bt_p{uuid} has at least 16&nbsp;bytes available.
    */
    UuidView& operator=(const Val * const uuid) noexcept
    {
        _mUuid = uuid;
        return *this;
    }

    /*!
    @brief
        Creates a UUID from this view.

    @returns
        UUID containing the viewed bytes.
    */
    operator Uuid() const noexcept;

    /*!
    @brief
        Creates and returns a string containing the textual
        representation of the viewed UUID.

    @returns
        Textual representation of the viewed UUID.
    */
    std::string str() const
    {
        std::string s;

        s.resize(BT_UUID_STR_LEN);
        bt_uuid_to_str(_mUuid, &s[0]);

        return s;
    }

    /*!
    @brief
        Returns whether or not the viewed UUID is equal to
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if the viewed UUID is equal to \bt_p{other}.
    */
    bool operator==(const UuidView& other) const noexcept
    {
        return bt_uuid_compare(_mUuid, other._mUuid) == 0;
    }

    /*!
    @brief
        Returns whether or not the viewed UUID is \em not equal to
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if the viewed UUID is \em not equal to \bt_p{other}.
    */
    bool operator!=(const UuidView& other) const noexcept
    {
        return !(*this == other);
    }

    /*!
    @brief
        Returns whether or not the viewed UUID is less than
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if the viewed UUID is less than \bt_p{other}.
    */
    bool operator<(const UuidView& other) const noexcept
    {
        return bt_uuid_compare(_mUuid, other._mUuid) < 0;
    }

    /*!
    @brief
        16

    @returns
        16
    */
    static constexpr std::size_t size() noexcept
    {
        return BT_UUID_LEN;
    }

    /*!
    @brief
        Pointer to the 16 viewed UUID bytes.

    @returns
        Pointer to the 16 viewed UUID bytes.
    */
    const Val *data() const noexcept
    {
        return _mUuid;
    }

    /*!
    @brief
        Returns the viewed UUID byte at index \bt_p{index}.

    @param[in] index
        Index of the viewed UUID byte to get.

    @returns
        Viewed UUID byte at index \bt_p{index}.

    @pre
        \bt_p{index}&nbsp;&lt;&nbsp;16.
    */
    Val operator[](const std::size_t index) const noexcept
    {
        return _mUuid[index];
    }

    /*!
    @brief
        Iterator at the first byte of the viewed UUID.

    @returns
        Iterator at the first byte of the viewed UUID.
    */
    ConstIter begin() const noexcept
    {
        return _mUuid;
    }

    /*!
    @brief
        Iterator \em after the last byte of the viewed UUID.

    @returns
        Iterator \em after the last byte of the viewed UUID.
    */
    ConstIter end() const noexcept
    {
        return _mUuid + this->size();
    }

    /*!
    @brief
        Whether or not the viewed UUID is the nil UUID.

    @returns
        \c true if the viewed UUID is the nil UUID.
    */
    bool isNil() const noexcept
    {
        return std::all_of(this->begin(), this->end(), [](const std::uint8_t byte) {
            return byte == 0;
        });
    }

private:
    const Val *_mUuid;
};

/*
 * A universally unique identifier.
 *
 * A `Uuid` object contains its UUID data: see `UuidView` to have a
 * UUID view on existing UUID data.
 */

/*!
@brief
    UUID.

A Uuid instance contains the 16 bytes of a UUID.

Generate a new UUID with Uuid::generate().

Get the bytes of a UUID with data().

Get a single byte by index with operator[]().

Iterate the bytes with begin() and end().

Create a textual representation of the UUID with str().

Check whether or not the UUID is the nil UUID with isNil().

Validate a UUID string with Uuid::isValidUuidStr().
*/
class Uuid final
{
public:
    using Val = UuidView::Val;
    using ConstIter = UuidView::ConstIter;

public:
    /*!
    @brief
        Builds the nil UUID.
    */
    explicit Uuid() noexcept = default;

    /*!
    @brief
        Builds a UUID containing a copy of the 16 bytes \bt_p{uuid}.

    @param[in] uuid
        16 UUID bytes to copy.

    @pre
        \bt_p{uuid} has at least 16&nbsp;bytes available.
    */
    explicit Uuid(const Val * const uuid) noexcept
    {
        this->_setFromPtr(uuid);
    }

    /*!
    @brief
        Builds a UUID containing the bytes represented by \bt_p{str}.

    @param[in] str
        Textual representation of a UUID.

    @pre
        \bt_p{str} is a valid standard textual representation of a UUID,
        for example <code>40311ef2-16a5-4a16-8ef4-10783d8701ab</code>
        (see isValidUuidStr()).
    */
    explicit Uuid(const std::string_view str) noexcept
    {
        const auto ret = bt_uuid_from_str(str.data(), str.data() + str.size(), _mUuid.data());
        BT_ASSERT(ret == 0);
    }

    /*!
    @brief
        Builds a UUID containing a copy of the 16 bytes viewed
        by \bt_p{view}.

    @param[in] view
        View of the 16 UUID bytes to copy.
    */
    explicit Uuid(const UuidView& view) noexcept : Uuid {view.data()}
    {
    }

    Uuid(const Uuid&) noexcept = default;
    Uuid& operator=(const Uuid&) noexcept = default;

    /*!
    @brief
        Makes this UUID contain a copy of the 16 UUID bytes \bt_p{uuid}.

    @param[in] uuid
        16 UUID bytes to copy.

    @returns
        <code>*this</code>

    @pre
        \bt_p{uuid} has at least 16&nbsp;bytes available.
    */
    Uuid& operator=(const Val * const uuid) noexcept
    {
        this->_setFromPtr(uuid);
        return *this;
    }

    /*!
    @brief
        Generates and returns a new UUID.

    @returns
        New UUID.
    */
    static Uuid generate() noexcept
    {
        bt_uuid_t uuidGen;

        bt_uuid_generate(uuidGen);
        return Uuid {uuidGen};
    }

    /*!
    @brief
        Creates and returns a string containing the textual
        representation of this UUID.

    @returns
        Textual representation of this UUID.
    */
    std::string str() const
    {
        return this->_view().str();
    }

    /*!
    @brief
        Returns whether or not this UUID is equal to
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if this UUID is equal to \bt_p{other}.
    */
    bool operator==(const Uuid& other) const noexcept
    {
        return this->_view() == other._view();
    }

    /*!
    @brief
        Returns whether or not this UUID is \em not equal to
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if this UUID is \em not equal to \bt_p{other}.
    */
    bool operator!=(const Uuid& other) const noexcept
    {
        return this->_view() != other._view();
    }

    /*!
    @brief
        Returns whether or not this UUID is less than
        \bt_p{other}.

    @param[in] other
        Other UUID to compare to.

    @returns
        \c true if this UUID is less than \bt_p{other}.
    */
    bool operator<(const Uuid& other) const noexcept
    {
        return this->_view() < other._view();
    }

    /*
     * The returned UUID view must not outlive the UUID object.
     */

    /*!
    @brief
        Creates a view of this UUID.

    @returns
        @parblock
        View of this UUID.

        Valid as long as this UUID exists.
        @endparblock
    */
    operator UuidView() const noexcept
    {
        return this->_view();
    }

    /*!
    @brief
        16

    @returns
        16
    */
    static constexpr std::size_t size() noexcept
    {
        return UuidView::size();
    }

    /*!
    @brief
        Pointer to the 16 bytes of this UUID.

    @returns
        Pointer to the 16 bytes of this UUID.
    */
    const Val *data() const noexcept
    {
        return _mUuid.data();
    }

    /*!
    @brief
        Returns the UUID byte at index \bt_p{index}.

    @param[in] index
        Index of the UUID byte to get.

    @returns
        UUID byte at index \bt_p{index}.

    @pre
        \bt_p{index}&nbsp;&lt;&nbsp;16.
    */
    Val operator[](const std::size_t index) const noexcept
    {
        return this->_view()[index];
    }

    /*!
    @brief
        Iterator at the first byte of this UUID.

    @returns
        Iterator at the first byte of this UUID.
    */
    ConstIter begin() const noexcept
    {
        return this->_view().begin();
    }

    /*!
    @brief
        Iterator \em after the last byte of this UUID.

    @returns
        Iterator \em after the last byte of this UUID.
    */
    ConstIter end() const noexcept
    {
        return this->_view().end();
    }

    /*!
    @brief
        Whether or not this UUID is the nil UUID.

    @returns
        \c true if this UUID is the nil UUID.
    */
    bool isNil() const noexcept
    {
        return this->_view().isNil();
    }

    /*!
    @brief
        Returns whether or not \bt_p{str} is a valid UUID
        textual representation.

    @param[in] str
        UUID textual representation to check.

    @returns
        \c true if \bt_p{str} is a valid UUID textual representation.
    */
    static bool isValidUuidStr(const std::string_view str) noexcept
    {
        std::array<Val, Uuid::size()> tmp;

        return bt_uuid_from_str(str.data(), str.data() + str.size(), tmp.data()) == 0;
    }

private:
    /*
     * std::copy_n() won't throw when simply copying bytes below,
     * therefore this method won't throw.
     */
    void _setFromPtr(const Val * const uuid) noexcept
    {
        BT_ASSERT(uuid);
        std::copy_n(uuid, BT_UUID_LEN, std::begin(_mUuid));
    }

    UuidView _view() const noexcept
    {
        return UuidView {_mUuid.data()};
    }

    std::array<Val, UuidView::size()> _mUuid = {};
};

inline UuidView::UuidView(const Uuid& uuid) noexcept : _mUuid {uuid.data()}
{
}

inline UuidView::operator Uuid() const noexcept
{
    return Uuid {*this};
}

inline std::string format_as(const bt2c::Uuid& uuid)
{
    return uuid.str();
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_UUID_HPP */
