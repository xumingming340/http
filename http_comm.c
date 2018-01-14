#include "http_comm.h"

http_global_data_type g_http_data;


g_http_data *get_http_global_data()
{
	return &g_http_data;
}

void init_http_global_data()
{
	bzero(&g_http_data, sizeof(http_global_data_type));
}




