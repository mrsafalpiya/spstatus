# See LICENSE file for copyright and license details.

include config.mk

BIN  = spstatus
SRC  = ${BIN}.c
OBJ  = ${SRC:.c=.o}

all: options $(BIN)

options:
	@echo ${BIN} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} ${OPTS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

${BIN}: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ${BIN} ${OBJ} ${BIN}-${VERSION}.tar.gz config.h

dist: clean
	mkdir -p ${BIN}-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		${BIN}.1 ${SRC} ${BIN}.png ${BIN}-${VERSION}
	tar -cf ${BIN}-${VERSION}.tar ${BIN}-${VERSION}
	gzip ${BIN}-${VERSION}.tar
	rm -rf ${BIN}-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/${BIN}
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < ${BIN}.1 > ${DESTDIR}${MANPREFIX}/man1/${BIN}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${BIN}.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${BIN}\
		${DESTDIR}${MANPREFIX}/man1/${BIN}.1

run: ${BIN}
	./${BIN}

.PHONY: all options clean dist install uninstall
