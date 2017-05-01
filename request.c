#include "main.h"
#include "buffer.h"
#include "message.h"

request *
request_init(void)
{
    reqeuest *req;
    req = (request *)_zalloc(sizeof(*req));
    if(NULL == req) return NULL;

    req->header = header_init();
    if(NULL == req->header){
        _free(req);
        return NULL;
    }

    req->body = list_init();
    if(NULL == req->body){
        header_free(req->header);
        _free(req);
        return NULL;
    }

    req->status = req->size = req->len = 0;

    return req;
}

void
request_free(request *req)
{
    if(NULL == req) return;

    list_free(req->body, 0);

    header_free(req->header);

    _free(req);
}

//解析请求
void
request_parse(client *c)
{

}
