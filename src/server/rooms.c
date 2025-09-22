#include "rooms.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

void init_rooms(Rooms * rooms){
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
  rooms->room_names_len = 0;
}

void add_room(Rooms *rooms ,Room *room){
  rooms->all_rooms[rooms->n_rooms] = *room;
  rooms->n_rooms+=1;
  rooms->room_names_len+=strlen(room->room_name);//add len of name every add_room operation
  
}

void init_room(Room *room,AddRoom *add_room_msg,int client_sockfd){
  room->sockets_index = 0;
  strcpy(room->room_name,add_room_msg->room_name);
  room->clients_sockets[room->sockets_index] = client_sockfd;
}

void show_all_rooms(Rooms * rooms){

  //COMPACTING BUFFER AS MUCH AS POSIBLE
  
  uint8_t buffer[1+1+rooms->room_names_len + rooms->n_rooms];//use room_names_len to setup the smalles buffer possible
  
  size_t offset = 0;
  
  buffer[offset++] = FLAG_ISSHOW_ROOM;//first byte 
  buffer[offset++] = rooms->n_rooms;//second byte

  for (int i =0 ;i<rooms->n_rooms;i++){
    char *current_room_name = rooms->all_rooms[i].room_name;
    strcpy((char *)(buffer + offset),current_room_name);
    //offset contemplates'\0'
    offset+=strlen(current_room_name) + 1;
   }


  
	
  
  

}
