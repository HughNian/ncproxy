#ifndef _SERVER_POLL_H_
#define _SERVER_POLL_H_

#include "main.h"
#include "message.h"
#include "list.h"

typedef struct server_node{
    uint32_t server_idx;

    struct sockadd_in server_addr;
    struct event ev;
    struct list_head list;
} server;

typedef struct server_pool{

    server **servers;
    struct list_head list;
} server_pool;

#endif