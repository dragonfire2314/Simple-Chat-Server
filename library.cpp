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


///////////////////////////////////////////////////////////
//  
//  Function name:    setupSocket
//  Description:      This function sets up a socket with 
//                    all the given information
//  Parameters:       string ip - The IP address of whoever is 
//                                trying to create a socket
//                    Socket *s - The socket about to be created
//                    bool isServer - False if not the server
//                    char* portnum - The port number gotten from CLA
//  Return Value:     None
//
///////////////////////////////////////////////////////////
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

    
    if ((s->socketID = socket(s->res->ai_family, s->res->ai_socktype, s->res->ai_protocol)) < 0){
		perror("Unable to create socket");
		exit(1);
	}
}

///////////////////////////////////////////////////////////
//  
//  Function name:    sendMessage
//  Description:      Sends a given message, whether it's from the server or client
//  Parameters:       int socketID - Which socket this is being sent to
//                    string msg - The message to be sent
//  Return Value:     None
//
///////////////////////////////////////////////////////////
void sendMessage(int socketID, std::string msg)
{
    int len, bytes_sent;

    len = msg.length();
    bytes_sent = send(socketID, msg.c_str(), len, 0);
}

///////////////////////////////////////////////////////////
//  
//  Function name:    recvMessage
//  Description:      Handles receiving functions from both client and server
//  Parameters:       int socketID - which socket ID is sending this message
//  Return Value:     s (string) - the message that's being received
//
///////////////////////////////////////////////////////////
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
