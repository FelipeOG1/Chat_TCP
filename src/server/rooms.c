#include "rooms.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

void init_rooms(Rooms * rooms){
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
}

void add_room(Rooms *rooms ,Room *room){
  rooms->all_rooms[rooms->n_rooms] = *room;
  rooms->n_rooms+=1;
}

void init_room(Room *room,AddRoom *add_room_msg,int client_sockfd){
  room->sockets_index = 0;
  strcpy(room->room_name,add_room_msg->room_name);
  room->clients_sockets[room->sockets_index] = client_sockfd;
}

void show_all_rooms(Rooms * rooms){

  //COMPACTING BUFFER AS MUCH AS POSIBLE
  
  //1.Get the total len of all the name rooms that we have
  //2.create a array of names with the names
  const char *room_names[rooms->n_rooms];
  size_t room_names_len = 0;
  for (int i = 0 ;i<rooms->n_rooms;i++){
    const char * room_name = rooms->all_rooms[i].room_name;
    room_names_len +=strlen(room_name);
    room_names[i] = room_name;
  }
  //Add one byte to every room_name_len for the '\0' that strcpy adds sign
  uint8_t buffer[1+1+room_names_len + rooms->n_rooms];
  
  //copy all names into a array of room_names
  size_t offset = 0;
  
  buffer[offset++] = FLAG_ISSHOW_ROOM;//first byte 
  buffer[offset++] = rooms->n_rooms;//second byte 

  for (int i =0 ;i<rooms->n_rooms;i++){
    size_t room_name_len = strlen(room_names[i]);
    strcpy((char *)(buffer + offset), room_names[i]);
    //offset contemplates '\0'
    offset+=room_name_len + 1;
   }


  
	
  
  

}
