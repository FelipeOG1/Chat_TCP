#include <stdint.h>
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
#include "../common/packet.h"
#include "rooms.h"
#define BACKLOG 20


void init_pollset(struct pollset *poll_set, int sock_fd) {
  poll_set->index = 0;
  poll_set->size = sizeof(poll_set->fds) / sizeof(poll_set->fds[0]);
  
  for (int i = 0; i<poll_set->size;i++){
    poll_set->fds[i].fd = -1;//ignore file descriptors
  }
  poll_set->fds[0].fd = sock_fd;
  poll_set->fds[0].events = POLLIN;
  poll_set->index++;//start index at 1 to start adding clients_sockets

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
 
void process_recv_buffer(char buffer[200],Rooms *rooms,int client_sockfd){
  uint8_t flag = *(uint8_t *)buffer;
  int send_response = -1;
  switch (flag){
  case FLAG_ISMESSAGE:
    ClientMessage cl = *(ClientMessage *)buffer;
    printf("mensaje recibido por parte de %s\n",cl.username);
    printf("mensaje:%s\n",cl.message);
    break;

  case FLAG_ISADD_ROOM:
    AddRoom new_room_msg = *(AddRoom *)buffer;
    add_room(rooms,&new_room_msg,client_sockfd);
    uint8_t add_room_flag = 0x02;
    send_response = send(client_sockfd,&add_room_flag,1,0);//ask for room names
    assert(send_response>0);
    break;
  case FLAG_ISSHOW_ROOM:
    
    printf("se recibio el flag de show rooms\n");
    if (rooms->n_rooms >0){
      send_response = send (client_sockfd,rooms->buffer,rooms->buffer_offset,0);
      assert(send_response>0);
    }else{
      uint8_t is_null_flag = 0x10;
      send_response  = send(client_sockfd,&is_null_flag,sizeof(is_null_flag),0);
    }
    break;
}
}


void close_connection(struct pollset *poll_set,int current_index){

/**
 * close_connection - Closes a socket and removes it from the poll set
 * @poll_set: Pointer to the server's main poll_set structure
 * @current_index: Index of the socket descriptor to remove from the poll set
 *
 * Calls `close()` on the socket descriptor located at @current_index.
 * If it is not the last descriptor in the poll set, the last socket
 * descriptor is moved into its position to keep the array compact.
 * If it is the last descriptor, the position is cleared and marked
 * as inactive (fd = -1).
 *
 */
  int user_socket = poll_set->fds[current_index].fd;
  close(poll_set->fds[current_index].fd);
  if (current_index != poll_set->index - 1){  
    poll_set->fds[current_index] = poll_set->fds[poll_set->index - 1];//move last fd to closed fd pos.			
  }else{
    poll_set->fds[current_index].fd = -1;
    poll_set->fds[current_index].events = 0;
    poll_set->fds[current_index].revents = 0;

  }
  poll_set->index--;
  printf("User with socket descriptor %d disconect\n",user_socket);
}

//TODO: pass fds for reference to a client_handler
void event_handler(int sock_fd){
   struct pollset poll_set;
   Rooms rooms;
   init_rooms(&rooms);
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
        for (int i = 1; i < poll_set.index; i++) {
          if (poll_set.fds[i].revents & POLLIN){
            char buffer[200];
            int bytes = recv(poll_set.fds[i].fd, buffer, sizeof(buffer), 0);
            if (bytes == 0) { //case bytes are 0 means user desconected
	      close_connection(&poll_set,i); 
             
            }
            if (bytes > 0){
	      int client_sockfd = poll_set.fds[i].fd;
              printf("se recibieron %d por parte de %d\n",bytes,poll_set.fds[i].fd);
	      process_recv_buffer(buffer,&rooms,client_sockfd);
             
                }
            }
        }
    }
  }
}
  




} 
  
