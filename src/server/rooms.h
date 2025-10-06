#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../common/packet.h"

typedef struct room{
  char room_name[MAX_ROOM_NAME_LEN];
  int clients_sockets[100];
  uint8_t sockets_index;
  uint8_t room_id;
  size_t room_name_len;
}Room;

typedef struct rooms{
  Room all_rooms[MAX_NUM_OF_ROOMS];
  uint8_t n_rooms;
  size_t room_names_len;
  char room_names[MAX_NUM_OF_ROOMS][MAX_ROOM_NAME_LEN];
  int room_names_offset;
  uint8_t room_ids[MAX_NUM_OF_ROOMS];
}Rooms;


void add_room(Rooms *rooms,AddRoom * add_room,int sockfd);
void show_all_rooms(Rooms *rooms);
