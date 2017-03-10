#ifndef _BUFFER_H_
#define _BUFFER_H_

typedef struct buffer{
	char *data;

	size_t used;
	size_t size;
	size_t len; //*ptr length
	struct buffer *next;
} buffer;

typedef struct list{
	struct buffer *first;
	struct buffer *last;
} list;

void *buffer_init(size_t size);

list *list_init(size_t size);

#endif
