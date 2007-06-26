INCLUDES =		\
	$(ATOMATO_CFLAGS)

lib_LTLIBRARIES = libatomato.la

DBUS_ACTION_PROVIDER_SRC = dbus-action-provider.c dbus-action-provider.h

libatomato_la_SOURCES =			\
	$(DBUS_ACTION_PROVIDER_SRC)	\
	atomato-action-provider.c	\
	atomato-action-provider.h	\
	atomato.c			\
	atomato.h			\
	shell-action-provider.c		\
	shell-action-provider.h

libatomato_la_LIBADD =	\
	$(ATOMATO_LIBS)
