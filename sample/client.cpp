#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() 
{
    int status;
    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo("127.0.0.1", "3490", &hints, &res);

    //std::cout << AF_INET << " = "<< res->ai_family << "\n";
    //std::cout << SOCK_STREAM << " = "<< res->ai_socktype << "\n";
    //std::cout << AI_PASSIVE << " = "<< res->ai_flags << "\n";

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // error checking for socket creation
    if (sockfd == -1) { 
   	printf("socket creation failed\n"); 
   	exit(0); 
    }
    //std::cout << "Socket: " << sockfd << "\n";

    // error checking for connecting to the socket
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
	{
	perror("Can't connect to socket\n");
	return(-1);
	}

    char buf[512];
    while (recv(sockfd, buf, 512, 0)) {
        std::cout << buf << std::endl;
		}

    freeaddrinfo(res); // free the linked-list
}
