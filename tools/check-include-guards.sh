#!/bin/bash
#
# SPDX-License-Identifier: GPL-2.0-only
#
# SPDX-FileCopyrightText: 2024 EfficiOS Inc.

# Change directory to the root of the project, to make `find` simpler
cd "$(dirname "${BASH_SOURCE[0]}")/.." || exit 1

find src tests \
	\( -name '*.hpp' -or -name '*.h' \) \
	! -path '/.git/*' \
	! -path 'src/argpar/*' \
	! -path 'src/cpp-common/vendor/*' \
	! -path 'tests/plugins/flt.lttng-utils.debug-info/bins/tp.h' \
	! -path 'tests/plugins/flt.lttng-utils.debug-info/bins/libhello.h' \
	! -path 'tests/utils/catch2/*' \
	-print0 | xargs -P "$(nproc)" -n1 -t -0 tools/check-include-guard.py "$@"
