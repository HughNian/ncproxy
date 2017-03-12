#ifndef _CLIENT_H_
#define _CLIENT_H_

#define CLIENT_MAX_SIZE 1024

typedef struct client{
    int cfd;
    struct event ev;

    struct sockadd_in client_addr;
    socket_t socket_len;

    size_t len;
    size_t size;
    size_t used;
    time_t cost_time;

    struct client *client_conns[CLIENT_MAX_SIZE];

    struct client *prev;
    struct client *next;
} client;

int client_init(void);
int client_accept(void);

#endif
