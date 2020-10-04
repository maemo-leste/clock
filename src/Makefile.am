lib_LTLIBRARIES = libclockcore0.la

libclockcore0_la_CFLAGS = $(CLOCK_CFLAGS) -I$(srcdir)/../include

libclockcore0_la_LDFLAGS = -Wl,--as-needed $(CLOCK_LIBS) -Wl,--no-undefined

libclockcore0_la_SOURCES = \
			     clockcore.c \
			     clockcore-citytime.c \
			     clockcore-cities.c \
			     clockcore-gconf.c

MAINTAINERCLEANFILES = Makefile.in
