/*
 * Copyright (c) 2022 Francis Deslauriers <francis.deslauriers@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BABELTRACE_CPP_COMMON_BT2C_FILE_UTILS_HPP
#define BABELTRACE_CPP_COMMON_BT2C_FILE_UTILS_HPP

#include <cstdint>
#include <vector>

#include "c-string-view.hpp"

namespace bt2c {

class Logger;

/*!
@brief
    Returns the complete data of the file \bt_p{path}, logging with
    \bt_p{logger}.

@ingroup common-cpp-bt2c

On error, depending on \bt_p{fatalError}:

<dl>
  <dt>\c false
  <dd>Log with the debug level and throw NoSuchFileOrDirectoryError.

  <dt>\c true
  <dd>
    Log with the error level, append a cause to the error of the
    current thread, and throw NoSuchFileOrDirectoryError.
</dl>

@note
    You must use this function in libbabeltrace2 context because it
    appends causes to the error of the current thread before throwing
    on error.

@code{.cpp}
#include "cpp-common/bt2c/file-utils.hpp"
@endcode

@param[in] path
    Path of the file to read.
@param[in] logger
    Logger to use on error.
@param[in] fatalError
    \c true if any file reading error is to be considered as an error.

@returns
    Full data of \bt_p{path}.

@pre
    \bt_p{path} exists and is readable.
*/
std::vector<std::uint8_t> dataFromFile(const CStringView path, const Logger& logger,
                                       bool fatalError);

} /* namespace bt2c */

#endif /* BABELTRACE_CPP_COMMON_BT2C_FILE_UTILS_HPP */
