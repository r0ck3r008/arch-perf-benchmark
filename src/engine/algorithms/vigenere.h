#ifndef VIGNERE_H
#define VIGNERE_H

#include"utils/global_defs.h"

struct image *encrypt_vigenere(struct image *, void *);
struct image *decrypt_vigenere(struct image *, void *);

#endif
