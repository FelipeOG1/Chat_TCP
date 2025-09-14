#pragma once
#include <stdint.h>
#include <stddef.h>

#define FLAG_ISMESSAGE 0x01 //recast to message struct
#define FLAG_ISADD_ROOM 0x02 //recast to connection struct
#define FLAG_ISJOIN_ROOM 0x04
#define MAX_PAYLOAD_LEN 1000
#define MAX_MESSAGE_LEN 500
#define MAX_USERNAME_LEN 20
#define MAX_ROOMNAME_LEN 20


typedef struct join_room{
  uint8_t is_join_room_flag;
  char username[MAX_USERNAME_LEN];
  char room_name[MAX_ROOMNAME_LEN];
}JoinRoom;

typedef struct client_message{
  uint8_t is_message_flag;
  char username[MAX_USERNAME_LEN];
  char message[MAX_MESSAGE_LEN];
  char room_name[MAX_ROOMNAME_LEN];
}ClientMessage;

typedef struct add_room{
  uint8_t is_add_room_flag;
  char username[MAX_USERNAME_LEN];
  char room_name[MAX_ROOMNAME_LEN]; 
}AddRoom;
typedef struct packet{
  unsigned char flags;
  size_t payload_len;
  char payload[MAX_PAYLOAD_LEN];
}Packet;
