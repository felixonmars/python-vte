
EXTRA_DIST = iso2022.txt


# The library

headerdir = $(includedir)/deepinvte-$(DEEPINVTE_API_VERSION)/deepinvte
header_HEADERS = pty.h reaper.h deepinvte.h deepinvteaccess.h deepinvtepty.h deepinvtetypebuiltins.h deepinvteversion.h deepinvtedeprecated.h

lib_LTLIBRARIES = libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@.la

EXTRA_libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_SOURCES = \
	genkeysyms.py \
	keysyms.c \
	marshal.list \
	mkunitables.sh \
	unitable.CNS11643 \
	unitable.CP437 \
	unitable.GB12345 \
	unitable.GB2312 \
	unitable.JIS0201 \
	unitable.JIS0208 \
	unitable.JIS0212 \
	unitable.KSX1001 \
	deepinvteseq-2.gperf \
	deepinvteseq-2.c \
	deepinvteseq-n.gperf \
	deepinvteseq-n.c \
	deepinvtetypebuiltins.c.template \
	deepinvtetypebuiltins.h.template \
	$(NULL)

libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_SOURCES = \
	buffer.h \
	caps.c \
	caps.h \
	debug.c \
	debug.h \
	iso2022.c \
	iso2022.h \
	keymap.c \
	keymap.h \
	marshal.c \
	marshal.h \
	matcher.c \
	matcher.h \
	pty.c \
	pty.h \
	reaper.c \
	reaper.h \
	ring.c \
	ring.h \
	table.c \
	table.h \
	trie.c \
	trie.h \
	deepinvte.c \
	deepinvte.h \
	deepinvte-gtk-compat.h \
	deepinvte-private.h \
	deepinvteaccess.c \
	deepinvteaccess.h \
	deepinvtebg.c \
	deepinvtebg.h \
	deepinvteconv.c \
	deepinvteconv.h \
	deepinvtedraw.c \
	deepinvtedraw.h \
	deepinvtedeprecated.h \
	deepinvteint.h \
	deepinvtepty.h \
	deepinvtepty-private.h \
	deepinvteregex.c \
	deepinvteregex.h \
	deepinvterowdata.c \
	deepinvterowdata.h \
	deepinvteseq.c \
	deepinvteseq-list.h \
	deepinvtestream.c \
	deepinvtestream.h \
	deepinvtestream-base.h \
	deepinvtestream-file.h \
	deepinvtestream-mem.h \
	deepinvtetc.c \
	deepinvtetc.h \
	deepinvtetree.c \
	deepinvtetree.h \
	deepinvtetypebuiltins.c \
	deepinvtetypebuiltins.h \
	deepinvteunistr.c \
	deepinvteunistr.h \
	deepinvteversion.h
	$(NULL)

libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_CPPFLAGS = \
	-DG_LOG_DOMAIN=\"Deepinvte-$(DEEPINVTE_API_VERSION)\" \
 	-DDATADIR='"$(datadir)"' \
	-DLIBEXECDIR='"$(libexecdir)"' \
	-DLOCALEDIR='"$(localedir)"' \
	-DTERMCAPDIR='"$(pkgdatadir)/termcap-$(DEEPINVTE_API_VERSION)"' \
	-DDEEPINVTE_COMPILATION \
	$(AM_CPPFLAGS)

libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_CFLAGS = $(DEEPINVTE_CFLAGS) $(AM_CFLAGS)
libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_LIBADD = $(DEEPINVTE_LIBS)
libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_la_LDFLAGS = \
  $(DEEPINVTE_LDFLAGS) \
	-version-info $(LT_VERSION_INFO) \
	-export-symbols-regex "^deepinvte_terminal_.*|^deepinvte_pty_.*|^deepinvte_get_.*|^_deepinvte_pty_.*|^deepinvte_reaper_.*|_deepinvte_debug_.*" \
	@LIBTOOL_EXPORT_OPTIONS@ @LIBTOOL_FLAGS@ \
	$(AM_LDFLAGS)


# Generated sources

DEEPINVTESEQ_BUILTSOURCES = deepinvteseq-list.h deepinvteseq-2.c deepinvteseq-n.c
BUILT_SOURCES = marshal.c marshal.h deepinvtetypebuiltins.c deepinvtetypebuiltins.h $(DEEPINVTESEQ_BUILTSOURCES)
MAINTAINERCLEANFILES = $(DEEPINVTESEQ_BUILTSOURCES)
EXTRA_DIST += $(DEEPINVTESEQ_BUILTSOURCES)
CLEANFILES = marshal.c marshal.h deepinvtetypebuiltins.c deepinvtetypebuiltins.h stamp-deepinvtetypebuiltins.h

