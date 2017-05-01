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

	int  scount,cp_size;
	char count[10];
    conn_pool *cp;

    read_config("[servercount]", "count", count);
    scount = atoi(count);
    cp_size = scount ? scount * 2 : CONN_POOL_STEP;

    cp = (conn_pool *)_zalloc(sizeof(*cp));

    if(NULL == cp){
        fprintf(stderr, "conn pool init failed\n");
        return NULL;
    }

    cp->conns = (conn **)_zalloc(sizeof(conn*) * cp_size);
    if(NULL == cp->conns){
        fprintf(stderr, "conn pool's conns hash create failed\n");
        _free(cp);
        return NULL;
    }
    memset(cp->conns, 0, sizeof(conn*) * CONN_POOL_STEP);

    cp->pool_size += CONN_POOL_STEP;
    memset(cp->conns, 0, sizeof(conn*) * cp_size);

    if(use_ketama){
		conn_pool_ketama = (struct ketama *)calloc(sizeof(struct ketama), 1);
		if(NULL == conn_pool_ketama){
			fprintf(stderr, "conn pool ketama calloc failed, [%s-%d]\n", __FILE__, __LINE__);
			_free(cp->conns);
			_free(cp);
			return NULL;
		}

		conn_pool_ketama->count = cp_size;
		conn_pool_ketama->weight = (int *)calloc(sizeof(int), conn_pool_ketama->count);
		conn_pool_ketama->name = (char **)calloc(sizeof(char *), conn_pool_ketama->count);

		if(conn_pool_ketama->weight == NULL || conn_pool_ketama->name == NULL) {
			fprintf(stderr, "conn_pool_ketama weight name calloc failed, [%s-%d]\n", __FILE__, __LINE__);
			return NULL;
		}

		for(i = 0; i < conn_pool_ketama->count; i++){
			conn_pool_ketama->weight[i] = 100;
			conn_pool_ketama->totalweight += conn_pool_ketama->weight[i];
		}

		if(create_ketama(conn_pool_ketama, KETAMA_STEP))){
			fprintf(stderr, "create ketama failed, [%s-%d]\n", __FILE__, __LINE__);
			return NULL
		}
    }

    cp->pool_size = cp_size;
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

int
remove_conn(conn_pool *cp, client *c)
{
	struct list_head *pos;
	conn *cn;
	int conn_idx;
    const char *key_name;
    key_name = c->req->header->key;

    list_for_each(pos, &(cp->list)){
    	cn = list_entry(pos, conn, list);

    	if(strncmp(key_name, cn->key_name, strlen(key_name)) == 0){
    		if(use_ketama){
				conn_idx = get_pool(conn_pool_ketama, cn->key_name);
			} else {
				conn_idx = hashme(cn->key_name)%cp->pool_size;
			}

    		if(conn_idx == cn->conn_idx){
    			list_free(pos);
    			free(cn->key_name);
    			free(cn);
    		}
    	}
    }
    cp->used--;

    return 0;
}
