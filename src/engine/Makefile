ALL_OBJS := main.o utils/{time_keeper.o,fifo.o,alloc.o,image.o} algorithms/{rc4.o,chaos.o,vigenere.o}
LINKER_FLAGS := -lm -o
COMPILER_FLAGS := -g -c

all:	engine clean_objs

engine: utils_objs algorithms_objs main.o
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} ./engine

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

utils_objs:
	make -C utils/

algorithms_objs:
	make -C algorithms/

clean_objs:
	rm -f ./*.o
	make -C utils/ clean_objs
	make -C algorithms/ clean_objs

clean:
	rm ./engine
