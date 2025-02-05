/*
 * Copyright (c) 2023 Simon Marchi <simon.marchi@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_OBSERVABLE_HPP
#define BABELTRACE_CPP_COMMON_BT2C_OBSERVABLE_HPP

#include <algorithm>
#include <cstdint>
#include <functional>
#include <limits>
#include <utility>
#include <vector>

#include "common/assert.h"

namespace bt2c {

/*!
@brief
    <a href="https://en.wikipedia.org/wiki/Observer_pattern">Observer pattern</a>.

@ingroup common-cpp-bt2c

Instantiate an observable with, for example:

@code{.cpp}
bt2c::Observable<int, const std::string&> myObservable;
@endcode

The template arguments are the parameter type(s) of the data passed from
the actor which notifies the observers to the observer callbacks.

Attach an observer with attach():

@code{.cpp}
auto token = myObservable.attach([](const int i, const std::string& s) {
    // Do something
});
@endcode

attach() returns a token (Observable::Token instance) which identifies
this specific observer within the observable. The destructor of the
token detaches the observer from the observable.

Notify all the observers with notify(), for example:

@code{.cpp}
myObservable.notify(23, "salut");
@endcode

You can move an observable, but not copy it.

@code{.cpp}
#include "cpp-common/bt2c/observable.hpp"
@endcode
*/
template <typename... Args>
class Observable
{
private:
    using _TokenId = std::uint64_t;
    using _ThisObservable = Observable<Args...>;

    /* Type of user callback of an observer */
    using _ObserverFunc = std::function<void(Args...)>;

public:
    /*!
    @brief
        Observer token.

    A token instance is a unique observer handle within a
    given observable.

    On destruction, the token detaches the observer from the observable.

    You can move a token, but not copy it.
    */
    class Token
    {
        friend class Observable;

    private:
        explicit Token(_ThisObservable& observable, const _TokenId tokenId) noexcept :
            _mObservable {&observable}, _mTokenId(tokenId)
        {
        }

    public:
        ~Token()
        {
            if (_mTokenId != _invalidTokenId) {
                _mObservable->_detach(_mTokenId);
            }
        }

        Token(const Token&) = delete;

        Token(Token&& other) noexcept :
            _mObservable {other._mObservable}, _mTokenId {other._mTokenId}
        {
            other._mTokenId = _invalidTokenId;
        }

        Token& operator=(const Token&) = delete;

        Token& operator=(Token&& other) noexcept
        {
            _mObservable = other._mObservable;
            _mTokenId = other._mTokenId;
            other._mTokenId = _invalidTokenId;
        }

    private:
        static constexpr _TokenId _invalidTokenId = std::numeric_limits<_TokenId>::max();
        _ThisObservable *_mObservable;
        _TokenId _mTokenId;
    };

public:
    /*!
    @brief
        Builds an observable.
    */
    Observable() = default;

    Observable(const Observable&) = delete;
    Observable(Observable&&) = default;
    Observable& operator=(const Observable&) = delete;
    Observable& operator=(Observable&&) = default;

    /*!
    @brief
        Attaches an observer with the callback \bt_p{func}
        and returns a corresponding token.

    @param[in] func
        Observer callback.

    @returns
        Observer token.
    */
    Token attach(_ObserverFunc func)
    {
        const auto tokenId = _mNextTokenId;

        ++_mNextTokenId;
        _mObservers.emplace_back(tokenId, std::move(func));
        return Token {*this, tokenId};
    }

    /*
     * Notifies all the managed observers, passing `args` to their user
     * callback.
     */

    /*!
    @brief
        Notifies all the attached observers, passing \bt_p{args} to
        their callback function.

    @param[in] args
        Arguments to pass to the observer callbacks.
    */
    void notify(Args... args)
    {
        for (auto& observer : _mObservers) {
            observer.func(std::forward<Args>(args)...);
        }
    }

private:
    /* Element type of `_mObservers` */
    struct _Observer
    {
        _Observer(const _TokenId tokenIdParam, _ObserverFunc funcParam) :
            tokenId {tokenIdParam}, func {std::move(funcParam)}
        {
        }

        _TokenId tokenId;
        _ObserverFunc func;
    };

    /*
     * Removes the observer having the token ID `tokenId` from this
     * observable.
     */
    void _detach(const _TokenId tokenId)
    {
        const auto it =
            std::remove_if(_mObservers.begin(), _mObservers.end(), [tokenId](_Observer& obs) {
                return obs.tokenId == tokenId;
            });

        BT_ASSERT(_mObservers.end() - it == 1);
        _mObservers.erase(it, _mObservers.end());
    }

    /* Next token ID to hand out */
    _TokenId _mNextTokenId = 0;

    /* List of observers */
    mutable std::vector<_Observer> _mObservers;
};

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_OBSERVABLE_HPP */
