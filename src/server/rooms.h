#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../common/packet.h"
typedef struct room{
  char room_name[MAX_ROOMNAME_LEN];
  int clients_sockets[100];
  uint8_t sockets_index;
  
}Room;

typedef struct rooms{
  Room all_rooms[255];
  uint8_t n_rooms;
}Rooms;

void init_rooms(Rooms * rooms);
void add_room(Rooms *rooms,Room*room);
void init_room(Room *room,AddRoom *add_room_msg,int client_sockfd);
void show_all_rooms(Rooms *rooms);
