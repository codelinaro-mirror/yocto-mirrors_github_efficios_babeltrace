# SPDX-FileCopyrightText: 2024 EfficiOS Inc.
# SPDX-License-Identifier: MIT

all-local: doxygen-doc

@DX_RULES@

$(DX_DOCDIR)/$(PACKAGE).tag: \
	Doxyfile \
	style.css \
	all.dox \
	cpp.dox

MOSTLYCLEANFILES = $(DX_CLEANFILES)
EXTRA_DIST = \
	Doxyfile.in \
	style.css \
	all.dox \
	cpp.dox
