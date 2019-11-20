#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include <math.h>

typedef struct {
    unsigned char r,g,b;
}Pixel;

typedef struct {
	unsigned int width, height;
    Pixel * data;
}Image;

unsigned int getImgWidth(const Image * i){ return i->width; }

unsigned int getImgHeight(const Image * i){ return i->height; }

void setPixel(int x, int y, Image ** data, const Pixel data_new)
{
  Pixel * p = (*data)->data;
  p[x + y * getImgWidth(*data)].r = data_new.r;
  p[x + y * getImgWidth(*data)].g = data_new.g;
  p[x + y * getImgWidth(*data)].b = data_new.b;

}

Pixel  getPixel(Image * i, int x, int y){ return i->data[getImgWidth(i)*y + x]; }

Image * new_image(int width, int height)
{
	Image * i = malloc(sizeof(Image));

	if(!i) {
		fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
	}
	i->width = width;
	i->height = height;

	i->data = malloc(sizeof(Pixel)*width*height);

	if(!i->data) {
		fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
	}
	return i;
}

void destroy_image(Image ** i)
{
	free(*i);
	free((*i)->data);
}

#define RGB 255

Image * read_PPM(const char *filename)
{
     char buff[16];
     Image * img;
     int ch;
     int rgb;

     //open and read image file
     FILE * fp = fopen(filename, "rb");
     if (!fp) {
          fprintf(stderr, "Unable to open file '%s'\n", filename);
          exit(1);
     }

     //read image format
     if (!fgets(buff, sizeof(buff), fp)) {
          perror(filename);
          fclose(fp);
          exit(1);
     }

    //parse magic number
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         fclose(fp);
         exit(1);
    }

    //parse comment
    ch = getc(fp);
    while (ch == '#') {
	while (getc(fp) != '\n') ;
		ch = getc(fp);
    }
	ungetc(ch, fp);

    int width, height;
    //parse width and height
    if (fscanf(fp, "%d %d", & width, & height) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //parse rgb depth
    if (fscanf(fp, "%d", &rgb) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n",
		 filename);
         fclose(fp);
         exit(1);
    }

    //check max rgb value correctness
    if (rgb !=  RGB) {
         fprintf(stderr, "'%s' is not a 24-bits image.\n", filename);
         fclose(fp);
         exit(1);
    }

	//create new image
    img = new_image(width, height);

    int bytes;
    //read image data from file and store inside pixel array
    if ((bytes=fread(img->data, 3 * img->width, img->height, fp)) != img->height){
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}

void write_PPM(const char * filename, Image * img)
{
    unsigned int w =  getImgWidth(img);
    unsigned int h =  getImgHeight(img);

    FILE * fp = fopen(filename, "wb");

    if (!fp) {
          fprintf(stderr, "Unable to open file '%s'\n", filename);
          exit(1);
    }

    fprintf(fp, "P6\n %d\n %d\n 255\n", w, h);

	fwrite(img->data, 3, getImgWidth(img) * getImgHeight(img), fp);

    fclose(fp);
}

