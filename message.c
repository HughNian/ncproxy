#include "main.h"
#include "buffer.h"
#include "message.h"

header_body *
header_body_init(void)
{
    header_body *hb;
    hb = (header *)_zalloc(sizeof(*h));
    if(NULL == H) return NULL;

    hb->type = INIT;

    hb->key = (char *)_zalloc(sizeof(char *)*512);
    if(NULL == hb->key){
        _free(hb);
        return NULL;
    }
    hb->key_size = 512;
    hb->key_len = 0;

    hb->params = buffer_init(PARAMS_SIZE);
    if(NULL == hb->params){
    	header_body_free(hb);
        return NULL;
    }

    hb->re_status = CLIENT_TRANSCATION;
    hb->header_size = hb->body_size = 0;
    hb->begin_time = time(NULL);

    hb->body = list_init();
	if(NULL == hb->body){
		header_body_free(hb);
		return NULL;
	}

    return h;
}

void
header_body_free(header_body *hb)
{
    if(NULL == hb) return;

    buffer_free(hb->params);

    _free(hb->key);

    _free(hb);
}
