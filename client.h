#ifndef _CLIENT_H_
#define _CLIENT_H_

typedef struct client{
    int cfd;

    struct sockadd_in client_addr;

    size_t len;
    size_t size;
    size_t used;
    time_t cost_time;

    struct client *prev;
    struct client *next;
} client;

#endif
