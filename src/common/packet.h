#pragma once
#include <stdint.h>
#include <stddef.h>
#define FLAG_ISMESSAGE 0x01 //recast to message struct
#define FLAG_ISADD_ROOM 0x02 //recast to connection struct
#define FLAG_ISJOIN_ROOM 0x04
#define FLAG_ISSHOW_ROOM 0x08
#define MAX_PAYLOAD_LEN 1000
#define MAX_MESSAGE_LEN 500
#define MAX_USERNAME_LEN 20
#define MAX_ROOM_NAME_LEN 20
#define MAX_NUM_OF_ROOMS 255


typedef struct join_room{
  uint8_t is_join_room_flag;
  char username[MAX_USERNAME_LEN];
  char room_name[MAX_ROOM_NAME_LEN];
}JoinRoom;

typedef struct client_message{
  uint8_t is_message_flag;
  char username[MAX_USERNAME_LEN];
  char message[MAX_MESSAGE_LEN];
  char room_name[MAX_ROOM_NAME_LEN];
}ClientMessage;

typedef struct add_room{
  uint8_t is_add_room_flag;
  char username[MAX_USERNAME_LEN];
  char room_name[MAX_ROOM_NAME_LEN]; 
}AddRoom;

typedef struct show_rooms{
  uint8_t is_show_room_flag;
  char room_names[250][MAX_ROOM_NAME_LEN];
}ShowRooms;


