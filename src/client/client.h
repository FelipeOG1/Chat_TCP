#include "../common/packet.h"
#pragma once
int connect_to_server (const char *IP,const char *PORT);

int send_message(int sockfd,ClientMessage *msg, size_t len_msg);

int receive_client_message(int sockfd,char buffer[250],int buff_len);

int send_add_room(int sockfd, AddRoom *msg,size_t len_struct);
