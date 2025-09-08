#include "serializer.h"
#include <stdio.h>
#include <string.h>
int main(){
char buffer[500];
fgets(buffer,sizeof(buffer),stdin);
buffer[strlen(buffer)-1] = 0;
ClientMessage m = {.message_buffer = buffer,.payload_len = strlen(buffer)};
struct packet pa = {.flags = 0x01, .struct_pointer = &m};

char *final_buffer;
serialize_message(pa,final_buffer);

return 0;
}

