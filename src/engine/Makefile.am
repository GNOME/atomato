AM_CPPFLAGS = \
	-DGETTEXT_PACKAGE=\""$(GETTEXT_PACKAGE)"\"  \
	-DGNOMELOCALEDIR=\""$(localedir)"\" 	    \
	$(NULL)

lib_LTLIBRARIES = libatomato-engine

libatomato_engine_VALAFLAGS = \
	$(ATOMATO_VALAFLAGS)		\
	--target-glib=2.38			\
	--pkg gio-2.0				\
	--pkg gio-unix-2.0

libatomato_engine_SOURCES = 			\
	action.vala				\
	aggregate-action.vala			\
	conditional-action.vala			\
	loop-action.vala

libatomato_engine_LDADD = $(ATOMATO_LIBS)

AM_CFLAGS = $(ATOMATO_CFLAGS)
