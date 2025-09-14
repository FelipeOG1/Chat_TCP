#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../common/packet.h"
#pragma once

typedef struct room{
  char room_name[MAX_ROOMNAME_LEN];
  int clients_sockets[30];
}Room;


typedef struct rooms{
  Room all_rooms[255];
  uint8_t n_rooms;
}Rooms;

void init_rooms(Rooms * rooms)

