#include "connection.h"

int conn_count;
struct conn_tqh conns;

void
conn_init()
{
	conn_count = 0;
    TAILQ_INIT(&conns);
}

void
conn_put_head(struct conn *conn)
{
    if(NULL == conn) reutrn;

    TAILQ_INSERT_HEAD(&conns, conn, conn_tqe);
    conn_count++;

    return;
}

struct conn *
conn_get(void *owner, conn_type type)
{
	int find = 0;
	struct conn *conn;

	if(NULL == owner) return NULL;

    if(TAILQ_EMPTY(&conns)) return NULL;

    TAILQ_FOREACH(conn, &conns, conn_tqe){
    	if(type == conn->type && (memcmp(owner, conn->owner, sizeof(owner)) == 0)){
    		find = 1;
    		break;
    	}
    }

    if(find == 1){
    	TAILQ_REMOVE(&conns, conn, conn_tqe);
		conn_count--;

		return conn;
    }

    return NULL;
}

struct conn *
_conn_get(void *owner, conn_type type)
{
	struct conn *conn;

    conn = (struct conn*)_zalloc(sizeof(*conn));
    if(NULL == conn){
    	fpritnf(stderr, "conn malloc failed, [%s-%d]\n", __FILE__, __LINE__);
    	return NULL;
    }

    conn->type = type;
    conn->owner = owner;

    if(conn->type == CLIENT_TYPE)
    	conn->fd = owner->cfd;
    if(conn->type == SERVER_TYPE)
    	conn->fd = owner->sfd;

    conn->req  = owner->req;
    conn->resp = owner->resp;
    conn->status = 1;
    conn->times = time(NULL);

    return conn;
}

struct conn *
conn_get_first()
{
	struct conn *conn;

	conn = TAILQ_FIRST(&conns);
	TAILQ_REMOVE(&conns, conn, conn_tqe);
	if(NULL != conn)
		conn_count--;

	return conn;
}

struct conn *
conn_get_last()
{
   struct conn *conn;
   conn = TAILQ_LAST(&conns, conn_tqh);
   TAILQ_REMOVE(&conns, conn, conn_tqe);
   if(NULL != conn)
   		conn_count--;

   return conn;
}

void
conn_dinit()
{
	struct conn *conn,*nconn;

	if(conn_count == 0) return;

	for(conn = TAILQ_FIRST(&conns); conn != NULL;conn = nconn,conn_count--){
		nconn = TAILQ_NEXT(conn, conn_tqe);
		TAILQ_REMOVE(&conns, conn, conn_tqe);
		conn_free(conn);
	}

	return;
}

void
conn_free(struct conn *conn)
{
	if(NULL == conn) return;

	_free(conn);
}
