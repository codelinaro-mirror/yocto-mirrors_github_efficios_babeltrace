/*
 * Copyright (c) 2023 Philippe Proulx <pproulx@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_CALL_HPP
#define BABELTRACE_CPP_COMMON_BT2C_CALL_HPP

#include <functional>
#include <utility>

namespace bt2c {

/*
 * Partial implementation ofINVOKE.
 *
 * As found in
 * <https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0312r1.html>.
 */

/*!
@brief
    Partial implementation of
    <a href="https://en.cppreference.com/w/cpp/utility/functional"><code>INVOKE</code></a>.

@ingroup common-cpp-bt2c

See
<a href="https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0312r1.html">Making Pointers to Members Callable</a>.

Use this function for any immediately invoked function expression
(IIFE), for example:

@code{.cpp}
const auto size = bt2c::call([this] {
    auto& sender = this->_curSender();

    if (sender.strategy() == Strategy::ACK) {
        return sender.strategySize();
    } else if (sender.strategy() == Strategy::NACK) {
        return 0;
    }

    return _mDefSize;
});
@endcode

@code{.cpp}
#include "cpp-common/bt2c/call.hpp"
@endcode

@param[in] func
    See <a href="https://en.cppreference.com/w/cpp/utility/functional"><code>INVOKE</code></a>.
@param[in] args
    See <a href="https://en.cppreference.com/w/cpp/utility/functional"><code>INVOKE</code></a>.

@returns
    See <a href="https://en.cppreference.com/w/cpp/utility/functional"><code>INVOKE</code></a>.
*/
template <typename FuncT, typename... ArgTs>
auto call(FuncT func, ArgTs&&...args) -> decltype(std::ref(func)(std::forward<ArgTs>(args)...))
{
    return std::ref(func)(std::forward<ArgTs>(args)...);
}

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_CALL_HPP */
