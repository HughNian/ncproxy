#ifndef _CLIENT_H_
#define _CLIENT_H_

<<<<<<< HEAD
#define CLIENT_MAX_CONN_SIZE 2048
#define CLIENT_MAX_FREE_SIZE 512

static int client_conn_nums = 0;
static struct client *client_frees[CLIENT_MAX_FREE_SIZE];
static int client_free_nums = 0;
=======
#define CLIENT_MAX_SIZE 1024
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

typedef struct client{
    int cfd;
    struct event ev;
<<<<<<< HEAD
    int ev_flags;
=======
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

    struct sockadd_in client_addr;
    socket_t socket_len;

    size_t len;
    size_t used;
    time_t cost_time;

<<<<<<< HEAD
    request *req;
    response *resp;
=======
    struct client *client_conns[CLIENT_MAX_SIZE];
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

    struct client *prev;
    struct client *next;
} client;

<<<<<<< HEAD
int client_init(client **c);
int client_link(proxy *p, client *c);
int client_unlink(proxy *p, client *c);
int client_close(proxy *p, client *c);
void client_accept(const int pfd, const short which, void *arg);
void client_drive(const int cfd, const short which, void *arg);
=======
int client_init(void);
int client_accept(void);
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

#endif
