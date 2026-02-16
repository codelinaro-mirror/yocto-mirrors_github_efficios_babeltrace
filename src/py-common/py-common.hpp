/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 EfficiOS Inc.
 */

#ifndef BABELTRACE_PY_COMMON_PY_COMMON_HPP
#define BABELTRACE_PY_COMMON_PY_COMMON_HPP

/* `Python.h` needs to be included before any system header. */
#include <Python.h>

#include <vector>

/*
 * Convert `py_str_list` a `PyList` of `PyUnicode`s, to an array of
 * `const char *`.
 *
 * The resulting array must be freed by the caller, but the strings
 * themselves must not, as they refer to the Python string objects.
 */
std::vector<const char *> btPyStrListToVector(PyObject *py_str_list);

#endif /* BABELTRACE_PY_COMMON_PY_COMMON_HPP */
