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
#include "interface.h"
#include "client.h"
#define BUFFER_SIZE 250

int main(int argc,char *argv[]){
  if(argc!=3)
  {
    fprintf(stderr,"Se esperan dos argumentos\n");
    return -1;
  
  }
  printf("me cago en todooo");
  const char *IP = argv[1];
  const char *PORT = argv[2];
  int sockfd = connect_to_server( IP, PORT);
  render_main_window(sockfd);
  return 0;
  struct pollfd fds[2];
  fds[0].fd = sockfd;
  fds[0].events = POLLIN;
  fds[1].fd = STDIN_FILENO;
  fds[1].events = POLLIN;

  printf("Connected to server!\n");
  char message[MAX_MESSAGE_LEN];
  char username[MAX_USERNAME_LEN];
  printf("Digite su nombre de usuario \n");
  //save username into struct
  fgets(username,sizeof(username),stdin);
  username[strlen(username)-1] = 0;
  ClientMessage client_message;
  strncpy(client_message.username,username,MAX_USERNAME_LEN);
  //Set proper flag to server cast to proper struct
  client_message.is_message_flag = 0x01;
  printf("Bienvenido %s ahora puede escribir un mensaje \n",username);
  int connection = 1;
  while(connection){
    int ret = poll(fds, 2, -1); 
    if(fds[0].revents & POLLIN){
      char recv_buffer[250];
      //int bytes = receive_client_message(sockfd, recv_buffer,BUFFER_SIZE);
      //recv_buffer[bytes] = '\0';
      //printf("%s",recv_buffer);
     }
     if(fds[1].revents & POLLIN){
        char send_buffer[250] = {0};
	if (fgets(send_buffer,sizeof(send_buffer),stdin)!=NULL){
  	  strncpy(client_message.message,send_buffer,MAX_MESSAGE_LEN);
	  //send_message(sockfd,&client_message,sizeof(ClientMessage));
	}
     }
 
  }
  
  return 0;

}

