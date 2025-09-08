#include "serializer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
int main(){
char buffer[500];
fgets(buffer,sizeof(buffer),stdin);
buffer[strlen(buffer)-1] = 0;
ClientMessage m = {.message_buffer = buffer,.payload_len = strlen(buffer)};
char final_buffer[500];
uint8_t flags = 0x01;
serialize_message(&m,final_buffer,flags);



return 0;
}

