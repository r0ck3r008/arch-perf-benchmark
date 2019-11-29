#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"

struct image *make_image(char *data, int size_h, int size_w)
{
	struct image *im=alloc_image(size_h, size_w);
	char *a=strtok(data, ";");
	for(int i=0; a!=NULL; i++){
		int buf[3];
		for(int j=0; j<3; j++){
			buf[j]=strtol(a, NULL, 10);
			a=strtok(NULL, ";");
		}
		im->data[i].r=buf[0];
		im->data[i].g=buf[1];
		im->data[i].b=buf[2];
	}

	return im;
}

int get_img_width(struct image *im)
{
	return im->width;
}

int get_img_height(struct image *im)
{
	return im->height;
}
