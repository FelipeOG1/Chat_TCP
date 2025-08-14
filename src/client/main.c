#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(int argc,char *argv[]){
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *dummy;
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  const char * PORT = "4000";
  int sock,new_sock;
  
  memset(&hints,0,sizeof(hints));
  
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  int add_res = getaddrinfo("localhost",PORT,&hints,&res);

  if (add_res<0){
    fprintf(stderr,"fallo");
    return -1;
  }
  int sock1 = socket(res ->ai_family,res->ai_socktype,res->ai_protocol);
  
  int res_con = connect(sock1,res->ai_addr,res->ai_addrlen);
  

  if(res_con == -1){
    fprintf(stderr,"Couldnt connect to server check server is listening");
    return -1;

  }
    
  // Enviar mensaje
 
    char buff[256];
    char message_buff[256];
      
    printf("Escribe un mensaje: ");
    fgets(message_buff, sizeof(message_buff), stdin);
    
    //strscpn retorna el indice de la ocurrencia del char.
    message_buff[strcspn(message_buff, "\n")] = '\0';

    send(sock1, message_buff, strlen(message_buff), 0);

  int n = recv(sock1, buff, sizeof(buff) -1, 0);
  if (n > 0) {
      
      buff[n] = '\0';
      
      printf("Servidor dice: %s\n", buff);
      printf("se recibieron un total de %d bytes",n);
  }

    


  close(sock1);
  freeaddrinfo(res);
  
    
  return 0;
}

