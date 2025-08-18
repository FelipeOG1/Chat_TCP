#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <poll.h>
#include "server.h"
#define backlog 20


int main(int argc,char *argv[]){
  const char *IP = "localhost";
  const char *PORT = "3000";
  int socket_fd = tcp_listener(IP,PORT);
  event_handler(listener_socket);
  
  //TODO implement start_eventloop
  
  //start_event_loop(socket_fd);
    

  return 0;
}

