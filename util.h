#ifndef _UTIL_H_
#define _UTIL_H_

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define NC_INET4_ADDRSTRLEN (sizeof("255.255.255.255") - 1)
#define NC_INET6_ADDRSTRLEN \
    (sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255") - 1)

int set_blocking(int sd);
int set_nonblocking(int sd);
int set_reuseaddr(int sd);
int set_tcpnodelay(int sd);
int set_linger(int sd, int timeout);
int set_sndbuf(int sd, int size);
int set_rcvbuf(int sd, int size);
int set_tcpkeepalive(int sd);
int get_soerror(int sd);
int get_sndbuf(int sd);
int get_rcvbuf(int sd);

void *_alloc(size_t size);
void *_zalloc(size_t size);
void *_calloc(size_t nmemb, size_t size);
void *_realloc(void *ptr, size_t size);
void _free(void *ptr);

static inline unsigned int crc32(char *buf, unsigned int size);
static inline int hashme(char *str);
#endif
