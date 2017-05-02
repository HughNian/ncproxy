#ifndef _CONN_POOL_H_
#define _CONN_POOL_H_

#include "main.h"
#include "client.h"
#include "message.h"
#include "server_pool.h"
#include "ketama.h"
#include "list.h"

#define CONN_MAX_SIZE 1024
#define CONN_MAX_TIMES 10
#define CONN_POOL_STEP 256

typedef struct conn_node{
    client *c;

    const char *key_name; //可以是缓存的键值，队列名称，接口服务的名称等，冗余header中的key
    int conn_idx;         //hash主键
    uint16_t status:1;    //链接状态
    uint16_t times;       //链接开始时间

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
void try_conn_pool_resize(conn_pool *);
int put_conn_into_pool(conn_pool *, client *);
int remove_conn(conn_pool *, client *);

#endif
