#include<math.h>

#include"utils/alloc.h"
#include"utils/image.h"

struct image *encrypt_chirikov(struct image *img, int K)
{
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_cypher = alloc_image(w,h);

	int i_prime, j_prime;

	struct pixel *p_ct = img_cypher->data;
	struct pixel *p_pt = img->data;
	//p_ct[0].r = p_pt[0].r;
	for (int i = 0;i<h;i++){
		for (int j = 0;j<w;j++){
			if (i+j!= 0) {
				i_prime = (i-1+j-1) % h;
				j_prime = (int) (floor(
					j-1+K*sin(2*3.14159*i_prime/h))) % h;
				p_ct[i_prime*w + j_prime].r = p_pt[j + i*w].r;
			}
		}
	}

	return img_cypher;
}
