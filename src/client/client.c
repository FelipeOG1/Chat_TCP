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

int send_message(int sockfd,char buffer[250],int msg_len)
{
  int send_res = send(sockfd,buffer,msg_len,0);
  if (send_res<0)
  {
    fprintf(stderr,"Fallo el send\n");
    return -1;

  }
  return send_res;
}

int receive_client_message(int sockfd,char buffer[250],int buff_len)
{

  ssize_t bytes = recv(sockfd,buffer,buff_len,0);
  
  if (bytes<0)
  {
    fprintf(stderr,"Fallo el send\n");
    return -1;

  }
  

  return bytes;


}



