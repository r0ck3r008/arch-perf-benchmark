#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

struct pixel
{
	unsigned char r, g, b;
};

struct image
{
	unsigned int width, height;
	struct pixel *data;
};

#endif
