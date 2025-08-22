#pragma once

int connect_to_server (const char *IP,const char *PORT);

int send_message(int sockfd,char buffer[250],int msg_len);
int receive_client_message(int sockfd,char buffer[250],int buff_len);

