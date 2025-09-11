#include "serializer.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
/*First byte flags (ISMESSAGE,ISCONNECTION)
 *Second byte payloadlen
 *Third and fourth byte extended payload len if necesary (if it is less than 170 is tha actual len if it is 70 chek the fifth an sixht byte)
 *fifth byte and sixth byte payloadata()
 * IF is connection message, 52 bytes are reserved for user_name and room_id
 * If is packetHeader 50 bytes of payload is reserved for username;
 *
 *
 *
 * 
 *
 * 
 *
 *
 *
 */

void message_deserializer(void *struct_pointer){
uint8_t flag = *(uint8_t *)struct_pointer;
switch (flag){
  case FLAG_ISMESSAGE:
	  ClientMessage message = *(ClientMessage *)struct_pointer;
	  printf("username :%s\n",message.username);
	  printf("message:%s\n",message.message);
	  break;
	
}

}

