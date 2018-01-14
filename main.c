#include "http_comm.h"
#include "unix_inc.h"


int main(int argc, char** argv)
{
	int c = 0;
	http_global_data_type *gdata = NULL;
		
	init_http_global_data();
	gdata = get_http_global_data();
	
	opterr = 0;
	while ((c = getopt(argc, argv, "csa:p:")) != EOF)
	{
		switch (c)
		{
			case 'c':
				gdata->type = CLIENT;
				printf("server type is client");
				break;
			case 's':
				gdata->type = SERVER;
				printf("server type is server");
				break;
			case 'a':
				strcpy(gdata->server_ip, optarg);
				printf("server ip is %s", gdata->server_ip);
				break;
			case 'p':
				gdata->server_port = atoi(optarg);
				printf("server port is %s", gdata->server_port);
				break;
			default:
				break;
		}
	}

	exit(0);
}

