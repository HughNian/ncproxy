#ifndef _CONN_POOL_H_
#define _CONN_POOL_H_

#include "main.h"
#include "client.h"
#include "message.h"
#include "server_pool.h"
#include "ketama.h"
#include "list.h"

#define CONN_MAX_SIZE 2048
#define CONN_MAX_TIMES 10
#define CONN_POOL_STEP 10

typedef struct conn_node{
    client *c;

    const char *key; //可以是缓存的键值，队列名称，接口服务的名称等。
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
    struct list_head list;
} conn_pool;

conn_pool *conn_pool_init(void);
int put_conn_into_pool(client *c);
int remove_conn();

#endif
