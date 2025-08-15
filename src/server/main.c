#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <poll.h>

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
  struct poll pollfds[];
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
  int res_bind = bind(sock1,res->ai_addr,res->ai_addrlen); assert(res_bind!=-1);

  int res_lis = listen(sock1,backlog);
  

  if (res_lis == 0) {
    int listening = 1;
    char msg_buffer[200];
    addr_size = sizeof(their_addr);
    printf("Escuchando clientes en el puerto %s\n", PORT);
    int active_sockets[30];
    
    int socket_index = 0;

    while (listening) {
        // Accept espera el proximo mensaje que llegue al puerto y lo acepta
        int new_sock = accept(sock1, (struct sockaddr *)&their_addr, &addr_size);
        assert(new_sock != -1);
        printf("nuevo cliente conectado con el socket %d\n", new_sock);
        
        active_sockets[socket_index] = new_sock;
    
        int res_recv = recv(new_sock, msg_buffer, sizeof(msg_buffer), 0);
        assert(res_recv != -1);

        if (res_recv > 0) {
            msg_buffer[res_recv] = '\0';
            printf("el cliente con el id %d dice %s\n", new_sock, msg_buffer);
        }

        char msg[200];
        sprintf(msg, "Mensaje para el socket %d", new_sock);
        

        int res = send(new_sock, msg, strlen(msg), 0);
        assert(res != -1);

        if (res > 0) {
            printf("Mensaje enviado\n");
        }

        // Si quieres cerrar el socket después de enviar el mensaje
        // close(new_sock);
    }

} else {
    fprintf(stderr, "Listening failed");
    return -1;
}

freeaddrinfo(res);
close(new_sock);

return 0;
}

