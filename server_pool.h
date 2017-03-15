#ifndef _SERVER_POLL_H_
#define _SERVER_POLL_H_

#include "main.h"
#include "buffer.h"
#include "message.h"
#include "list.h"

#define SERVER_POOL_STEP 10

typedef enum{
    WORK = 1, //work server
    BAK = 2   //backup server
} server_type;

typedef struct server_node{
    uint32_t server_idx;
    uint16_t status:1;
    uint16_t weight;
    sever_type type;

    struct event ev;

    request *req;
    response *resp;

    struct list_head list;
} server;

typedef struct server_pool{
    size_t pool_size;
    size_t pool_len;
    int used;

    char *ip;
    int port;
    struct sockadd_in server_addr;

    server **servers;
    struct list_head list;
} server_pool;

#endif