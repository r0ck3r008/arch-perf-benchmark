#include<stdio.h>
#include<math.h>
#include<time.h>

#include"time_keeper.h"
#include"algorithms/rc4.h"
#include"alloc.h"

//TODO Add function pointer as a way to dynamically call the algorithm
//TODO add the decryption
void time_keeper(struct image *img,
		struct image *(*encrypt_fn)(struct image *, void *),
		struct image *(*decrypt_fn)(struct image *, void *))
{
	struct image *cypher;
	char *K="m2TJtI9hiJw74UAAuMSy0klQxC8N2GPlYK5EUFZ8SJ8yJX6uSRCGMfwO06ZqgPnYOR7au4rFZPGMkEz5AZosbbuTYuuCYlcN5bDSpK6ldW44cOaGWy9N2390ababcdcd";
	clock_t tic, toc;
        double cpu_time_enc, cpu_time_dec;

	//encryption
	tic=clock();
	cypher=encrypt_fn(img, (void *)K);
	toc=clock();
	cpu_time_enc=(double) (toc-tic)*1000.0/ CLOCKS_PER_SEC;

	//decryption
	tic=clock();
	cypher=decrypt_fn(cypher, (void *)K);
	toc=clock();
	cpu_time_dec=(double) (toc-tic)*1000.0/ CLOCKS_PER_SEC;

	printf("%lf:%lf", cpu_time_enc, cpu_time_dec);

	dealloc_image(img);
	dealloc_image(cypher);
}
/*code for std dev and avg
 * double mean_cpu_time = sum/60;
	double std_cpu_time = 0.0;
	for (int c = 0;c<count;c++){
		std_cpu_time += pow(times[c] - mean_cpu_time, 2);
	}

        printf("Average CPU Time: %lf \n", mean_cpu_time);
	printf("Std. Dev. CPU Time: %lf \n", sqrt(std_cpu_time/count) );*/

