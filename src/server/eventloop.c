#include <eventloop.h>
struct pollset{
  struct pollfd fds[100];
  int index;
  int size;

};

void init_pollset(struct pollset *poll_set, int sock_fd) {
  memset(poll_set->fds, 0, sizeof(poll_set->fds));
  poll_set->index = 0;
  poll_set->size = sizeof(poll_set->fds) / sizeof(poll_set->fds[0]);
  poll_set->fds[0].fd = sock_fd;
  poll_set->fds[0].events = POLLIN;
  poll_set->index++;
}

void start_event_loop(int sock_fd){
  struct pollset poll_set;
  init_pollset(&poll_set,sock_fd);
  event_loop(&poll_set);
  
}

void event_loop(struct pollset *poll_set){



}
