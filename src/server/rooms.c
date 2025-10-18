#include "rooms.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

static int room_id_counter = 0;

static void init_room(Room *room,AddRoom *add_room_msg,int client_sockfd){
  room->sockets_index = 0;
  room->room_name_len = strlen(add_room_msg->room_name);
  strlcpy(room->room_name,add_room_msg->room_name,MAX_ROOM_NAME_LEN);//+1 pos add '\0'
  room->clients_sockets[room->sockets_index] = client_sockfd;//add creator of room socket into room sockets
  room->room_id = room_id_counter++;//room_id = room_id_counter and then increment by 1
}

void init_rooms(Rooms * rooms){
  rooms->buffer_offset = 0;
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
  rooms->room_names_len = 0;
  rooms->buffer[rooms->buffer_offset++] = FLAG_ISSHOW_ROOM;
  rooms->buffer[rooms->buffer_offset++] = 0;//number of rooms
}

void add_room(Rooms *rooms ,AddRoom * add_room,int sockfd){
  Room room;
  init_room(&room,add_room,sockfd);
  rooms->all_rooms[room.room_id] = room;
  size_t current_room_name_len = room.room_name_len;
  size_t written = strlcpy((char *)&rooms->buffer[rooms->buffer_offset],room.room_name,sizeof(rooms->buffer) - rooms->buffer_offset);
  rooms->buffer_offset+=written + 1; //written dont contemplate de null character
  rooms->n_rooms+=1;
  rooms->room_names_len+=current_room_name_len;
  rooms->buffer[1] = rooms->n_rooms;
  
}

void add_client_to_room(int sockfd,int room_index,Rooms *rooms){
  Room room = rooms->all_rooms[room_index];
  room.clients_sockets[room.sockets_index] = room_index; 
}


