#ifndef RC4_H
#define RC4_H

#include"utils/global_defs.h"

void swap(unsigned char *, unsigned char *);
void KSA(char *, unsigned char *);
struct image *PRGA(struct image *, unsigned char *);
struct image *PRGA_decrypt(struct image *, unsigned char *);
struct image *encrypt_rc4(struct image *, void *);
struct image *decrypt_rc4(struct image *, void *);

#endif
