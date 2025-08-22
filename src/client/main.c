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
#define BUFFER_SIZE 250
struct pollfd fds[2];
fds[0].fd = sockfd;      // socket del servidor
fds[0].events = POLLIN;  // leer mensajes

fds[1].fd = STDIN_FILENO; // entrada estándar
fds[1].events = POLLIN;   // leer input del usuario

//TODO terminar cliente con poll;
int main(int argc,char *argv[]){
  if(argc!=3)
  {
    fprintf(stderr,"Se esperan dos argumentos\n");
    return -1;
  
  }
  const char *IP = argv[1];

  const char *PORT= argv[2];
  
  int sockfd = connect_to_server(IP,PORT);
  
  if (sockfd>0)
  {
    printf("Connected to server!\n");
    printf("write something\n");
    int connection = 1;
    while(connection)
    {
      int ret = poll(fds, 2, -1); 
      if(fds[0].revents & POLLIN) {
        char recv_buffer[250];
        receive_client_message(sockfd, recv_buffer,BUFFER_SIZE);
        printf("Server: %s", buffer);
      }
      if(fds[1].revents & POLLIN) {
        // hay input del usuario
        char send_buffer[250];
        fgets(buffer, sizeof(buffer), stdin);
        send_message(sockfd, buffer, strlen(send_buffer));
      }

    }

    printf("Conectado exitosamente a %s %s\n",IP,PORT);
   

  }

  return 0;

}

