XHP_SHARED_DEPENDENCIES = libxhp.a
XHP_SHARED_LIBADD := libxhp.a ${XHP_SHARED_LIBADD}
$(srcdir)/ext.cpp: libxhp.a
libxhp.a: force
	$(MAKE) -f Makefile.xhp $@
force: ;
