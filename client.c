#include "client.h"

int
client_init(client *c)
{
    c = (client *)_zalloc(sizeof(*c));

    if(NULL == c){
        fprintf(stderr, "client init failed, error msg(%s)\n", strerror(errno));
        return -1;
    }

    c->len = 0;
    c->size = 0;
    c->used = 0;
    c->cost_time = time(NULL);
}
