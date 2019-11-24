#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include <math.h>
#include <time.h>

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

Image * PRGA(Image * img, unsigned char*M){ 
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_cypher = new_image(w,h);
	 
	int k,j = 0;
	
	Pixel * p_ct = img_cypher->data;
	Pixel * p_pt = img->data;
	for (int i = 0;i < w*h;i++){
		
		k = (k+1) % 256;
		j = (j + M[k]) % 256;
		swap(&M[k],&M[j]);
		
		//apply key as xor with just red channel for now.
		p_ct[i].r = ((M[k]+M[j]) % 256) ^ p_pt[i].r;
	}
	
	return img_cypher;
}

Image * encrypt_RC4(Image *img,char *K){
	//define key and M to fill  
	unsigned char M[256]; 
	
	KSA(K,M);
	
	return PRGA(img,M);
}

Image * encrypt_Vigenere(Image *img, char* K){
	//first init empty target image 
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_cypher = new_image(w,h);
	
	Pixel * p_ct = img_cypher->data;
	Pixel * p_pt = img->data;
	for (int i = 0;i<w*h;i++){
		p_ct[i].r = (((unsigned int)K[i % strlen(K)]) + p_pt[i].r) % 256;
	}
	
	
	return img_cypher;
}

Image * encrypt_Chirikov(Image *img, int K){
	unsigned int w = getImgWidth(img);
    unsigned int h = getImgHeight(img);
	Image *img_cypher = new_image(w,h);
	
	int i_prime, j_prime;
	
	Pixel * p_ct = img_cypher->data;
	Pixel * p_pt = img->data;
	//p_ct[0].r = p_pt[0].r;
	for (int i = 0;i<h;i++){
		for (int j = 0;j<w;j++){
			if (i+j!= 0) {
				i_prime = (i-1+j-1) % h;
				j_prime = (int) (floor(j-1+K*sin(2*3.14159*i_prime/h))) % h;
				p_ct[i_prime*w + j_prime].r = p_pt[j + i*w].r;
			}
		}
	}
	
	return img_cypher;
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
	
	clock_t tic, toc;
        double cpu_time;
        double num_cycles;

	
	//apply emboss filter
	//Image * result = emboss_image(img);
	
	//RC4 encrypt 
	//Image * img = read_PPM("33.ppm");
	// char *K = "m2TJtI9hiJw74UAAuMSy0klQxC8N2GPlYK5EUFZ8SJ8yJX6uSRCGMfwO06ZqgPnYOR7au4rFZPGMkEz5AZosbbuTYuuCYlcN5bDSpK6ldW44cOaGWy9N2390ababcdcd";
	// tic = clock();
	// Image * cypher = encrypt_RC4(img, K);
	// toc = clock();
	// num_cycles = (double) (toc - tic);
	// cpu_time =  num_cycles / CLOCKS_PER_SEC;
	// //write result 
	// write_PPM("encrypted.ppm", cypher);
	
	//Vignere encrypt 
	Image * img = read_PPM("./src_images/800_600.ppm");
	char *K = "zzacdbabababababayhbabzeezggabab";	
	
	int count = 60;
	double times[count];
	double sum = 0.0;
	for (int c = 0;c<count;c++){
		tic = clock();
		//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		//getrusage(RUSAGE_SELF, &before);

		Image * cypher = encrypt_Vigenere(img,K);

		toc = clock();
		//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
		//getrusage(RUSAGE_SELF, &after);	

		//clock_gettime() method
		//double cpu_time = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;    //microseconds
		//printf("CPU Time: %lf", cpu_time*.001);

		//clock() method 
		//num_cycles = (double) (toc - tic);
		cpu_time =  (double) (toc-tic)*1000.0/ CLOCKS_PER_SEC;
		times[c] = cpu_time; 	
		sum += cpu_time;
	}	
	double mean_cpu_time = sum/60;
	double std_cpu_time = 0.0;
	for (int c = 0;c<count;c++){
		std_cpu_time += pow(times[c] - mean_cpu_time, 2);
	}
	
	//printf("Cycles: %lf", num_cycles);
        printf("Average CPU Time: %lf \n", mean_cpu_time);
	printf("Std. Dev. CPU Time: %lf \n", sqrt(std_cpu_time/count) );
	Image * cypher = encrypt_Vigenere(img,K);
	write_PPM("./output/encrypted_vignere_800.ppm", cypher);
	
	//TODO: maybe loop over this for 60 images (one second of data) and get an average cpu time.
	//Chaos map encrypt
	//read image file
	//Image * img = read_PPM("./src_images/320_320.ppm");	
	//tic = clock();
	//Image * cypher = encrypt_Chirikov(img,10000);
	//toc = clock();
	//num_cycles = (long double) (toc - tic);
	//cpu_time =  num_cycles / CLOCKS_PER_SEC;
	//printf("Cycles: %Lf", num_cycles);
        //printf("CPU Time: %Lf", cpu_time);
	//printf("Clocks per sec",CLOCKS_PER_SEC);
	 //write result 
	//write_PPM("./output/encrypted_chaos_320.ppm", cypher);


	

//	destroy_image(&img);
//	destroy_image(&result);

	return 0;
}
