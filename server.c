//
// Created by Mehdi Khenissi on 06/02/2022.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include "try.h"
#define PORT 8080

int main(int argc, char ** argv) {

    char *hello = "Hello from server";
    char buffer[1024] = {0};
    int opt = 1;
    int val = 0;

    // creation of socket

    int sockId = try(socket(AF_INET, SOCK_STREAM, 0));

    // Forcefully attaching socket to the port 8080

    try(setsockopt(sockId, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)));

    // connection
    struct sockaddr_in  resSock;
    int addrlen = sizeof(resSock);
    resSock.sin_family = AF_UNSPEC;
    resSock.sin_addr.s_addr = INADDR_ANY;
    resSock.sin_port = htons(PORT);

    try(bind(sockId, (struct sockaddr *) &resSock, sizeof(resSock)));

    try(listen(sockId, 3));

    int new_socket = try(accept(sockId, (struct sockaddr *) &resSock,  (socklen_t*) &addrlen));

    val = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    return 0;
}