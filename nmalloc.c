#include "nmalloc.h"

#define NMHEAD_SIZE sizeof(nmHead)

void
nminit(int mb)
{
	if (mb < 0) mb = 100;
	slabs_init(NMALLOC_POWER_BLOCK * mb);
}

void *
nmalloc(unsigned int size)
{
	void *point;
	unsigned char type;
	unsigned int allocsize;
	nmHead *head;

	allocsize = size + NMHEAD_SIZE;

	if (allocsize > NMALLOC_POWER_BLOCK) {
		type = NMALLOC_SYSTEM;
		point = malloc(allocsize);
	} else {
		type = NMALLOC_SLABS;
		point = slabs_alloc(allocsize);
	}

	if (!point)
		return NULL;

	head = (nmHead *)point;
	head->type = type;
	head->size = allocsize;

	return point + NMHEAD_SIZE;
}

void *
nrealloc(void *point, unsigned int nsize)
{
	void *original = (void *)(point - NMHEAD_SIZE);
	nmHead *head = (nmHead *)original;
	unsigned int orgsize, newsize;
	unsigned char orgtype, newtype;
	void *ret;

	orgtype = head->type;
	orgsize = head->size;
	newsize = nsize + NMHEAD_SIZE;

	if (orgtype == NMALLOC_SYSTEM) {
		ret = (void *)realloc(original, newsize);
		if (!ret)
			return NULL;
		newtype = NMALLOC_SYSTEM;
	} else {
		if (newsize > NMALLOC_POWER_BLOCK) {
			ret = malloc(newsize);
			if (!ret)
				return NULL;
			newtype = NMALLOC_SYSTEM;
		} else {
			ret = slabs_alloc(newsize);
			if (!ret)
				return NULL;
			newtype = NMALLOC_SLABS;
		}

		memcpy(ret + NMHEAD_SIZE, point, orgsize - NMHEAD_SIZE);
		slabs_free(original, orgsize);
	}

	head = (nmHead *)ret;
	head->type = newtype;
	head->size = newsize;

	return ret + NMHEAD_SIZE;
}

void
nfree(void *point)
{
	void *original;
	nmHead *head;

	original = (void *)(point - NMHEAD_SIZE);
	head = (nmHead *)original;

	if (head->type == NMALLOC_SYSTEM) {
		free(original);
	} else {
		slabs_free(original, head->size);
	}

	return;
}

char *
ntype(void *point)
{
	nmHead *head = (nmHead *)(point - NMHEAD_SIZE);

	switch (head->type) {
	case NMALLOC_SYSTEM:
		return "system";
	case NMALLOC_SLABS:
		return "slabs";
	}
}

unsigned int
nsize(void *point)
{
	nmHead *head = (nmHead *)(point - NMHEAD_SIZE);
	return head->size - NMHEAD_SIZE;
}
