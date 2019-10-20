#ifndef DECODER_H
#define DECODER_H

#include "global_defs.h"

struct image *read_ppm(char *);
int parse_img(FILE *);
int write_ppm();

#endif