marshal.c: marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_deepinvte_marshal --header --body --internal $< > $@
	
marshal.h: marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_deepinvte_marshal --header --internal $< > $@

deepinvtetypebuiltins.h: stamp-deepinvtetypebuiltins.h
	@true
stamp-deepinvtetypebuiltins.h: deepinvtetypebuiltins.h.template deepinvte.h deepinvtepty.h deepinvtedeprecated.h
	$(AM_V_GEN) $(GLIB_MKENUMS) --template $< $(filter %.h,$^) > xgen-vtbh \
	&& (cmp -s xgen-vtbh deepinvtetypebuiltins.h || cp xgen-vtbh deepinvtetypebuiltins.h ) \
	&& rm -f xgen-vtbh \
	&& echo timestamp > $(@F)

deepinvtetypebuiltins.c: deepinvtetypebuiltins.c.template deepinvte.h deepinvtepty.h deepinvtedeprecated.h
	$(AM_V_GEN) $(GLIB_MKENUMS) --template $< $(filter %.h,$^) > xgen-vtbc \
	&& (cmp -s xgen-vtbc deepinvtetypebuiltins.c || cp xgen-vtbc deepinvtetypebuiltins.c ) \
	&& rm -f xgen-vtbc

deepinvteseq-2.c: deepinvteseq-2.gperf
	$(AM_V_GEN) $(top_srcdir)/missing --run gperf -m 100 --no-strlen $< > $@.tmp && \
	mv -f $@.tmp $@

deepinvteseq-n.c: deepinvteseq-n.gperf
	$(AM_V_GEN) $(top_srcdir)/missing --run gperf -m 100 $< > $@.tmp && \
	mv -f $@.tmp $@

deepinvteseq-list.h: deepinvteseq-2.gperf deepinvteseq-n.gperf
	$(AM_V_GEN) echo '/* Generated file.  Do not edit */' > $@.tmp && \
	cat $^ | grep -v '^#' | grep '\<DEEPINVTE_SEQUENCE_HANDLER\>'| sed 's/.*, //' | LANG=C sort -u >> $@.tmp && \
	mv -f $@.tmp $@


# deepinvte the application

bin_PROGRAMS = deepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@

deepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_SOURCES = deepinvteapp.c
deepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_CFLAGS = $(DEEPINVTE_CFLAGS)
deepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@_LDADD = libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@.la $(DEEPINVTE_LIBS)

# introspection

INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION

Deepinvte-@DEEPINVTE_API_VERSION@.gir: libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@.la
Deepinvte_@DEEPINVTE_API_VERSION_U@_gir_INCLUDES = Pango-1.0 Gdk-$(GTK_API_VERSION) Gtk-$(GTK_API_VERSION)
Deepinvte_@DEEPINVTE_API_VERSION_U@_gir_CFLAGS = $(DEEPINVTE_CFLAGS) -DDEEPINVTE_COMPILATION -I$(top_srcdir)
Deepinvte_@DEEPINVTE_API_VERSION_U@_gir_LIBS = libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@.la
Deepinvte_@DEEPINVTE_API_VERSION_U@_gir_FILES = \
	deepinvte.c \
	deepinvte.h \
	deepinvtepty.h \
	pty.c \
	deepinvtetypebuiltins.c \
	deepinvtetypebuiltins.h \
	$(NULL)

INTROSPECTION_GIRS += Deepinvte-$(DEEPINVTE_API_VERSION).gir

girdir = $(INTROSPECTION_GIRDIR)
nodist_gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(INTROSPECTION_TYPELIBDIR)
nodist_typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(nodist_gir_DATA) $(nodist_typelib_DATA)
endif


# Misc unit tests and utilities

noinst_PROGRAMS = interpret slowcat
noinst_SCRIPTS = decset osc window
EXTRA_DIST += $(noinst_SCRIPTS)

TEST_SH = check-doc-syntax.sh
EXTRA_DIST += $(TEST_SH)

check_PROGRAMS = dumpkeys iso2022 reaper reflect-text-view reflect-deepinvte mev ssfe table trie xticker deepinvteconv deepinvtetc
TESTS = table trie $(TEST_SH)

