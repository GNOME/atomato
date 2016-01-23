AM_CPPFLAGS = \
	-DGETTEXT_PACKAGE=\""$(GETTEXT_PACKAGE)"\"  \
	-DGNOMELOCALEDIR=\""$(localedir)"\" 	    \
	$(NULL)

bin_PROGRAMS = atomato

atomato_VALAFLAGS = \
	$(ATOMATO_VALAFLAGS)		\
	--target-glib=2.38			\
	--pkg gtk+-3.0				\
	--pkg gio-2.0				\
	--pkg gio-unix-2.0

atomato_SOURCES = 			\
	config.vapi				\
	library-list.vala		\
	main.vala				\
	main-window.vala		\
	workflow-editor.vala

atomato_LDADD = 				\
	$(ATOMATO_LIBS)				\
	$(ATOMATO_GUI_LIBS)

AM_CFLAGS = 				\
	$(ATOMATO_CFLAGS)		\
	$(ATOMATO_GUI_CFLAGS)
