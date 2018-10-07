CFLAGS = -I include
all: cdecl cdecl-fsm
cdecl: cdecl.c
	gcc -o $@ $^ ${CFLAGS}
cdecl-fsm: cdecl-fsm.c
	gcc -o $@ $^ ${CFLAGS}
clean:
	rm cdecl cdecl-fsm
