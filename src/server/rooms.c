#include "rooms.h"
#include <string.h>
#include <stdio.h>
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
  for (int i=0; i<=rooms->n_rooms;i++){
    printf("%s",rooms->all_rooms[i].room_name);
  }

}
