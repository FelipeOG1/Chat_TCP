#include "../common/packet.h"

#pragma once
void render_menu_and_get_response(char *options[],int n_options,char res_buffer[],size_t buffer_size);
void render_chat_room_window(int sockfd);
void render_create_room_window(int sockfd);
void render_join_room_window(int sockfd);
void render_main_window(int sockfd);
