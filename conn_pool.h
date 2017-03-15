#ifndef _CONN_POOL_H_
#define _CONN_POOL_H_

#include "main.h"
#include "client.h"
#include "message.h"
#include "server_pool.h"
#include "list.h"

#define CONN_MAX_NUMS 2048
#define CONN_MAX_TIMES 10
#define CONN_POOL_STEP 10

typedef struct conn_node{
    client *c;

    uint32_t conn_idx;
    uint16_t status:1;
    uint16_t times;

    struct list_head list;
} conn;

typedef struct conn_pool{
    size_t pool_size;
    size_t pool_len;
    int used;

    conn **conns;
    struct server_pool *servers;
    struct list_head list;
} conn_pool;


#endif
