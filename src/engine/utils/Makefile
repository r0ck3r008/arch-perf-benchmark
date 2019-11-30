ALL_OBJS := time_keeper.o fifo.o alloc.o image.o
COMPILER_FLAGS := -g -c

all:	${ALL_OBJS}

time_keeper.o:	time_keeper.c time_keeper.h
	${COMPILER} ${COMPILER_FLAGS} time_keeper.c

fifo.o:		fifo.c fifo.h
	${COMPILER} ${COMPILER_FLAGS} fifo.c

alloc.o:	alloc.c alloc.h
	${COMPILER} ${COMPILER_FLAGS} alloc.c

image.o:	image.c image.h
	${COMPILER} ${COMPILER_FLAGS} image.c

clean_objs:
	rm -f ./*.o
