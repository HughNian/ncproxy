#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "buffer.h"

typedef enum{
    SET,
    GET,
    DEL,
	ENQUEUE,
	DELQUEUE
} method;

typedef struct header{
	method type:1;
	int re_read:1;

	size_t header_size;
	size_t body_size;
	time_t begin_time;
} header;

typedef struct request{
	int type;

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

/**request**/
int request_init();
int parse_command(request *req);

/**response**/
int response_init();
int send_response(void *resp);

#endif
