gladedir = $(datadir)/atomato
glade_DATA = atomato-gui.glade

INCLUDES =					\
	-DATOMATO_GLADE_DIR="\"$(gladedir)\""	\
	$(ATOMATO_CFLAGS)			\
	$(ATOMATO_GUI_CFLAGS)

bin_PROGRAMS = atomato

atomato_SOURCES = 		\
	atomato-gui.h		\
	gui.c			\
	main.c			\
	main-window.c

atomato_LDADD = 				\
	$(ATOMATO_LIBS)				\
	$(ATOMATO_GUI_LIBS)			\
	$(top_builddir)/libatomato/libatomato.la
