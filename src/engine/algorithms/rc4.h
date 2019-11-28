#ifndef RC4_H
#define RC4_H

#include"utils/global_defs.h"

void swap(unsigned char *, unsigned char *);
void KSA(char *, unsigned char *);
struct image *PRGA(struct image *, unsigned char *);
struct image *encrypt_RC4(struct image *, char *);

#endif
