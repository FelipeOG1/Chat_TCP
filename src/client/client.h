#include "../common/packet.h"
#pragma once
int connect_to_server (const char *IP,const char *PORT);
int send_message(int sockfd,void * msg_struct);
int _send_message(int sockfd,void *msg_struct,size_t len_struct);
