#ifndef __HTTP_COMM__
#define __HTTP_COMM__

typedef enum _http_type 
{
	CLIENT = 0,
	SERVER,
} http_type;

typedef struct _http_global_data_typedef
{
	http_type type;				/* CLIENT or SERVER, default: CLIENT*/
	
	char server_ip[32];
	int server_port;
} http_global_data_typedef;

http_global_data_typedef *get_http_global_data();
void init_http_global_data();




#endif
