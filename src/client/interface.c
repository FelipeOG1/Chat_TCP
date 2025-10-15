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

void render_menu_and_get_response(char *options[],int n_options,char res_buffer[],size_t buffer_size){
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
        const char *selected_option = options[highlight];
	strncpy(res_buffer,selected_option,buffer_size - 1);
	menu_mode = 0;
	break;


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
    curs_set(0);
    int n_rooms = buffer[1];//second byte has nunber of rooms
    char *options[n_rooms];
    fill_options_names(buffer,options,n_rooms);
    char user_response[100];
    render_menu_and_get_response(options,n_rooms,user_response,sizeof(user_response));
    
    
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



