#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "buffer.h"

#define PARAMS_SIZE 1024

typedef enum{
	INIT,
    SET,
    GET,
    DEL,
	ENQUEUE,
	DELQUEUE,
	RETURN
} method;

typedef enum{
	CLIENT_TRANSCATION,
	CLIENT_REREAD,
	CLIENT_REWRITE
} header_status;

typedef struct header_body{
	method type;
	header_status re_status;

    const char *key; //可以是缓存的键值，队列名称，接口服务的名称等。
    size_t key_size;
    size_t key_len;
    buffer *params; //header内容

	size_t header_size;
	size_t body_size;
	time_t begin_time;

	list *body;
} header_body;

typedef struct request{
	int status;

	size_t size;
	size_t len;

	header_body *header_body;
} request;

typedef struct response{
	int status;

	size_t size;
	size_t len;

	header_body *header_body;
} response;

header_body *header_body_init(void);
void header_body_free(header *);
/**request**/
request *request_init(void);
void request_parse(client *);
void request_free(request *);

/**response**/
response *response_init(void);
void send_response(int, void *);
void response_free(response *);

#endif
