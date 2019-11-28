#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

struct image *alloc_image(int size_h, int size_w)
{
	struct image *im=alloc("struct image", 1);

	im->width=size_w;
	im->height=size_h;

	im->data=alloc("struct pixel", size_h*size_w);

	return im;
}

void dealloc_image(struct image *im)
{
	dealloc("struct pixel", im->height*im->width, im->data);
	dealloc("struct image", 1, im);
}

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")){
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	} else if(!strcmp(type, "struct pixel")){
		ret=malloc(sizeof(struct pixel)*size);
		explicit_bzero(ret, sizeof(struct pixel)*size);
	} else if(!strcmp(type, "struct image")){
		ret=malloc(sizeof(struct image)*size);
		explicit_bzero(ret, sizeof(struct image)*size);
	}

	if(ret==NULL){
		fprintf(stderr, "[-]Error in allocating %d bytes to %s type\n",
			size, type);
		_exit(-1);
	}
}

void dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char")){
		explicit_bzero(buf, sizeof(char)*size);
	} else if(!strcmp(type, "struct pixel")){
		explicit_bzero(buf, sizeof(struct pixel)*size);
	} else if(!strcmp(type, "struct image")){
		explicit_bzero(buf, sizeof(struct image)*size);
	}

	free(buf);
}
