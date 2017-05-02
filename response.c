#include "main.h"
#include "buffer.h"
#include "message.h"

response *
response_init(void)
{
	int blen;
	buffer *b;

    response *res;
    res = _zalloc(sizeof(*res));
    if(NULL == res) return NULL;

    res->header_body = header_body_init();
    if(NULL == res->header_body){
        _free(res);
        return NULL;
    }

    b = res->header_body->body->first;
    while(b){
    	blen += b->len;
    	b = b->next;
    }

    res->status = 0;
    res->size = res->header_body->header_size + res->header_body->body_size;
    res->len = res->header_body->params->len + blen;

    return res;
}

void
response_free(response *res)
{
    if(NULL == res) return;

    list_free(res->body, 0);

    header_body_free(res->header_body);

    _free(res);
}
