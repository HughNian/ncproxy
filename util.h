#ifndef _UTIL_H_
#define _UTIL_H_

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define INET4_ADDRSTRLEN (sizeof("255.255.255.255") - 1)
#define INET6_ADDRSTRLEN \
    (sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255") - 1)

#define CONFIG_FILE_PATH "config.ini"

//配置数组
typedef struct configs{
	int size;
	char **vals;
}configs;

int set_blocking(int);
int set_nonblocking(int);
int set_reuseaddr(int);
int set_tcpnodelay(int);
int set_linger(int, int);
int set_sndbuf(int, int);
int set_rcvbuf(int, int);
int set_tcpkeepalive(int);
int get_soerror(int);
int get_sndbuf(int);
int get_rcvbuf(int);
void read_config(char *, char *, void *);
void read_configs(char *, configs *);
void get_ip_port(char *, char *, char *);
char *remove_enter(char *);
char *remove_br(char *);

void *_alloc(size_t);
void *_zalloc(size_t);
void *_calloc(size_t, size_t);
void *_realloc(void *, size_t);
void _free(void *);

static inline unsigned int crc32(char *, unsigned int);
static inline int hashme(const char *);
#endif
