#include "rooms.h"
#pragma once

void process_recv_buffer(char buffer[200],Rooms *rooms,int sockfd);

int tcp_listener(const char * port,const char *ip);

void event_handler(int sock_fd);






