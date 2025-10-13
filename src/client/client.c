#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int connect_to_server(const char *IP,const char *PORT)
{
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *dummy;
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  int sock,new_sock;
  memset(&hints,0,sizeof(hints)); 
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;
  int add_res = getaddrinfo(IP,PORT,&hints,&res);
  if (add_res<0){
    fprintf(stderr,"fallo\n");
    return -1;
  }

  int sock1 = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
  if(sock1<0){
    fprintf(stderr,"fALLO EL SOCKET\n");
  }
  
  int res_con = connect(sock1,res->ai_addr,res->ai_addrlen);

  if(res_con == -1){
    fprintf(stderr,"Couldnt connect to server check server is listening\n");
    return -1;

  }
  
  return sock1;

}

int _send_message(int sockfd,void * msg_struct,size_t len_struct)
{
  int send_res = send(sockfd,msg_struct,len_struct,0);
  if (send_res<0)
  {
    fprintf(stderr,"Fallo el send\n");
    return -1;
  }
  return send_res;
}

int send_message(int sockfd,void *msg_struct){
  uint8_t flag = *(uint8_t *)msg_struct;
  size_t len_struct = 0;
  switch (flag){
  case FLAG_ISMESSAGE:
    len_struct = sizeof(ClientMessage);
    break;
  case FLAG_ISADD_ROOM:
    len_struct = sizeof(AddRoom);
    break;
  case FLAG_ISJOIN_ROOM:
    len_struct = sizeof(JoinRoom);
    break;
  case FLAG_ISSHOW_ROOM:
    break;
 }

  int res = _send_message(sockfd,msg_struct,len_struct);
  return res;
}


void fill_options_names(uint8_t *buffer,char *options[],int n_rooms){
  int names_offset = 2;
  for (int i =0 ;i<n_rooms;i++){
    char *current_name = (char *)&buffer[names_offset];
    options[i] = current_name;
    names_offset += (int)strlen(current_name)+1;
  }
}
 
//TODO CREATE THE RECEIVE MESSAGE FROM SERVER FUNCTION;


