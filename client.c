//
// Created by Mehdi Khenissi on 06/02/2022.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "try.h"
#define PORT 8080

int main(int argc, char ** argv) {

    char *hello = "Hello from client";
    char buffer[1024] = {0};
    int sockId = 0;
    int val = 0;

    // creation of socket
    sockId = try(socket(AF_INET, SOCK_STREAM, 0));

    // connection
    struct sockaddr_in  resSock;
    resSock.sin_family = AF_UNSPEC;
    resSock.sin_port = htons(PORT);


    // have to cast it as sockaddr cuz of the param and cause we are using sockaddr_in
    try(connect(sockId, (struct sockaddr *) &resSock, sizeof(resSock)));

    send(sockId , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    val = try(read( sockId , buffer, 1024));
    printf("%s\n",buffer );


    return 0;
}



