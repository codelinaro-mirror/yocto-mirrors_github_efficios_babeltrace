/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2010 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#ifndef BABELTRACE_COMMON_ALIGN_H
#define BABELTRACE_COMMON_ALIGN_H

#include "compat/compiler.h"
#include "compat/limits.h"

#define BT_ALIGN(x, a)		__BT_ALIGN_MASK(x, (__typeof__(x))(a) - 1)
#define __BT_ALIGN_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#define BT_ALIGN_FLOOR(x, a)	__BT_ALIGN_FLOOR_MASK(x, (__typeof__(x)) (a) - 1)
#define __BT_ALIGN_FLOOR_MASK(x, mask)	((x) & ~(mask))

#endif /* BABELTRACE_COMMON_ALIGN_H */
