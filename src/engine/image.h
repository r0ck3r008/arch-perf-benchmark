#ifndef IMAGE_H
#define IMAGE_H

#include"global_defs.h"

struct image *make_image(char *, int, int);
int get_img_width(struct image *);
int get_img_height(struct image *);

#endif
