#pragma once



void start_event_loop(int sock_fd);

void event_loop(struct pollfd * poll_fds);


