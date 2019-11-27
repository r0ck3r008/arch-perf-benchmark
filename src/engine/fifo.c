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

char *read_from(int fd)
{
	int size=1000000;
	char *cmdr=alloc("char", size);
	char *buffer=alloc("char", 8);
	int exit=0;
	while(!exit){
		if(read(fd, buffer, sizeof(char)*8)==-1){
		fprintf(stderr, "[-]Error in reading the fifo: %s\n",
			strerror(errno));
		dealloc("char", 470000, cmdr);
		dealloc("char", 8, buffer);
		_exit(-1);
		}
		if(strlen(buffer)==0){
			printf("[!]Read compelete!\n");
			exit=1;
		}
		sprintf(cmdr, "%s%s", cmdr, buffer);
		explicit_bzero(buffer, sizeof(char)*8);
	}

	free(buffer);
	return cmdr;
}

/*char *read_from(int fd)
{
	int size=1000000;
	char *cmdr=alloc("char", size);
	if(read(fd, cmdr, sizeof(char)*size)==-1){
		fprintf(stderr, "[-]Error in reading: %s\n",
			strerror(errno));
		dealloc("char", 500000, cmdr);
		_exit(-1);
	}

	return cmdr;
}*/
