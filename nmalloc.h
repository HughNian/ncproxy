#ifndef __NMALLOC_H__
#define __NMALLOC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slabs.h"

#define NMALLOC_SLABS  1
#define NMALLOC_SYSTEM 2
#define NMALLOC_POWER_BLOCK 1048576

typedef struct nmHead {
	unsigned char type;
	unsigned int  size;
} nmHead;

void nminit(int mb);
void *nmalloc(unsigned int size);
void *nrealloc(void *point, unsigned int nsize);
void nfree(void *point);
char *ntype(void *point);
unsigned int nsize(void *point);

#endif
