#include<string.h>

#include"utils/image.h"
#include"utils/alloc.h"

struct image * encrypt_Vigenere(struct image *img, char *K)
{
	//first init empty target image
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_cypher=alloc_image(w,h);

	struct pixel *p_ct = img_cypher->data;
	struct pixel *p_pt = img->data;
	for (int i = 0;i<w*h;i++){
		p_ct[i].r = (((unsigned int)K[i % strlen(K)]) + p_pt[i].r)%256;
	}

	return img_cypher;
}
