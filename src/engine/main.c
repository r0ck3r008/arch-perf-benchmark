#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"utils/fifo.h"
#include"utils/image.h"
#include"utils/time_keeper.h"

void fun_selector(int selector)
{

}

int main(int argc, char *argv[])
{
	//arguments are pipe name and algo type
	int fifo_fd=open_fifo(argv[1]);
	char *data=read_from(fifo_fd);

	struct image *im=make_image(data, 240, 360);
	time_keeper(im, NULL);
	printf("[!]Done!\n");
}
