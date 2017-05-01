#include "server_pool.h"

server_pool *
server_pool_init(void)
{
    server_pool *sp;

    sp = (server_pool *)_zalloc(sizeof(*sp));

    if(NULL == sp){
    	fprintf(stderr, "server pool init failed\n");
    	return NULL;
    }


}
