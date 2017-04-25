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
    memset(cp->conns, 0, sizeof(conn*) * CONN_POOL_STEP);

    cp->pool_size += CONN_POOL_STEP;
    cp->pool_len = 0;
    cp->used = 0;

    INIT_LIST_HEAD(&cp->list);

    return cp;
}

int
put_conn_into_pool(conn_pool *cp, client *c)
{
    struct conn_node *cn;

    cn = (conn *)_zalloc(sizeof(*cn));
    if(NULL == cn){
        fprintf(stderr, "put conn into pool failed\n");
        return -1;
    }

    cn->c = c;
    cn->key_name = strdup(c->req->header->key);

    if(use_ketama){
        cn->conn_idx = get_pool(conn_pool_ketama, cn->key_name);
    } else {
        cn->conn_idx = hashme(cn->key_name)%cp->pool_size;
    }

    cn->status = 0;
    cn->times  = time(NULL);
    cn->req = request_init();
    cn->resp = response_init();

    list_add_tail(&cn->list, &cp->list);
    cp->conns[cn->conn_idx] = cn;
    cp->used++;

    try_conn_pool_resize(cp);

    return 0;
}

void
try_conn_pool_resize(conn_pool *cp)
{
    conn **new_conns;
    if(cp->used == cp->pool_size){
        new_conns = (conn **)_realloc(cp->conns, sizeof(conn*) * (cp->pool_size + CONN_POOL_STEP));
    }

    if(NULL == new_conns){
        fprintf(stderr, "conn pool conns realloc failed\n");
        return;
    } else {
        cp->conns = new_conns;
        cp->pool_size += CONN_POOL_STEP;
    }

    return;
}
