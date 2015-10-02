EXTRA_DIST = xterm xterm.baseline
termcapdir = $(pkgdatadir)/termcap-$(DEEPINVTE_API_VERSION)
termcap_DATA = xterm

if DEEPINVTE_DEFAULT_EMULATION
termcap_DATA += $(DEEPINVTE_DEFAULT_EMULATION)
$(DEEPINVTE_DEFAULT_EMULATION): xterm
	$(AM_V_GEN) $(SED) -e s,^xterm:,$(DEEPINVTE_DEFAULT_EMULATION):,g \
	    -e s,^xterm\|,$(DEEPINVTE_DEFAULT_EMULATION)\|,g $< > $@
endif

-include $(top_srcdir)/git.mk
