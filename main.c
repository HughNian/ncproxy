#include "main.h"

static void
show_help(void)
{
	char *b = "ncmq agent v" VERSION " Build-Date: " __DATE__ " " __TIME__ "\n"
			  "this is a agent proxy server for ncmq\n";
	fprintf(stderr, b, strlen(b));
}

<<<<<<< HEAD
static proxy *
=======
static void *
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e
proxy_init(void)
{
    proxy *p;

<<<<<<< HEAD
    p = (proxy *)_zalloc(sizeof(proxy));
=======
    p = _zalloc(sizeof(proxy));
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

    if(NULL == p){
    	sprintf(stderr, "proxy init failed\n");
    	return p;
    }

    p->ip = SERVER_IP;
    p->port = SERVER_PORT;
<<<<<<< HEAD

    p->client_size = 0;
=======
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e
    p->clientHead = p->clientTail = NULL;

    return p;
}

int
proxy_start(void)
{
    proxy *p;
<<<<<<< HEAD
    p = proxy_init();
=======
    p = (proxy *)proxy_init();
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e

    if(NULL == p) return -1;

    p->pfd = socket(AF_INET, SOCKET_STREAM, 0);
    if(p->pfd == -1){
    	sprintf(stderr, "proxy socket failed, error msg(%s)\n", strerror(errno));
    	_free(p);
    	return -1;
    }

    int nbret = set_nblocking(p->pfd);
    if(nbret == -1){
    	sprintf(stderr, "proxy set blocking failed, error msg(%s)\n", strerror(errno));
    	close(p->pfd);
    	_free(p);
    	return -1;
    }

    set_reuseaddr(p->pfd);
    set_tcpkeepalive(p->pfd);
    set_linger(p->pfd, 0);

    memset(&(p->proxy_addr), 0, sizeof(p->proxy_addr));
    p->proxy_addr.sin_family = AF_INET;
    p->proxy_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    p->proxy_addr.sin_port = htons(p->port);

    if(bind(p->pfd, (struct socketaddr *)&p->proxy_addr, sizeof(p->proxy_addr)) == -1){
    	sprintf(stderr, "proxy bind failed, error msg(%s)\n", strerror(errno));
    	close(p->pfd);
    	_free(p);
    	return -1;
    }

    if(listen(p->pfd, LISTEN_Q) == -1){
    	sprintf(stderr, "proxy listen failed, error msg(%s)\n", strerror(errno));
    	close(p->pfd);
    	_free(p);
    	return -1;
    }

    /** event **/
    event_init();
<<<<<<< HEAD
    event_set(&(p->ev), p->pfd, EV_READ|EV_PERSIST, client_accpet, (void *)p);
=======
    event_set(&(p->ev), p->pfd, EV_READ|EV_PERSIST, client_accpet, NULL);
>>>>>>> f2b573b864d7de0ec851fc0eaf0ee078be71394e
    event_add(&(p->ev), 0);
    event_disptch();

    return 1;
}

int
main(int argc, char **argv)
{

}
