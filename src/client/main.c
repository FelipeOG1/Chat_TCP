#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/poll.h>
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

  //TODO:create a username and send every message with a usernme witch message_struct;
  printf("Connected to server!\n");
  char message[MAX_MESSAGE_LEN];
  char username[MAX_USERNAME_LEN];
  printf("Digite su nombre de usuario \n");
  fgets(username,sizeof(username),stdin);
  username[strlen(username)-1] = 0;
  printf("Bienvenido %s ahora puede escribir un mensaje \n",username);
  ClientMessage m;
  strncpy(m.username,username,MAX_USERNAME_LEN);
  m.is_message_flag = 0x01;
  message_deserializer(&m);
  int connection = 1;
  while(connection){
    int ret = poll(fds, 2, -1); 
    if(fds[0].revents & POLLIN){
      char recv_buffer[250];
      int bytes = receive_client_message(sockfd, recv_buffer,BUFFER_SIZE);
      recv_buffer[bytes] = '\0';
      printf("%s",recv_buffer);
     }
     if(fds[1].revents & POLLIN){
        char send_buffer[250] = {0};
	if (fgets(send_buffer,sizeof(send_buffer),stdin)!=NULL){
  	  strncpy(m.message,send_buffer,MAX_MESSAGE_LEN);
	  send_message(sockfd,&m,sizeof(ClientMessage));
	     	
	}
     }

  
  }
  
  return 0;

}

