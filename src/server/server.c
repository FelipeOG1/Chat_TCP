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
#define BACKLOG 20



int tcp_listener(const char * ip,const char * port){
  struct addrinfo *res;
  struct addrinfo hints;

  memset(&hints,0,sizeof(hints));
  

  hints.ai_family = AF_INET;

  hints.ai_socktype = SOCK_STREAM;
  
  hints.ai_protocol = 0;
  
  int res_addrinfo = getaddrinfo(ip,port,&hints,&res);

  if(res_addrinfo == -1){
    fprintf(stderr,"addrinfo failed");

    exit(1);

  }      
  int sock_fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
  if(sock_fd == -1){
    fprintf(stderr,"sock failed");

    exit(1);

  }
  int res_bind = bind(sock_fd,res->ai_addr,res->ai_addrlen);
  
  if(res_bind == -1){
    fprintf(stderr,"Bind failed");
    exit(1);

  }
  
  int res_listen = listen(sock_fd,BACKLOG);
  printf("Listening into port %s\n",port);
  return sock_fd;
  
}

void event_handler(int sock_fd){

  




} 
  
