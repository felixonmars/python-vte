EXTRA_DIST = deepinvte.defs pydeepinvte.pc.in deepinvte.override cat.py unrealize.py deepinvte-demo.py

if BUILD_PYTHON_MODULES

defsdir = $(datadir)/pygtk/2.0/defs
defs_DATA = deepinvte.defs

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pydeepinvte.pc

PYTHON_MODULES = deepinvtemodule.la

pythonsiteexecdir = $(pyexecdir)/gtk-2.0
pythonsiteexec_LTLIBRARIES = $(PYTHON_MODULES)

CLEANFILES = deepinvte.c

deepinvtemodule_la_SOURCES = deepinvtemodule.c
deepinvtemodule_la_CPPFLAGS = -I$(top_builddir)/src $(AM_CPPFLAGS)
deepinvtemodule_la_CFLAGS = $(DEEPINVTE_CFLAGS) $(X_CFLAGS) $(PYTHON_INCLUDES) $(PYGTK_CFLAGS) $(AM_CFLAGS)

# we do this to suport building with -Wl,-z,defs which errors on
# deepinvtemodule.so as we cannot include $(PYTHON_LIBS) due to bug 410986.
deepinvtemodule_la_LDFLAGS = -module -avoid-version -export-symbols-regex initdeepinvte $(PYTHON_LDFLAGS) $(AM_LDFLAGS)
deepinvtemodule_la_LIBADD = $(top_builddir)/src/libdeepinvte.la $(LIBS) $(PYGTK_LIBS) $(DEEPINVTE_LIBS) $(X_LIBS)
nodist_deepinvtemodule_la_SOURCES = deepinvte.c

deepinvte.c: deepinvte.defs deepinvte.override

.defs.c:
	$(AM_V_GEN) (cd $(srcdir) \
	 && $(PYGTK_CODEGEN) \
            --register $(PYGTK_DEFSDIR)/pango-types.defs \
            --register $(PYGTK_DEFSDIR)/gdk-types.defs \
            --register $(PYGTK_DEFSDIR)/gtk-types.defs \
            --override $*.override \
            --prefix py$* $*.defs) > gen-$*.c \
        && cp gen-$*.c $*.c \
        && rm -f gen-$*.c

endif

-include $(top_srcdir)/git.mk
