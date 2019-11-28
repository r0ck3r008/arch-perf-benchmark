#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"fifo.h"
#include"image.h"
#include"rc4.h"

int main(int argc, char *argv[])
{
	//arguments are pipe name and algo type
	int fifo_fd=open_fifo(argv[1]);
	char *data=read_from(fifo_fd);

	struct image *im=make_image(data, 240, 360);
	start(im);
	printf("[!]Done!\n");
}
