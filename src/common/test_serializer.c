#include "serializer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(){
char message[MAX_MESSAGE_LEN];
char username[MAX_USERNAME_LEN];
printf("Digite su nombre de usuario \n");
fgets(username,sizeof(username),stdin);
username[strlen(username)-1] = 0;
printf("Bienvenido %s ahora puede escribir un mensaje \n",username);
fgets(message,sizeof(message),stdin);
ClientMessage m;
strncpy(m.username,username,MAX_USERNAME_LEN);
strncpy(m.message,message,MAX_MESSAGE_LEN);
m.is_message_flag = 0x01;
message_deserializer(&m);

return 0;
}

