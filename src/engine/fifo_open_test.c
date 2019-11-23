#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int fd;
	if((fd=open(argv[0], O_WRONLY))==-1){
		fprintf(stderr, "[-]Error in opening the fifo at %s: %s\n",
			argv[0], strerror(errno));
	}

	close(fd);
}
