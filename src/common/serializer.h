#pragma once
#include <stdint.h>
#include <stddef.h>
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

struct connection_message{
  unsigned char user_name[50];
  uint8_t room_id[2];
};

typedef struct client_message{
  char * message_buffer;
  size_t payload_len;
}ClientMessage;
struct packet{
  unsigned char flags;
  void *struct_pointer;
};

void serialize_message(struct packet p,char buffer[510]);

	
	


