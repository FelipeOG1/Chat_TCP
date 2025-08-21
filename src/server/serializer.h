#pragma once
#include <stdint.h>
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
  unsigned char room_id[2];
  int sock_id;
};
struct client_message{
  unsigned char message_buffer[30];
  uint32_t client_fd;
  uint64_t payload_len;
};

struct packetHeader{
  uint8_t flags;
  uint16_t payload_len;
};

void serialize_connection_message(struct connection_message cn_message);

void serialize_client_message(struct client_message cl_message,unsigned char *out_buffer);

void deserialize_message(unsigned char buffer[1000]);


