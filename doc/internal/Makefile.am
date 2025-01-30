# SPDX-FileCopyrightText: 2024 EfficiOS Inc.
# SPDX-License-Identifier: MIT

all-local: doxygen-doc

@DX_RULES@

$(DX_DOCDIR)/$(PACKAGE).tag: \
	Doxyfile \
	style.css \
	all.dox \
	cpp.dox \
	@top_srcdir@/src/compat/bitfield.h \
	@top_srcdir@/src/compat/compiler.h \
	@top_srcdir@/src/compat/endian.h \
	@top_srcdir@/src/compat/fcntl.h \
	@top_srcdir@/src/compat/limits.h \
	@top_srcdir@/src/compat/memstream.h \
	@top_srcdir@/src/compat/mman.h \
	@top_srcdir@/src/compat/socket.hpp \
	@top_srcdir@/src/compat/stdio.h \
	@top_srcdir@/src/compat/stdlib.h \
	@top_srcdir@/src/compat/time.h \
	@top_srcdir@/src/compat/unistd.h \
	@top_srcdir@/src/compat/utc.h

MOSTLYCLEANFILES = $(DX_CLEANFILES)
EXTRA_DIST = \
	Doxyfile.in \
	style.css \
	all.dox \
	cpp.dox
