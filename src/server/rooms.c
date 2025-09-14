#include "rooms.h"


void init_rooms(Rooms * rooms){
  memset(rooms->all_rooms,0,sizeof(rooms->all_rooms));
  rooms->n_rooms = 0;
}


//TODO CREATE ADD ROOM FUNCTIO
