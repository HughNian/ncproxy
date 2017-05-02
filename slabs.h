#ifndef __SALBS_H_
#define __SALBS_H_

unsigned int slabs_clsid(unsigned int);
void slabs_init(unsigned int);
void *slabs_alloc(unsigned int);
void slabs_free(void *, unsigned int);
char* slabs_stats(int *);

#endif