void swap(unsigned char*a, unsigned char*b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Output M is a 256 byte state vector, initialized by K with 128 byte length
void KSA(char *K,unsigned char *M){
	char *T; //potential error initializing without length known
	for (int k = 0;k < 256;k++){
		M[k] = k;
		T[k] = K[k % 128]; //key has length of 128 bytes
	}
	
	int j = 0;
	for (int k = 0;k < 256;k++){
		j = (j + M[k] + T[k]) % 256;
		swap(&M[k],&M[j]); // this should swap them within M
	}
}

void PRGA(Image * img, unsigned char*M){ 
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	 
	int k,j = 0;
	
	Pixel * p = img->data;
	for (int i = 0;i < w*h;i++){
		
		k = (k+1) % 256;
		j = (j + M[k]) % 256;
		swap(&M[k],&M[j]);
		
		//apply key as xor with just red channel for now.
		p[i].r = ((M[k]+M[j]) % 256) ^ p[i].r;
	}
}

void encrypt_RC4(Image *img){
	//define key and M to fill  
	char *K;
	unsigned char *M; //TODO: see how they init S in example code 
	
	strncpy(K,"\xee\xf7\x62\x66\x74\x48\xb9\x43\x4d\xaf\xe5\xf7\xb2\x68\xf5\xec\xf6\x53\x46\xcd\x0e\x54\xcf\xb9\x9f\x9d\x6f\xca\x45\xec\x91\x15\x87\x12\x3f\x2c\xcc\xbc\xaf\x51\x54\xb8\x85\x86\xfb\x48\x3d\x6d\xf0\xad\xb1\xd4\x5f\x5c\x65\x0a\xc7\x14\x16\x03\xd2\x15\x5d\x90\xb9\x2b\x03\x06\xc4\xa2\xf7\xee\xce\x81\xd0\x25\x40\xec\xfc\xc7\xa9\x7e\xec\x28\x58\x02\xc8\xd1\x9c\x88\xfc\x49\x30\x1e\xb8\xce\xf4\x11\x62\x85\x75\x43\x2b\x3d\x3e\x4f\x95\xac\x43\x16\x36\xdc\xec\x96\xff\xf8\xe6\xbc\xa2\xb4\xd7\x5e\xcd\xad\xd8\x8a\x28\xd1",128);
	
	KSA(K,M);
	
	PRGA(img,M);
}
//same as encrypt 
void decrypt_RC4(Image *img){ 
	//define key and M to fill  
	char *K;
	unsigned char *M; //TODO: see how they init S in example code 
	
	strncpy(K,"\xee\xf7\x62\x66\x74\x48\xb9\x43\x4d\xaf\xe5\xf7\xb2\x68\xf5\xec\xf6\x53\x46\xcd\x0e\x54\xcf\xb9\x9f\x9d\x6f\xca\x45\xec\x91\x15\x87\x12\x3f\x2c\xcc\xbc\xaf\x51\x54\xb8\x85\x86\xfb\x48\x3d\x6d\xf0\xad\xb1\xd4\x5f\x5c\x65\x0a\xc7\x14\x16\x03\xd2\x15\x5d\x90\xb9\x2b\x03\x06\xc4\xa2\xf7\xee\xce\x81\xd0\x25\x40\xec\xfc\xc7\xa9\x7e\xec\x28\x58\x02\xc8\xd1\x9c\x88\xfc\x49\x30\x1e\xb8\xce\xf4\x11\x62\x85\x75\x43\x2b\x3d\x3e\x4f\x95\xac\x43\x16\x36\xdc\xec\x96\xff\xf8\xe6\xbc\xa2\xb4\xd7\x5e\xcd\xad\xd8\x8a\x28\xd1",128);
	
	KSA(K,M);
	
	PRGA(img,M);
}

Image * encrypt_Vigenere(Image *img, char* K){
	//first init empty target image 
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_cypher = new_image(w,h);
	
	Pixel * p_ct = img_cypher->data;
	Pixel * p_pt = img->data;
	for (int i = 0;i<w;i++){
		for (int j = 0;j<h;j++){
			p_ct[i + j*w].r = (K[j] + p_pt[i + j*w].r) % 256;
		}
	}
	
	
	return img_cypher;
}

Image * decrypt_Vigenere(Image *img, char* K){
	//first init empty target image 
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_plain = new_image(w,h);
	
	Pixel * p_pt = img_plain->data;
	Pixel * p_ct = img->data;
	for (int i = 0;i<w;i++){
		for (int j = 0;j<h;j++){
			p_pt[i + j*w].r = (K[j] - p_ct[i + j*w].r) % 256;
		}
	}
	
	
	return img_plain;
}

Image * encrypt_Chirikov(Image *img, int K){
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_cypher = new_image(w,h);
	
	int x_prime, y_prime;
	
	Pixel * p_ct = img_cypher->data;
	Pixel * p_pt = img->data;
	for (int i = 0;i<w;i++){
		for (int j = 0;j<h;j++){
			if (i+j!= 0) {
				x_prime = (i-1+j-1) % h;
				y_prime = (unsigned int ) (floor(j-1+K*sin(2*M_PI*x_prime/h))) % h;
				p_ct[x_prime + y_prime*w].r = p_pt[i + j*w].r;
			}
		}
	}
	
	return img_cypher;
}

Image * decrypt_Chirikov(Image *img, int K){
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_plain = new_image(w,h);
	
	int x_prime, y_prime;
	
	Pixel * p_pt = img_plain->data;
	Pixel * p_ct = img->data;
	for (int i = 0;i<w;i++){
		for (int j = 0;j<h;j++){
			if (i+j!= 0) {
				x_prime = (unsigned int ) (floor(i-j+K*sin(2*M_PI*i/h))) % h;
				y_prime = (unsigned int ) (floor(j-K*sin(2*M_PI*i/h))) % h;
				p_pt[x_prime + y_prime*w].r = p_ct[i + j*w].r;
			}
		}
	}
	
	return img_plain;
}

#define max(a,b) ((a>b)?(a):(b))

Image * emboss_image(Image * img)
{
    unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
    Image * emb_img = new_image(w, h);
    Pixel diff;
    Pixel upleft;
    Pixel curr;
    char maxDiff, tmp = 0;
    unsigned char v;
    int x, y;
    for(y=1; y<h; y++)
    {
        for(x=1; x<w; x++)
        {
		if(maxDiff > tmp)
			tmp = maxDiff;
		else
			maxDiff = tmp;
		upleft = getPixel(img, x-1,y-1);
		curr = getPixel(img,x,y);
		diff.r = curr.r - upleft.r;
		diff.g = curr.g - upleft.g;
		diff.b = curr.b - upleft.b;
		if((diff.r==diff.g && diff.r > diff.b)||
		   (diff.r==diff.b && diff.r > diff.g))
			maxDiff = diff.r;
		else
			maxDiff = max(diff.r,max(diff.g,diff.b));

		v = 128 + maxDiff;
		if(v<0)
			v=0;
		if(v>255)
			v=255;

		Pixel val2 = {v,v,v};
		setPixel(x,y,&emb_img,val2);
        }
    }
	return emb_img;
}


int main()
{

	//char filename[80] = "/home/naman/pic.ppm";

	//read image file
	Image * img = read_PPM("33.ppm");

	//TODO: switch this to an encoding function
	//apply emboss filter
	//Image * result = emboss_image(img);

	//write processed image to file
	write_PPM("result.ppm", img);

	//printf("Press any key to close.");
    //getchar();

//	destroy_image(&img);
//	destroy_image(&result);

	return 0;
}