AM_CFLAGS = $(GLIB_CFLAGS)
LDADD = $(GLIB_LIBS)

reflect_text_view_CPPFLAGS = -DUSE_TEXT_VIEW
reflect_text_view_CFLAGS = $(DEEPINVTE_CFLAGS)
reflect_text_view_SOURCES = reflect.c
reflect_text_view_LDADD = $(DEEPINVTE_LIBS)

reflect_deepinvte_CPPFLAGS = -DUSE_DEEPINVTE
reflect_deepinvte_CFLAGS = $(DEEPINVTE_CFLAGS)
reflect_deepinvte_SOURCES = reflect.c
reflect_deepinvte_LDADD = libdeepinvte@DEEPINVTE_LIBRARY_SUFFIX_U@.la $(DEEPINVTE_LIBS)

interpret_SOURCES = \
	buffer.h \
	caps.c \
	caps.h \
	debug.c \
	debug.h \
	iso2022.c \
	iso2022.h \
	matcher.c \
	matcher.h \
	table.c \
	table.h \
	trie.c \
	trie.h \
	deepinvteconv.c \
	deepinvteconv.h \
	deepinvtetc.c \
	deepinvtetc.h \
	deepinvtetree.c \
	deepinvtetree.h \
	interpret.c
interpret_CPPFLAGS = \
 	-DINTERPRET_MAIN \
 	-DTERMCAPDIR='"$(pkgdatadir)/termcap-$(DEEPINVTE_API_VERSION)"'
interpret_CFLAGS = $(GTK_CFLAGS)
interpret_LDADD = $(GTK_LIBS)

iso2022_SOURCES = \
	buffer.h \
	caps.c \
	caps.h \
	debug.c \
	debug.h \
	iso2022.c \
	iso2022.h \
	matcher.c \
	matcher.h \
	table.c \
	table.h \
	trie.c \
	trie.h \
	deepinvteconv.c \
	deepinvteconv.h \
	deepinvtetc.c \
	deepinvtetc.h \
	deepinvtetree.c \
	deepinvtetree.h
iso2022_CPPFLAGS = -DISO2022_MAIN
iso2022_CFLAGS = $(GTK_CFLAGS)
iso2022_LDADD = $(GTK_LIBS)

slowcat_SOURCES = \
	slowcat.c

table_SOURCES = \
	buffer.h \
	caps.c \
	caps.h \
	debug.c \
	debug.h \
	matcher.c \
	matcher.h \
	table.c \
	table.h \
	trie.c \
	trie.h \
	deepinvteconv.c \
	deepinvteconv.h \
	deepinvtetc.c \
	deepinvtetc.h
table_CPPFLAGS = -DTABLE_MAIN
table_CFLAGS = $(DEEPINVTE_CFLAGS)
table_LDADD = $(DEEPINVTE_LIBS)

trie_SOURCES = \
	trie.c \
	trie.h \
	buffer.h \
	caps.c \
	caps.h \
	debug.c \
	debug.h \
	matcher.c \
	matcher.h \
	table.c \
	table.h \
	deepinvteconv.c \
	deepinvteconv.h \
	deepinvtetc.c \
	deepinvtetc.h 
trie_CPPFLAGS = -DTRIE_MAIN
trie_CFLAGS = $(DEEPINVTE_CFLAGS)
trie_LDADD = $(DEEPINVTE_LIBS)

deepinvtetc_SOURCES = deepinvtetc.c deepinvtetc.h debug.c debug.h
deepinvtetc_CPPFLAGS = -DTERMCAP_MAIN

reaper_SOURCES = reaper.c reaper.h debug.c debug.h marshal.c marshal.h
reaper_CPPFLAGS =  -DREAPER_MAIN -DLOCALEDIR='"$(localedir)"'

deepinvteconv_SOURCES = buffer.h debug.c debug.h deepinvteconv.c deepinvteconv.h
deepinvteconv_CPPFLAGS = -DDEEPINVTECONV_MAIN
deepinvteconv_CFLAGS = $(DEEPINVTE_CFLAGS)
deepinvteconv_LDADD = $(DEEPINVTE_LIBS)

dumpkeys_SOURCES = dumpkeys.c
mev_SOURCES = mev.c
ssfe_SOURCES = ssfe.c
xticker_SOURCES = xticker.c

#

-include $(top_srcdir)/git.mk
-include $(INTROSPECTION_MAKEFILE)
