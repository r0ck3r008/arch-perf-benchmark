#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"utils/fifo.h"
#include"utils/image.h"
#include"utils/time_keeper.h"

#include"algorithms/rc4.h"
#include"algorithms/chaos.h"
#include"algorithms/vigenere.h"

void fun_selector(struct image *im, int selector)
{
	switch(selector){
	case 0:
		time_keeper(im, encrypt_rc4, decrypt_rc4);
		break;
	case 1:
		time_keeper(im, encrypt_chirikov, decrypt_chirikov);
		break;
	case 2:
		time_keeper(im, encrypt_vigenere, decrypt_vigenere);
		break;
	default:
		fprintf(stderr, "[-]Undefined algorithm\n");
	}
}

int main(int argc, char *argv[])
{
	//arguments are pipe name and algo type
	int fifo_fd=open_fifo(argv[1]);
	int height=strtol(argv[3], NULL, 10);
	int width=strtol(argv[4], NULL, 10);

	char *data=read_from(fifo_fd, height, width);

	struct image *im=make_image(data, height, width);

	fun_selector(im, strtol(argv[2], NULL, 10));

}
