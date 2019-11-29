#include<string.h>

#include"utils/image.h"
#include"utils/alloc.h"

struct image * encrypt_vigenere(struct image *img, void *K)
{
	//first init empty target image
	char *k=(char *)K;
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_cypher=alloc_image(w,h);

	struct pixel *p_ct = img_cypher->data;
	struct pixel *p_pt = img->data;
	for (int i = 0;i<w*h;i++){
		p_ct[i].r = (((unsigned int)k[i % strlen(k)]) + p_pt[i].r)%256;
	}

	return img_cypher;
}
