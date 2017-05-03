#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "main.h"
#include "client.h"
#include "message.h"
#include "server_pool.h"

typedef enum{
	CLIENT_TYPE,
	SERVER_TYPE
} conn_type;

struct conn{
	TAILQ_ENTRY(conn) conn_tqe;

	conn_type type;
    void *owner;

    int fd;
    int family;
    socket_t socket_len;
    struct sockaddr_in addr;

    request *req;
    response *resp;

    uint8_t status;
    uint16_t times;
}

TAILQ_HEAD(conn_tqh, conn);

void conn_init(void);
void conn_put_head(struct conn *conn);
struct conn *conn_get(void *owner, conn_type type);
struct conn *_conn_get(void *owner, conn_type type);
struct conn *conn_get_first(void);
struct conn *conn_get_last(void);
void conn_dinit(void);
void conn_free(struct conn *conn);

#endif
