#ifndef ALLOC_H
#define ALLOC_H

#include"global_defs.h"

struct image *alloc_image(int, int);
void dealloc_image(struct image *);
void *alloc(char *, int);
void dealloc(char *, int, void *);

#endif
