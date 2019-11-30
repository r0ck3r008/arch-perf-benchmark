#include<math.h>

#include"utils/alloc.h"
#include"utils/image.h"

struct image *encrypt_chirikov(struct image *img, void *K)
{
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_cypher = alloc_image(h, w);
	int k=10000;

	int i_prime, j_prime;

	struct pixel *p_ct = img_cypher->data;
	struct pixel *p_pt = img->data;
	//p_ct[0].r = p_pt[0].r;
	for (int i = 0;i<h;i++){
		for (int j = 0;j<w;j++){
			if (i+j!= 0) {
				i_prime = (i-1+j-1) % h;
				j_prime = (int) (floor(
					j-1+k*sin(2*3.14159*i_prime/h))) % h;
				p_ct[i_prime*w + j_prime].r = p_pt[j + i*w].r;
			}
		}
	}

	return img_cypher;
}

struct image *decrypt_chirikov(struct image *img, void *K)
{
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_plain=alloc_image(h, w);
	int k=10000;

	int i_prime, j_prime;

	struct pixel *p_pt = img_plain->data;
	struct pixel *p_ct = img->data;
	p_pt[0].r = p_ct[0].g;
	for (int i = 0;i<h;i++){
		for (int j = 0;j<w;j++){
			if (i+j!= 0) {
				i_prime = ( int ) (floor(i-j+k*sin(
							2*M_PI*i/h))) % h;
				j_prime = ( int ) (floor(j-k*sin(
							2*M_PI*i/h)))%h;
				p_pt[i_prime*w + j_prime].r = p_ct[j + i*w].g;
			}
		}
	}
	return img_plain;
}
