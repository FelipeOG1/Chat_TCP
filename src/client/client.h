#pragma once

int connect_to_server (const char *IP,const char *PORT);

int send_message(int sockfd,char buffer[250],int msg_len);

