#ifndef __SALBS_H_
#define __SALBS_H_

unsigned int slabs_clsid(unsigned int size);
void slabs_init(unsigned int limit);
void *slabs_alloc(unsigned int size);
void slabs_free(void *ptr, unsigned int size);
char* slabs_stats(int *buflen);

#endif
