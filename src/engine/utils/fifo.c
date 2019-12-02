#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"

int open_fifo(char *fname)
{
	int fd;
	if((fd=open(fname, O_RDONLY))==-1){
		fprintf(stderr, "[-]Error in opening the fifo at %s: %s\n",
			fname, strerror(errno));
	}
}

char *read_from(int fd, int size_h, int size_w)
{
	int size=size_h*size_w*12;
	char *cmdr=alloc("char", size);
	char *buffer=alloc("char", 64);
	int exit=0;
	while(!exit){
		if(read(fd, buffer, sizeof(char)*64)==-1){
			fprintf(stderr, "[-]Error in reading the fifo: %s\n",
			strerror(errno));
			dealloc("char", size, cmdr);
			dealloc("char", 64, buffer);
			_exit(-1);
		}
		if(strlen(buffer)==0)
			exit=1;

		strncat(cmdr, buffer, sizeof(char)*64);
		explicit_bzero(buffer, sizeof(char)*64);
	}

	free(buffer);
	return cmdr;
}
