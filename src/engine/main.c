#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"fifo.h"
#include"alloc.h"

int main(int argc, char *argv[])
{
	//arguments are pipe name and algo type
	int fifo_fd=open_fifo(argv[1]);
	char *data=read_from(fifo_fd);
	printf("[!]Read\n");

	FILE *f=NULL;
	if((f=fopen(argv[2], "w"))==NULL){
		fprintf(stderr, "[-]Error in opening file at %s: %s\n",
			argv[1], strerror(errno));
		_exit(-1);
	}

	fprintf(f, "%s", data);

	dealloc("char", 1000000, data);
	fclose(f);
}
