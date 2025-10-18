#include "interface.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <assert.h>
#include "client.h"
#include "../common/packet.h"
#define MAX_Y 40
#define MAX_X 153
#define ENTER 10



void render_room_window(int sockfd){
  clear();
  printw("Bienvenido al room");
}
int render_menu_and_get_room_index(char *options[],int n_options,size_t buffer_size){
  int highlight = 0; // selected option
  int menu_mode = 1;
  while (menu_mode){
    clear();
    for(int i = 0; i < n_options; i++) {
      if(i == highlight) {
        attron(COLOR_PAIR(1));      // Fondo azul
        attron(A_BOLD);             // Negrita
        mvprintw(5 + i, 10, "%s", options[i]);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
     }else {
        attron(COLOR_PAIR(2));      // Texto amarillo
	mvprintw(5 + i, 10, "%s", options[i]);
	attroff(COLOR_PAIR(2));
   }
}
    refresh();
    const int KEY_PRESS = getch();
    switch (KEY_PRESS) {
      case KEY_UP:
        highlight--;
	if(highlight < 0) highlight = n_options - 1;
	break;
      case KEY_DOWN:
	highlight++;
	if(highlight >= n_options) highlight = 0;
	break;

      case '\n':
	menu_mode = 0;
	return highlight;
	


    }


  
  }
	  
 
}


void render_show_room_window(int sockfd){ 
  uint8_t show_room_flag = 0x08;
  int send_res = send(sockfd,&show_room_flag,1,0);//ask for room names
  assert(send_res>0);
  uint8_t buffer[1024];
  memset(buffer,0,sizeof(buffer));
  ssize_t bytes_received = recv(sockfd,buffer,sizeof(buffer), 0);//prepare to rcv room_names
  if (bytes_received>0){
    uint8_t first_byte = buffer[0];//Check for is null flag (0x10)
    if (first_byte == FLAG_IS_NULL){
      clear();
      printw("NO ROOMS TO SHOW");
      getch();
      
    }else{
      int n_rooms = buffer[1];//if there is rooms first byte has n_rooms
      char *options[n_rooms];
      fill_options_names(buffer,options,n_rooms);
      int user_response;//get_response in this case 
      curs_set(0);
      int room_index = render_menu_and_get_room_index(options,n_rooms,sizeof(user_response));
      JoinRoom join_room = {.room_index = room_index,.username = "martin",.is_join_room_flag = 0x04};
      int send_response = send(sockfd,(void *)&join_room,sizeof(JoinRoom),0);
      assert(send_response>0);
      uint8_t recv_response[10]; 
      bytes_received = recv(sockfd,&recv_response,sizeof(recv_response),0);
      if (bytes_received>0 && recv_response[0] == FLAG_ISJOIN_ROOM){
        clear();
	printw("te uniste al room");
      }
      
    
      
    }
   
    
   }
    
       
}

//TODO SET FLAG TO INDICATE THAT SERVER SUCCESFULLY THE ROOM 
void render_create_room_window(int sockfd){
   clear();
   refresh();
   echo();
   curs_set(1);
   
   char room_name_buffer[100];
   uint8_t response_buffer[10];
   const char * username = "Felipe";
   AddRoom j;
   j.is_add_room_flag = 0x02;
   int send_response,recv_response;
   WINDOW * user_input = newwin(3,142,0, 6);
   strcpy(j.username,username);
   cbreak();
   refresh();
   box(user_input,0,0);
   wprintw(user_input,"TYPE NEW ROOM NAME");
   wmove(user_input,1,1);
   wgetstr(user_input,j.room_name);
   wrefresh(user_input);
   
   send_response = send (sockfd,(void *)&j,sizeof(AddRoom),0);
   recv_response = recv(sockfd,response_buffer,sizeof(response_buffer),0);
   assert(send_response > 0);
   uint8_t flag = response_buffer[0];//get_flag_byte;
   if (flag == 0x02){
     printw("room created");
     getch();
   }

   
}

void render_join_room_window(int sockfd){
  //Send a show room flag to server
  clear();
  echo();
  curs_set(1);
  getch();
}

void render_main_window(int sockfd){
  initscr();            // Iniciar ncurses
  start_color();        // Activar colores
  cbreak();             // Modo línea por línea
  noecho();             // No mostrar teclas presionadas
  keypad(stdscr, TRUE); // Habilitar flechas
  curs_set(0);
  init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Fondo azul
  init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Texto amarillo
  int highlight = 0;
  char *options[] = {"JOIN ROOM","ADD ROOM","SHOW ROOMS","Salir"};
  int n_options = 4;
  int ch;
  while(1) {
  clear();
  curs_set(0);
  for(int i = 0; i < n_options; i++) {
    if(i == highlight) {
      attron(COLOR_PAIR(1));      // Fondo azul
      attron(A_BOLD);             // Negrita
      mvprintw(5 + i, 10, "%s", options[i]);
      attroff(A_BOLD);
      attroff(COLOR_PAIR(1));
   }else {
	attron(COLOR_PAIR(2));      // Texto amarillo
	mvprintw(5 + i, 10, "%s", options[i]);
	attroff(COLOR_PAIR(2));
   }
}
  refresh();
  ch = getch();
  switch(ch) {
    case KEY_UP:
	highlight--;
	if(highlight < 0) highlight = n_options - 1;
	break;
    case KEY_DOWN:
	highlight++;
	if(highlight >= n_options) highlight = 0;
	break;
    case 10: // Enter
	if(highlight == n_options - 1) {
	    endwin();
	    exit(0); // Salir
	} else {
	if (strcmp(options[highlight], "ADD ROOM") == 0) {
	    render_create_room_window(sockfd);
	    // acción para "ADD ROOM"
	} else if (strcmp(options[highlight], "JOIN ROOM") == 0) {
	    render_join_room_window(sockfd);
	} else if (strcmp(options[highlight], "SHOW ROOMS") == 0) {
	    render_show_room_window(sockfd);
}
	}
	break;
}
}

    endwin();


}



