#include "conn_pool.h"

conn_pool *
conn_pool_init(void)
{
    conn_pool *cp;

    cp = (conn_pool *)_zalloc(sizeof(*cp));

    if(NULL == cp){
        fprintf(stderr, "pool init failed\n");
        return NULL;
    }

    cp->conns = (conn **)_zalloc(sizeof(conn*) * CONN_POOL_STEP);
    if(NULL == cp->conns){
        fprintf(stderr, "conn pool's conns hash create failed\n");
        _free(cp);
        return NULL;
    }
    cp->pool_size += CONN_POOL_STEP;
    cp->pool_len = 0;
    cp->used = 0;

    cp->server_pool = server_pool_init();
    INIT_LIST_HEAD(&cp->list);

    return cp;
}

int
put_conn_into_pool(client *c)
{
    struct conn_node *cn;

    cn = (conn *)_zalloc(sizeof(*cn));
    if(NULL == cn){
        fprintf(stderr, "put conn into pool failed\n");
        return -1;
    }

    
}