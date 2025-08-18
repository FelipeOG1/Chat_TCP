#pragma once
#define FLAG_ISMESSAGE //recast to message struct
#define FLAG_ISCONNECTION //recast to connection struct
#define FLAG_ISSMALL //small read only thirdbyte
#define MAX_PAYLOADLEN

struct connection_message{
  unsigned char user_name[50];
  unsigned char room_id[2];
  int sock_id;
};
struct client_message{
  unsigned username_destinatary[50];
  unsigned char message_buffer[30];
};

struct packetHeader{
  uint8_t flags;
  uint64_t payload_len;
};




/*First byte flags (ISMESSAGE,ISCONNECTION)
 *Second byte payloadlen
 *Third and fourth byte extended payload len if necesary (BIGGER THAN 255)
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
void serialize_message(struct void message);


void deserialize_user(struct void message);


