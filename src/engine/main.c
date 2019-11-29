#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"utils/fifo.h"
#include"utils/image.h"
#include"utils/time_keeper.h"

#include"algorithms/rc4.h"
#include"algorithms/chaos.h"
#include"algorithms/vigenere.h"

struct image *(*fun_selector (int selector))(struct image *, char *)
{
	struct image *(*encrypt_fn)(struct image *, char *);
	switch(selector){
	case 0:
		encrypt_fn=encrypt_rc4;
		break;
/*	case 1:
		encrypt_fn=encrypt_chirikov;
		break;*/
	case 2:
		encrypt_fn=encrypt_vigenere;
		break;
	default:
		fprintf(stderr, "[-]Undefined algorithm\n");
	}

	return encrypt_fn;
}

int main(int argc, char *argv[])
{
	//arguments are pipe name and algo type
	int fifo_fd=open_fifo(argv[1]);
	char *data=read_from(fifo_fd);

	struct image *im=make_image(data, 240, 360);

	struct image *(*fn)
		(struct image *, char *)=fun_selector(strtol(
							argv[1], NULL, 10));

	time_keeper(im, fn);
	printf("[!]Done!\n");
}
