#include<stdio.h>
#include<math.h>
#include<time.h>

#include"rc4.h"
#include"image.h"
#include"alloc.h"

void swap(unsigned char *a, unsigned char *b) {
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

struct image * PRGA(struct image *img, unsigned char *M)
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

struct image *encrypt_RC4(struct image *img)
{
	//define key and M to fill
	unsigned char M[256];

	char *K = "m2TJtI9hiJw74UAAuMSy0klQxC8N2GPlYK5EUFZ8SJ8yJX6uSRCGMfwO06ZqgPnYOR7au4rFZPGMkEz5AZosbbuTYuuCYlcN5bDSpK6ldW44cOaGWy9N2390ababcdcd";
	KSA(K,M);
	return PRGA(img,M);
}

void start(struct image *img)
{
	clock_t tic, toc;
        double cpu_time;
        double num_cycles;

	//RC4 encrypt
	int count = 60;
	double times[count];
	double sum = 0.0;
	for (int c = 0;c<count;c++){
		tic = clock();
		//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		//getrusage(RUSAGE_SELF, &before);

		struct image * cypher = encrypt_RC4(img);

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

	//write result
	struct image *cypher = encrypt_RC4(img);

	dealloc_image(img);
	dealloc_image(cypher);
}
