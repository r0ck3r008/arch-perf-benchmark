#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

#include"global_defs.h"

void time_keeper(struct image *,
		 struct image *(*)(struct image *, void *));

#endif
