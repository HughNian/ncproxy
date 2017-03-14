#include "client.h"

int
client_init(client **c)
{
    if(client_free_nums > 0){
        *c = client_frees[--client_free_nums];
    } else {
        *c = (client *)_zalloc(sizeof(client));

        if(NULL == *c){
            fprintf(stderr, "client init failed, error msg(%s)\n", strerror(errno));
            return -1;
        }
    }

    *c->socket_len = sizeof(*c->client_addr);
    *c->len  = 0;
    *c->used = 0;
    *c->cost_time = time(NULL);
    *c->req  = request_init();
    *c->resp = response_init();

    return 1;
}

//append to head
int
client_link(proxy *p, client *c)
{
    if(NULL == p || NULL == c)
        return -1;

    if(p->client_size = 0){
        c->prev = c->next = NULL;
        p->clientHead = p->clientTail = c;
    } else {
        c->prev = NULL;
        c->next = p->clientHead;
        p->clientHead->prev = c;

        p->clientHead = c;
    }

    p->client_size++;

    return 0;
}

int
client_unlink(proxy *p, client *c)
{
    if(NULL == p || NULL == c)
        return -1;

    if(c->prev)
        c->prev->next = c->next;
    else
        p->clientHead = c->next;

    if(c->next)
        c->next->prev = c->prev;
    else
        p->clientTail = c->prev;

    p->client_size--;

    return 0;
}

int
client_close(proxy *p, client *c)
{
    if(client_unlink(p, c) == -1){
        fprintf(stderr, "client unlink failed\n");
        return -1;
    }

    if(client_free_nums < CLIENT_MAX_FREE_SIZE){
        close(c->cfd);
        client_frees[client_free_nums++] = c;
    }
    else {
        close(c->cfd);
        _free(c);
    }

    return 1;
}

void
client_accept(const int pfd, const short which, void *arg)
{
    proxy *p;
    client *c;

    UNUSED(which);

    if(NULL == arg)
        return;

    p = (proxy *)arg;

    if(client_init(&c) == -1){
        fprintf(stderr, "client init failed\n");
        return;
    }

    c->cfd = accept(pfd, (struct sockaddr_in *)&(c->client_addr), &(c->socket_len));
    if(c->cfd == -1){
        fprintf(stderr, "client accept failed, error msg(%s)\n", strerror(errno));
        return;
    }

    if(client_conn_nums >= CLIENT_MAX_CONN_SIZE){
        fprintf(stderr, "client conn nums over the limit\n");

        const char *resp = "SERVER_ERROR OUT OF CONNECTION\n";
        write(c->cfd, resp, strlen(resp));
        close(c->cfd);
        return;
    }

    if(set_nblocking(c->cfd) == -1){
        fprintf(stderr, "client fd set nonblocking failed\n");
        close(c->cfd);
        return;
    }

    set_linger(c->cfd, 0);
    set_tcpkeepalive(c->cfd);
    set_reuseaddr(c->cfd);

    if(client_link(p, c) == -1){
        fprintf(stderr, "client list link failed\n");
        close(c->cfd);
        return -1;
    }

    /** event **/
    memset(&(c->ev), 0, sizeof(struct event));
    event_set(&(c->ev), c->cfd, EV_READ|EV_PERSIST, client_drive, (void *) c);
    event_add(&(c->ev), 0);
    c->ev_flags = EV_READ;

    return;
}
