#include "../rooms.h"
#include "../../common/packet.h"
#include <stdint.h>
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
  AddRoom sample2= {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "foo",.username = "martinez"};
  Rooms rooms;
  init_rooms(&rooms);
  add_room(&rooms,&sample1,3);
  add_room(&rooms,&sample2,5);
  
  assert(strcmp(rooms.all_rooms[0].room_name,"the room") == 0);
  assert(strcmp(rooms.all_rooms[1].room_name,"foo") == 0);
  assert(rooms.room_names_len == 11);
  assert(rooms.n_rooms == 2);
}

void test_show_all_rooms(){
  AddRoom sample1 = {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "Marcianos",.username = "martinez"};
  AddRoom sample2= {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "core dumped",.username = "martinez"};
  Rooms rooms;
  init_rooms(&rooms);
  add_room(&rooms,&sample1,3);
  add_room(&rooms,&sample2,5);
  int n_rooms = rooms.buffer[1];
  char *options[n_rooms];
  fill_options_names(rooms.buffer,options);
  for (int i = 0;i<n_rooms;i++){
    printf("%s",options[i]);
  }
  
 }

int main(){

  test_add_room();
  test_init_rooms();
  test_show_all_rooms();
  
  printf("ALL TESTS SUCCESS!!\n");
  return 0;
}



