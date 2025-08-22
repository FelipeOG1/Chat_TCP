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
#include "serializer.h"
#define BACKLOG 20

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
  
  int opt = 1;
  int res_opt = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  if (res_opt == -1){
    fprintf(stderr,"Opt Failed");
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

//TODO: pass fds for reference to a client_handler
void event_handler(int sock_fd){
   struct pollset poll_set;
   init_pollset(&poll_set,sock_fd);
   
   while (1) {
    //Start listening to events
    int poll_count = poll(poll_set.fds, poll_set.index, -1);
    if (poll_count == -1) {
        perror("poll");
        exit(1);
    }
   if(poll_count>0){
   //Binded socket received a event
   if (poll_set.fds[0].revents & POLLIN){
        struct sockaddr_storage client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }
        printf("El cliente con el socket_descriptor %d se a conectado\n",client_fd);
        poll_set.fds[poll_set.index].fd = client_fd;
        poll_set.fds[poll_set.index].events = POLLIN;
        poll_set.index++;
    }else{
        //Client socket received a event
        for (int i = 1; i < poll_set.index; i++) {
          if (poll_set.fds[i].revents & POLLIN) {
            char buffer[200];
            int bytes = recv(poll_set.fds[i].fd, buffer, sizeof(buffer), 0);
            if (bytes == 0) {
              printf("El usuario con el socket descriptor %d se ha desconectado\n", poll_set.fds[i].fd);
              close(poll_set.fds[i].fd);
              poll_set.fds[i] = poll_set.fds[poll_set.index- 1];
              i--;
              poll_set.index--;
            }
            if (bytes > 0) {
              printf("se recibieron %d por parte de %d\n",bytes,poll_set.fds[i].fd);
              for (int j = 1; j < poll_set.index; j++) {
                if (poll_set.fds[j].fd == poll_set.fds[i].fd) continue;
                  int res_send = send(poll_set.fds[j].fd, buffer, bytes, 0);
                  if (res_send == -1) perror("send");
                  }
                }
            }
        }
    }
  }
}
  




} 
  
