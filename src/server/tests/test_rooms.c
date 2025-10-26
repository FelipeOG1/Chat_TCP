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

void test_add_client_room(){
	

  AddRoom sample1 = {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "Marcianos",.username = "martinez"};//index 0
  AddRoom sample2= {.is_add_room_flag = FLAG_ISADD_ROOM,.room_name = "Nigus",.username = "goza"};//index 1
  Rooms rooms;
  int martinez_socket = 3;
  int goza_socket = 10;
  
  init_rooms(&rooms);
  add_room(&rooms,&sample1,martinez_socket);
  add_room(&rooms,&sample2,goza_socket);

  
  //Asserts for the room creators
  assert(rooms.all_rooms[0].clients_sockets[0] == martinez_socket);//assert that creator socket was added
  assert(rooms.all_rooms[1].clients_sockets[0] == goza_socket);//assert that index 1 creator was added
  

  //Asserts for new clients
  int new_socket_1 = 29;
  int new_socket_2 =1;
  add_client_to_room(new_socket_1,0,&rooms);
  add_client_to_room(new_socket_2,1,&rooms);
  assert(rooms.all_rooms[0].clients_sockets[1] == new_socket_1); 
  assert(rooms.all_rooms[1].clients_sockets[1] == new_socket_2); 
}

int main(){

  //test_add_room();
  //test_init_rooms();
  test_add_client_room();
  printf("ALL TESTS SUCCESS!!\n");
  return 0;
}



