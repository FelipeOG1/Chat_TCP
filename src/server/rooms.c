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
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
  rooms->room_names_len = 0;
  rooms->room_names_offset = 0;
}

void add_room(Rooms *rooms ,AddRoom * add_room,int sockfd){
  Room room;
  init_room(&room,add_room,sockfd);
  rooms->all_rooms[room.room_id] = room;
  size_t current_room_name_len = room.room_name_len;
  strlcpy(rooms->room_names[rooms->n_rooms],room.room_name,MAX_ROOM_NAME_LEN);
  rooms->n_rooms+=1;
  rooms->room_names_len+=current_room_name_len;
}

void add_client_to_room(int sockfd,const char * room_name,Rooms *rooms){
  for(int i = 0;i<rooms->n_rooms;i++){
    if ((strcmp(rooms->room_names[i], room_name)) == 0){
      
    }
  }

}

void show_all_rooms(Rooms * rooms){
  if (rooms->n_rooms>0){
    //COMPACTING BUFFER AS MUCH AS POSIBLE
    uint8_t buffer[1+1+rooms->room_names_len + rooms->n_rooms];//rooms->n_rooms adds all the necesary '\0' to consider
    memset(buffer,0,sizeof(buffer));
    size_t offset = 0;
    buffer[offset++] = FLAG_ISSHOW_ROOM;//first byte 
    buffer[offset++] = rooms->n_rooms;//second byte
    for (int i =0;i<rooms->n_rooms,i++){
      Room current_room = rooms->all_rooms[i];
      size_t written = strlcpy(&buffer[offset],
                             current_room.room_name,
                             sizeof(buffer) - offset);

      offset += written + 1;
    
    }
    }else{
   printf("No existen rooms todavia\n");
  }
 
}
