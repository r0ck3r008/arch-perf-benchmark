#include<stdio.h>
#include<math.h>
#include<time.h>

#include"rc4.h"
#include"utils/image.h"
#include"utils/alloc.h"

void swap(unsigned char *a, unsigned char *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Output M is a 256 byte state vector, initialized by K with 128 byte length
void KSA(char *K, unsigned char *M)
{
	//char *T[256];
	for (int k = 0;k < 256;k++){
		M[k] = k;
		//T[k] = K[k % 128]; //key has length of 128 bytes
	}

	int j = 0;
	for (int k = 0;k < 256;k++){
		j = (j + M[k] + K[k % 128]) % 256;
		swap(&M[k],&M[j]); // this should swap them within M
	}
}

struct image *PRGA(struct image *img, unsigned char *M)
{
	unsigned int w = get_img_width(img);
	unsigned int h = get_img_height(img);
	struct image *img_cypher=alloc_image(w,h);

	int k,j = 0;

	struct pixel *p_ct = img_cypher->data;
	struct pixel *p_pt = img->data;
	for (int i = 0;i < w*h;i++){

		k = (k+1) % 256;
		j = (j + M[k]) % 256;
		swap(&M[k],&M[j]);

		//apply key as xor with just red channel for now.
		p_ct[i].r = ((M[k]+M[j]) % 256) ^ p_pt[i].r;
	}

	return img_cypher;
}

struct image *encrypt_RC4(struct image *img, char *K)
{
	//define key and M to fill
	unsigned char M[256];
	KSA(K,M);
	return PRGA(img,M);
}
