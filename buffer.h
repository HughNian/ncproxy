#ifndef _BUFFER_H_
#define _BUFFER_H_

#define BUFFER_PIECE_SIZE 16

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

buffer *buffer_init(size_t);
void buffer_free(buffer *);
list *list_init(void);
void list_append(list *, buffer *);
void list_free(list *, int);

#endif
