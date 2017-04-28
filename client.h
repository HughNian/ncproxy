#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "main.h"
#include "buffer.h"
#include "message.h"

#define CLIENT_MAX_CONN_SIZE 2048
#define CLIENT_MAX_FREE_SIZE 512

static int client_conn_nums = 0;
static struct client *client_frees[CLIENT_MAX_FREE_SIZE];
static int client_free_nums = 0;

typedef struct client{
    int cfd;
    struct event ev;
    int ev_flags;

    struct sockadd_in client_addr;
    socket_t socket_len;

    time_t cost_time;

    request *req;
    response *resp;

    struct client *prev;
    struct client *next;
} client;

int  client_init(client **c);
int  client_link(proxy *p, client *c);
int  client_unlink(proxy *p, client *c);
int  client_close(proxy *p, client *c);
void client_accept(const int pfd, const short which, void *arg);
void client_drive(const int cfd, const short which, void *arg);

#endif
