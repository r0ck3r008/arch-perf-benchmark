#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"
#include"decoder.h"

struct image *read_ppm(char *fname)
{
	//open file
	FILE *f=NULL;
	if((f=fopen(fname, "r"))==NULL){
		fprintf(stderr, "[-]Error in opening file %s: %s\n",
			fname, strerror(errno));
		_exit(-1);
	}

	if(!parse_img(f))
		goto exit;

exit:
	fclose(f);
}

int parse_img(FILE *f)
{
	//read 
}

int write_ppm()
{

}
