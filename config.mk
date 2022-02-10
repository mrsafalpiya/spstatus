# Version
VERSION = 0.1

# Customize below to fit your system

# Paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# Flags
CFLAGS = -Wall -Wextra -Wno-deprecated-declarations -DVERSION=\"${VERSION}\"
ifeq ($(DEBUG),1)
	OPTS = -g
endif
LDFLAGS = -lX11

# Compiler and Linker
CC = cc
