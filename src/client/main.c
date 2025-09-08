#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include "../common/serializer.h"
#define BUFFER_SIZE 250

int main(int argc,char *argv[]){
  if(argc!=3)
  {
    fprintf(stderr,"Se esperan dos argumentos\n");
    return -1;
  
  }
  const char *IP = argv[1];

  const char *PORT= argv[2];
  
  int sockfd = connect_to_server(IP,PORT);
  assert(sockfd>0 && "connect_to server failed" );
  struct pollfd fds[2];
  fds[0].fd = sockfd;
  fds[0].events = POLLIN;
  fds[1].fd = STDIN_FILENO;
  fds[1].events = POLLIN;
  printf("Connected to server!\n");
  printf("write something\n");
  int connection = 1;
  while(connection){
    int ret = poll(fds, 2, -1); 
    if(fds[0].revents & POLLIN) {
      char recv_buffer[250];
      int bytes = receive_client_message(sockfd, recv_buffer,BUFFER_SIZE);
      recv_buffer[bytes] = '\0';
      printf("%s",recv_buffer);
     }
     if(fds[1].revents & POLLIN){
       char send_buffer[250] = {0};
       fgets(send_buffer,sizeof(send_buffer),stdin);
       send_message(sockfd, send_buffer, strlen(send_buffer));
     }

  
  }
  
  return 0;

}

