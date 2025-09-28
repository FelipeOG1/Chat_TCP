#include "rooms.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

void init_rooms(Rooms * rooms){
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
  rooms->room_names_len = 0;
  rooms->room_names_offset = 0;
}

void add_room(Rooms *rooms ,Room *room){
  size_t current_room_name_len = strlen(room->room_name);
  rooms->all_rooms[rooms->n_rooms] = *room;
  rooms->n_rooms+=1;
  strncpy(rooms->room_names[rooms->room_names_offset],room->room_name,current_room_name_len);
  rooms->room_names_len+=current_room_name_len;
  rooms->room_names[rooms->n_rooms - 1][current_room_name_len + 1] ='\0';
  rooms->room_names_offset+=current_room_name_len + 2;//adjust offset to next room_name in pos '\0' + 1
  
}

void init_room(Room *room,AddRoom *add_room_msg,int client_sockfd){
  room->sockets_index = 0;
  strcpy(room->room_name,add_room_msg->room_name);
  room->clients_sockets[room->sockets_index] = client_sockfd;
}

void show_all_rooms(Rooms * rooms){
  if (rooms->n_rooms>0){
    //COMPACTING BUFFER AS MUCH AS POSIBLE
    uint8_t buffer[1+1+rooms->room_names_len + rooms->n_rooms];//use room_names_len to setup the smalles buffer possible
    memset(buffer,0,sizeof(buffer));
    size_t offset = 0;
    buffer[offset++] = FLAG_ISSHOW_ROOM;//first byte 
    buffer[offset++] = rooms->n_rooms;//second byte
    printf("%s\n",rooms->room_names[0]);
  }else{
   printf("No existen rooms todavia\n");
  }
 
}
