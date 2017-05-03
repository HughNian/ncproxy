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
void get_config(char *server_name, char *key, void *vals);
void get_configs(char *server_name, configs *cfs);
void get_ip_port(char *address, char *ip, char *port);
char *remove_enter(char *str);
char *remove_br(char *str);

void *_alloc(size_t size);
void *_zalloc(size_t size);
void *_calloc(size_t nmemb, size_t size);
void *_realloc(void *ptr, size_t size);
void _free(void *ptr);

static inline unsigned int crc32(char *, unsigned int);
static inline int hashme(const char *);
#endif
