#include "../common/packet.h"
#pragma once
int connect_to_server (const char *IP,const char *PORT);
int send_message(int sockfd,void * msg_struct);
void fill_options_names(uint8_t *buffer,char *options[],int n_rooms);
int _send_message(int sockfd,void *msg_struct,size_t len_struct);
