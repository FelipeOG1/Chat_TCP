#include "serializer.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>


#define FLAG_ISMESSAGE 0x01 //recast to message struct
#define FLAG_ISCONNECTION 0x02 //recast to connection struct
#define FLAG_ISSMALL 0x04 //small read only thirdbyte
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


void serialize_connection_message(struct connection_message cn_message){
  
}
void serialize_client_message(struct client_message cl_message, unsigned char *out_buffer) {
  struct packetHeader header;
  header.flags |= FLAG_ISMESSAGE;
  header.payload_len = cl_message.payload_len;
  header.flags = htons(header.flags);
  header.payload_len = htons(header.payload_len);
  memcpy(out_buffer, &header, sizeof(header));
}

void deserialize_message(unsigned char buffer[1000]){

}


