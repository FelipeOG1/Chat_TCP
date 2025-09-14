#include "interface.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#define MAX_Y 40
#define MAX_X 153
void render_create_room_window(int sockfd){
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
   send_message(sockfd,(void*)&j);
   endwin();
   exit(1);
}

void render_menu_window(int sockfd){
  initscr();
  cbreak();
  //SETUP WINOW POSITION AND INITIAL CURSOR POSITION
  WINDOW * menu_window = newwin(10,142,0, 6);
  refresh();
  box(menu_window,0,0);
  wmove(menu_window,1,71);//CREATE ROOM COORDINATES (1,71)
  wprintw(menu_window,"CREATE ROOM");   
  wrefresh(menu_window);
  wmove(menu_window,3,71);//JOIN ROOM COORDINATES (3,71)
  wprintw(menu_window,"JOIN ROOM");
  wmove(menu_window,1,71);//RESET CURSOR POSITION
  wrefresh(menu_window);
  //STARTS LISTENING TO USER KEYS (KEY_UP,KEY_DOWN)
  keypad(menu_window, TRUE);
  int key = 0;
  while(key != 'e'){
    int y,x;
    getyx(menu_window,y,x);
    key = wgetch(menu_window);
    //HANDEL UP AND DOWN KEYS   
    if (key == KEY_DOWN){
      if (y == 1 && x == 71){
        wmove(menu_window,3,71);
      }else{
       wmove(menu_window,y,x);
      }
    }else if(key == KEY_UP){
      if (y == 3 && x == 71){
        wmove(menu_window,1,71);
      }else{
        wmove(menu_window,y,x);
      }
    wrefresh(menu_window);
    }
    //HANDLE ENTER
    if(key == 10 | key == KEY_ENTER){
      if (y == 1 && x == 71){
       endwin();
       clear();
       render_create_room_window(sockfd);
       
      }
    }
        
  }
   endwin();
}




