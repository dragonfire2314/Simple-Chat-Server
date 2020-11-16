#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

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

    //std::cout << "Socket: " << sockfd << "\n";

    connect(sockfd, res->ai_addr, res->ai_addrlen);

	    char buf[512];
				
	    while (recv(sockfd, buf, 512, 0)) {
        std::cout << buf << std::endl;
		}

    freeaddrinfo(res); // free the linked-list
}
