#include "main.h"
#include "buffer.h"
#include "message.h"

request *
request_init(void)
{
	int blen;
	buffer *b;

    reqeuest *req;
    req = (request *)_zalloc(sizeof(*req));
    if(NULL == req) return NULL;

    req->header_body = header_body_init();
    if(NULL == req->header_body){
        _free(req);
        return NULL;
    }

    b = req->header_body->body->first;
	while(b){
		blen += b->len;
		b = b->next;
	}

    req->status = 0;
    req->size = req->header_body->header_size + req->header_body->body_size;
    req->len = req->header_body->params->len + blen;

    return req;
}

void
request_free(request *req)
{
    if(NULL == req) return;

    list_free(req->body, 0);

    header_body_free(req->header_body);

    _free(req);
}

/**
 * 解析请求
 * command: set,get,del,enqueue,dequeue
 *
 *
 */
void
request_parse(client *c)
{

}
