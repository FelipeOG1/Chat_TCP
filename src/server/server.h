#pragma once

void process_recv_buffer(char buffer[200]);

int tcp_listener(const char * port,const char *ip);

void event_handler(int sock_fd);






