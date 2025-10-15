#include "rooms.h"
#include <poll.h>
#pragma once

struct pollset{
  struct pollfd fds[100];
  int index;
  int size;

};


void init_pollset(struct pollset *poll_set, int sock_fd);
void process_recv_buffer(char buffer[200],Rooms *rooms,int sockfd);

int tcp_listener(const char * port,const char *ip);

void event_handler(int sock_fd);

void close_connection(struct pollset *poll_set,int current_index);



