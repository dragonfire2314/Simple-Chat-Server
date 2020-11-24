//////////////////////////////////////////////////
//
// Names: Tanner Kern
// Creation Date: November 15, 2020
// Due Date: November 24, 2020
// Course: CSC328 - Network Programming
// Professor Name: Dr. Frye
// Assignment: Simple Chat Server
// Filename: library.cpp
// Purpose: The library file containing all 
//          the functions used by both the client
//          and the server. 
//  
///////////////////////////////////////////////////
#include "library.h"

void setupSocket(std::string ip, Socket *s, bool isServer, char* portnum)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
    hints.ai_family = AF_INET;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    int status;
	
	
    if (isServer) {
        if ((status = getaddrinfo(NULL, portnum, &hints, &(s->res))) != 0) {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            exit(1);
        }
    }
    else {
        if ((status = getaddrinfo(ip.c_str(), portnum, &hints, &(s->res))) != 0) {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            exit(1);
        }
    }

    
    if (s->socketID = socket(s->res->ai_family, s->res->ai_socktype, s->res->ai_protocol) < 0){
		perror("Unable to create socket");
		exit(1);
	}
}

void sendMessage(int socketID, std::string msg)
{
    int len, bytes_sent;

    len = msg.length();
    bytes_sent = send(socketID, msg.c_str(), len, 0);
}

std::string recvMessage(int socketID)
{
    char buf[512];
    //Clear the buffer? IDK why this is needed since its on the stack but dont remove.
    //It will break. Best guess I have is the compiler is messing with me?
    memset(buf, 0, 512);

    int status;
    if (recv(socketID, buf, 512, 0) == 0) {
        fprintf(stderr, "client gone, revc error: %s\n", gai_strerror(status));
        exit(1);
    }

    //printf("Message Recieved: %s\n", buf);

    std::string s(buf);
    return s;
}
