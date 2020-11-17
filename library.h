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

bool setupSocket(std::string ip, Socket *s, bool isServer);

void sendMessage(int socketID, std::string msg);
std::string recvMessage(int socketID);