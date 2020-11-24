//////////////////////////////////////////////////
//
// Names: Tanner Kern, Matt Masak, Andrew Zammetti
// Creation Date: November 15, 2020
// Due Date: November 24, 2020
// Course: CSC328 - Network Programming
// Professor Name: Dr. Frye
// Assignment: Simple Chat Server
// Filename: library.h
// Purpose: The header file for the library.
//          The completed functions are in library.cpp
//  
///////////////////////////////////////////////////


// ALL FUNCTION DOCUMENTATION IS IN library.cpp
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <vector>

struct Socket 
{
    int socketID;
    struct addrinfo *res;
};

void setupSocket(std::string ip, Socket *s, bool isServer, std::string portnum);

void sendMessage(int socketID, std::string msg);
std::string recvMessage(int socketID);
