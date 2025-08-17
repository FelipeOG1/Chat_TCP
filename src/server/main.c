#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <poll.h>
#include "server.h"
#define backlog 20


int main(int argc,char *argv[]){
    const char *IP = "localhost";
    const char *PORT = "3000";
    int listener_socket = tcp_listener(IP,PORT);

    


  return 0;
}

