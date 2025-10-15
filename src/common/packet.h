#pragma once
#include <stdint.h>
#include <stddef.h>

/** 
 *  Indicates that the packet should be recast to a message struct.
 *  Bit mask: 0x01 (0000 0001)
 */
#define FLAG_ISMESSAGE 0x01

/**  
 *  Indicates that the packet should be recast to an add room struct.
 *  Bit mask: 0x02 (0000 0010)
 */
#define FLAG_ISADD_ROOM 0x02

/**     Indicates that the packet should be recast to a join room struct.
 *  Bit mask: 0x04 (0000 0100)
 */
#define FLAG_ISJOIN_ROOM 0x04

/** Indicates that the packet should be recast to a show rooms struct.
 *  Bit mask: 0x08 (0000 1000)
 */
#define FLAG_ISSHOW_ROOM 0x08

/**
 *  Indicates an empty room or null condition.
 *  Bit mask: 0x10 (0001 0000)
 */
#define FLAG_NULL 0x10

/** Maximum allowed payload length */
#define MAX_PAYLOAD_LEN 1000

/**  Maximum allowed message length */
#define MAX_MESSAGE_LEN 500

/**  Maximum allowed username length */
#define MAX_USERNAME_LEN 20

/**  Maximum allowed room name length */
#define MAX_ROOM_NAME_LEN 20

/** Maximum number of rooms supported */
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


