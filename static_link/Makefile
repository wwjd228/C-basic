CFLAGS=-fno-builtin
LDFLAGS=-static -T

CC=gcc
LD=ld

TARGET=tinyHelloWorld

OBJECT=${TARGET}.o

DEFAULT:${TARGET}

${TARGET}:${OBJECT}
	${CC] -c ${CFLAGS} $@.c
	${LD} ${LDFLAGS} $@.lds -o $@ $^
clean:
	rm ${OBJECT} ${TARGET}
