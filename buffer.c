#include "main.h"
#include "buffer.h"

buffer *
buffer_init(size_t size)
{
    buffer *b;

    if(size <= 0) return NULL;
    b = (buffer *)_zalloc(size);
    if(NULL == b) return NULL;

    b->size = size;
    size += BUFFER_PIECE_SIZE - (size % BUFFER_PIECE_SIZE);

    b->data = (char *)_zalloc(size);
    if(NULL == b->data){
        free(b);
        return NULL;
    }

    b->len = size;

    b->next = NULL;

    return b;
}

list *
list_init(void)
{
    list *l;
    l = (list *)_zalloc(sizeof(*l));
    if(NULL == l) return NULL;

    list->first = list->last = NULL;

    return l;
}

void
buffer_free(buffer *b)
{
    if(NULL == b) return;

    _free(b->data);
    _free(b);
}

void
list_free(list *l, keep_list)
{
    if(NULL == l) return;

    buffer *lb, *n;
    lb = l->first;
    while(lb){
        n = lb;
        buffer_free(lb);
        lb = n->next;
    }

    if(keep_list)
        list->first = list->last = NULL;
    else
        _free(l);

    return;
}

void
list_append(list *l, buffer *b)
{
    if(NULL == l || NULL == b) return;

    if(l->first){          //插入单向链表尾部
        l->last->next = b; //l->last 为旧的l->last，对next指针赋值
        l->last = b;       //给l->last赋值，新的l->last
    } else
        l->first = l->last = b;
}