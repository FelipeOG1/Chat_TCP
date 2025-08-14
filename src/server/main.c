#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#define backlog 20


int main(int argc,char *argv[]){
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *dummy;
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  const char * PORT = "4000";
  int sock,new_sock;
  const char * msg = "Mensaje para cliente";
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
 
  int res_bind = bind(sock1,res->ai_addr,res->ai_addrlen);
  assert(res_bind!=-1);

  int res_lis =listen(sock1,backlog);

  if (res_lis==0){
    int listening  = 1;
    char msg_buffer[200];
    addr_size = sizeof(their_addr);
    printf("Escuchando clientes en el puerto %s\n",PORT);
    while(listening){
   
        //Accept espera el proximo mensaje que llegue al puerto y lo acepta
        int new_sock = accept(sock1, (struct sockaddr *)&their_addr, &addr_size);
        assert(new_sock!=-1);
        
        int res_recv = recv(new_sock, msg_buffer, sizeof(msg_buffer), 0);
        //TODO: revisar el numero del socket descriptor si un usuario cierra el proceso cliente una y otra vez
        if (res_recv>0){
            
            msg_buffer[res_recv] = '\0';
            

            char terminado[] = "exit";
            
            printf("el cliente dice : %s\n",msg_buffer);
            
            if (strcmp(msg_buffer,terminado)==0){
            
                printf("El usuario desea terminar la conneccion\n");
                close(new_sock);
                exit(1);
            }
            
        }
        assert(res_recv!=-1);
              
        int res = send(new_sock,msg,strlen(msg),0);
        
        if (res>0){
            printf("Mensaje enviado\n");

        }

        assert(res !=-1);

    }
    
     
  }else{
    fprintf(stderr,"Listening failed");
    return -1;
  }
  
  freeaddrinfo(res);

    
  return 0;
}
