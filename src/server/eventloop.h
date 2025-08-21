#pragma once
#include <poll.h>
struct pollset{
  struct pollfd fds[100];
  int index;
  int size;

};

void start_event_loop(int sock_fd);

void event_loop(struct pollset * poll_fds);


