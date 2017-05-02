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

void nminit(int);
void *nmalloc(unsigned int);
void *nrealloc(void *, unsigned int);
void nfree(void *);
char *ntype(void *);
unsigned int nsize(void *);

#endif
