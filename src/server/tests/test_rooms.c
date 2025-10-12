#include "../rooms.h"
#include "../../common/packet.h"
#include <stdio.h>
#include <assert.h>

void test_init_rooms(){
  Rooms rooms;
  init_rooms(&rooms);
  assert(rooms.buffer_offset == 2);
  assert(rooms.n_rooms == 0);
  assert(rooms.room_names_len == 0);
  
}
void test_add_room(){
  
  AddRoom sample1 = {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "the room",.username = "martinez"};
  Rooms rooms;
  init_rooms(&rooms);
  add_room(&rooms,&sample1,3);
  assert(strcmp(rooms.all_rooms[0].room_name,"the room") == 0);

  AddRoom sample2= {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "foo",.username = "martinez"};
  add_room(&rooms,&sample2,5);
  assert(strcmp(rooms.all_rooms[1].room_name,"foo") == 0);
  
}


int main(){

  test_add_room();
  test_init_rooms();


  printf("ALL TESTS SUCCESS!!\n");
  return 0;
}



