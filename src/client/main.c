#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
int main(int argc,char *argv[]){
  if(argc!=3)
  {
    fprintf(stderr,"Se esperan dos argumentos\n");
    return -1;
  
  }
  const char *IP = argv[1];

  const char *PORT= argv[2];
  
  int res_connect = connect_to_server(IP,PORT);
  
  if (res_connect>0)
  {
    printf("Connected to server!\n");
    printf("write something\n");
    int connection = 1;
    while(connection)
    {
      char buffer[250]= {0};
      if(fgets(buffer,sizeof(buffer),stdin)!=NULL)
      {
        size_t len = strlen(buffer);
        buffer[len-1]='\0';
        len--;
        printf("se van a enviar %zu bytes\n",len);
        

      }
      

    }

    printf("Conectado exitosamente a %s %s\n",IP,PORT);
   

  }

  return 0;

}

