#include "serializer.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#define FLAG_ISMESSAGE 0x01 //recast to message struct
#define FLAG_ISADD_ROOM 0x02 //recast to connection struct
#define FLAG_ISJOIN_ROOM 0x04
#define MAX_PAYLOADLEN 1000
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
void serialize_message (struct packet p,char buffer[510]){
  switch (p.flags){
	  case FLAG_ISMESSAGE:{
		printf("es un is messageee\n");
	  	ClientMessage *ptr = (ClientMessage*)p.struct_pointer;
		printf("%s",ptr->message_buffer);
		
	  }
		    
	     
  }
}
