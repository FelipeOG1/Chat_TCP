#include "interface.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "client.h"
#define MAX_Y 40
#define MAX_X 153

void render_show_room_window(int sockfd){
   clear();
   echo();
   curs_set(1);
   uint8_t show_room_flag = 0x08;
   getch();
   _send_message(sockfd,&show_room_flag,1);//send one byte to server with flag
}
void render_create_room_window(int sockfd){
   clear();
   echo();
   curs_set(1);
   char room_name_buffer[100];
   const char * username = "Felipe";
   AddRoom j;
   j.is_add_room_flag = 0x02;
   strcpy(j.username,username);
   refresh();
   initscr();
   cbreak();
   WINDOW * user_input = newwin(3,142,0, 6);
   refresh();
   box(user_input,0,0);
   wprintw(user_input,"TYPE NEW ROOM NAME");
   wmove(user_input,1,1);
   wgetstr(user_input,j.room_name);
   wrefresh(user_input);
   move(20,20);
   printw("%s wants to create the room named %s",j.username,j.room_name);
   getch();
   send_message(sockfd,(void *)&j);
   getch();
   endwin();
   exit(1);
}

void render_join_room_window(int sockfd){
  //Send a show room flag to server
  clear();
  echo();
  curs_set(1);
  getch();
  endwin();
  exit(0);
}

void render_menu_window(int sockfd){
  initscr();            // Iniciar ncurses
  start_color();        // Activar colores
  cbreak();             // Modo línea por línea
  noecho();             // No mostrar teclas presionadas
  keypad(stdscr, TRUE); // Habilitar flechas
  curs_set(0);
    // Definir pares de colores: id, fg, bg
  init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Fondo azul
  init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Texto amarillo

  char *options[] = {"JOIN ROOM","ADD ROOM","SHOW ROOMS","Salir"};
  int n_options = 4;
  int highlight = 0; // opción seleccionada
  int ch;
  while(1) {
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


