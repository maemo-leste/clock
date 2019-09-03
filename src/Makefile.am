lib_LTLIBRARIES = libclockcore0-0.la

libclockcore0_0_la_CFLAGS = $(CLOCK_CFLAGS) -I$(srcdir)/../include

libclockcore0_0_la_LDFLAGS = -Wl,--as-needed $(CLOCK_LIBS) -Wl,--no-undefined

libclockcore0_0_la_SOURCES = \
			     clockcore.c \
			     clockcore-citytime.c \
			     clockcore-gconf.c

MAINTAINERCLEANFILES = Makefile.in
