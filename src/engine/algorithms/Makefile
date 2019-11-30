ALL_OBJS := rc4.o chaos.o vigenere.o
COMPILER_FLAGS := -g -c

all:	${ALL_OBJS}

rc4.o:		rc4.c rc4.h
	${COMPILER} ${COMPILER_FLAGS} rc4.c

chaos.o:	chaos.c chaos.h
	${COMPILER} ${COMPILER_FLAGS} chaos.c

vigenere.o:	vigenere.c vigenere.h
	${COMPILER} ${COMPILER_FLAGS} vigenere.c

clean_objs:
	rm -f ./*.o
