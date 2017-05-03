#ifndef _SERVER_POLL_H_
#define _SERVER_POLL_H_

#include "main.h"
#include "buffer.h"
#include "message.h"
#include "ketama.h"
#include "list.h"

#define SERVER_MAX_SIZE 2048
#define SERVER_POOL_STEP 10

typedef enum{
    MASTER = 1, //master server
    READ = 2   //read server
} server_type;

typedef struct server_node{
	int sfd;
    int server_idx;

    uint16_t status:1;
    uint16_t weight;
    sever_type type;

    char ip[16];
    int port;
    socket_t socket_len;
    struct sockadd_in server_addr;

    request *req;
    response *resp;

    struct event ev;

    struct list_head list;
} server;

typedef struct server_pool{
    size_t pool_size;
    size_t pool_len;
    int used;

    server **servers;
    struct list_head list;
} server_pool;

server_pool *server_pool_init(void);
void try_server_pool_resize(server_pool *sp);
int put_server_into_pool(server_pool *sp, server *s);

#endif
