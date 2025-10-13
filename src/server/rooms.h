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
  uint8_t buffer[1024];
  int buffer_offset;
}Rooms;


void add_room(Rooms *rooms,AddRoom * add_room,int sockfd);
void show_all_rooms(Rooms *rooms);
void init_rooms(Rooms *rooms);
void add_client_to_room(int sockfd,const char * room_name,Rooms *rooms);
void show_all_rooms(Rooms *rooms);
void fill_options_names(uint8_t buffer[],char *options[]);
