#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "buffer.h"

#define PARAMS_SIZE 1024

typedef enum{
    SET,
    GET,
    DEL,
	ENQUEUE,
	DELQUEUE
} method;

typedef struct header{
	method type;
	uint16_t re_read:1;
	uint16_t re_write:1;

    const char *key; //可以是缓存的键值，队列名称，接口服务的名称等。
    size_t key_size;
    size_t key_len;
    buffer *params; //一些简单的入参

	size_t header_size;
	size_t body_size;
	time_t begin_time;
} header;

typedef struct request{
	int status;

	size_t size;
	size_t len;

	header *header;
	list *body;
} request;

typedef struct response{
	int status;

	size_t size;
	size_t len;

	header *header;
	list *body;
} response;

header *header_init(void);
void header_free(header *h);
/**request**/
request *request_init(void);
void parse_request(int cfd, request *req);
void request_free(request *req);

/**response**/
response *response_init(void);
void send_response(int cfd, void *resp);
void response_free(response *res);

#endif
