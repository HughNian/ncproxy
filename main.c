#include main.h

static void
show_help(void)
{
	char *b = "ncmq agent v" VERSION " Build-Date: " __DATE__ " " __TIME__ "\n"
			  "this is a agent proxy server for ncmq\n";
	fprintf(stderr, b, strlen(b));
}

static int
proxy_init(void)
{

}
