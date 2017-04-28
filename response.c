#include "main.h"
#include "buffer.h"
#include "message.h"

response *
response_init(void)
{
    response *res;
    res = _zalloc(sizeof(*res));
    if(NULL == res) return NULL;

    res->header = header_init();
    if(NULL == res->header){
        _free(res);
        return NULL;
    }

    res->body = list_init();
    if(NULL == res->body){
        header_free(res->header);
        _free(res);
        return NULL;
    }

    res->status = res->size = res->len = 0;

    return res;
}

void
response_free(response *res)
{
    if(NULL == res) return;

    list_free(res->body, 0);

    header_free(res->header);

    _free(res);
}