#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/queue.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <event.h>

#include "client.h"
#include "buffer.h"
#include "message.h"
#include "conn_pool.h"
#include "server_pool.h"
#include "ketama.h"
#include "nmalloc.h"
#include "util.h"

#define VERSION "0.1.1"
#define SERVER_IP "127.0.0.1"
#define CONF_FILE "conf.ini"
#define SERVER_PORT 21888
#define LISTEN_Q 1024
#define UNUSED(x) ( (void)(x) )

typedef struct proxy{
    int pfd;
    struct event ev;

    struct sockaddr_in proxy_addr;
    char ip[16];
    int port;

    size_t client_size;
    client *clientHead;
    client *clientTail;

    conn_pool *cp;  //连接池
    server_pool *sp; //服务池
} proxy;

