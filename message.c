#include "main.h"
#include "buffer.h"
#include "message.h"

header *
header_init(void)
{
    header *h;
    h = (header *)_zalloc(sizeof(*h));
    if(NULL == H) return NULL;

    h->key = (char *)_zalloc(sizeof(char *)*512);
    if(NULL == h->key){
        _free(h);
        return NULL;
    }
    h->key_size = 512;
    h->key_len = 0;

    h->params = buffer_init(PARAMS_SIZE);
    if(NULL == h->params){
        _free(h->key);
        _free(h);
        return NULL;
    }

    h->re_read = h->re_write = 0;
    h->header_size = h->body_size = 0;
    h->begin_time = time(NULL);

    return h;
}

void
header_free(header *h)
{
    if(NULL == h) return;

    buffer_free(h->params);

    _free(h->key);

    _free(h);
}