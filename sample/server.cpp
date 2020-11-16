#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "library.h"

int main() 
{
    struct sockaddr_storage their_addr;

    int socketID;
    struct addrinfo *res;

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
    hints.ai_family = AF_INET;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    int status;

    if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    //std::cout << "Socket: " << sockfd << "\n";

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        printf("Error at bind\n");
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        printf("Error at listen\n");
        exit(1);
    }

    socklen_t addr_size = sizeof(their_addr);
    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    //std::cout << new_fd << std::endl;

    
    char msg[] = "Hello";
    int len, bytes_sent;
	
	len = strlen(msg);
    send(new_fd, msg, len, 0);
	std::cout << "=> Connected with the client, you are good to go..." << std::endl;

    freeaddrinfo(res); // free the linked-list
}
