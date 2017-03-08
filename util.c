#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

int
set_blocking(int sd)
{
    int flags;

    flags = fcntl(sd, F_GETFL, 0);
    if(flags < 0) return flags;

    return fcntl(sd, F_SETFL, flags & ~O_NONBLOCK);
}

int
set_nblocking(int sd)
{
    int flags;

    flags = fcntl(sd, F_GETFL, 0);
    if(flags < 0) return flags;

    return fcntl(sd, F_SETFL, flags | O_NONBLOCK);
}

int
set_reuseaddr(int sd)
{
	int reuse;
	socklen_t len;

	reuse = 1;
	len = sizeof(reuse);

	return setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &reuse, len);
}

int
set_tcpnodelay(int sd)
{
    int nodelay;
    socklen_t len;

    nodelay = 1;
    len = sizeof(nodelay);

    return setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, &nodelay, len);
}

int
set_linger(int sd, int timeout)
{
    struct linger linger;
    socklen_t len;

    linger.l_onoff = 1;
    linger.l_linger = timeout;

    len = sizeof(linger);

    return setsockopt(sd, SOL_SOCKET, SO_LINGER, &linger, len);
}

int
set_tcpkeepalive(int sd)
{
    int val = 1;
    return setsockopt(sd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val));
}

int
set_sndbuf(int sd, int size)
{
    socklen_t len;

    len = sizeof(size);

    return setsockopt(sd, SOL_SOCKET, SO_SNDBUF, &size, len);
}

int
set_rcvbuf(int sd, int size)
{
    socklen_t len;

    len = sizeof(size);

    return setsockopt(sd, SOL_SOCKET, SO_RCVBUF, &size, len);
}

int
get_soerror(int sd)
{
    int status, err;
    socklen_t len;

    err = 0;
    len = sizeof(err);

    status = getsockopt(sd, SOL_SOCKET, SO_ERROR, &err, &len);
    if (status == 0) {
        errno = err;
    }

    return status;
}

int
get_sndbuf(int sd)
{
    int status, size;
    socklen_t len;

    size = 0;
    len = sizeof(size);

    status = getsockopt(sd, SOL_SOCKET, SO_SNDBUF, &size, &len);
    if (status < 0) {
        return status;
    }

    return size;
}

int
get_rcvbuf(int sd)
{
    int status, size;
    socklen_t len;

    size = 0;
    len = sizeof(size);

    status = getsockopt(sd, SOL_SOCKET, SO_RCVBUF, &size, &len);
    if (status < 0) {
        return status;
    }

    return size;
}

void *
_alloc(size_t size)
{
    void *val;

    val = malloc(size);

    if(NULL == val)
    	fprintf(stderr, "malloc failed\n");

    return val;
}

void *
_zalloc(size_t size)
{
    void *val;
    val = _alloc(size);
    if(NULL != val)
    	memset(val, 0, size);

    return val;
}

void *
_calloc(size_t nmemb, size_t size)
{
	return _zalloc(nmemb*size);
}

void *
_realloc(void *ptr, size_t size)
{
    void *val;

    val = realloc(ptr, size);
    if(NULL == val)
    	fprintf(stderr, "realloc failed\r\n");

    return val;
}

void
_free(void *ptr)
{
	assert(ptr != NULL);
	free(ptr);
}
