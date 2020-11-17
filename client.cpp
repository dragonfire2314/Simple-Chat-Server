#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "library.h"

std::mutex mtx;

Socket s;

void closeConnection(int signal)
{
    printf("Caught signal %d\n", signal);

    //Disconnect from the server
    std::string BYEmsg = "BYE";
    sendMessage(s.socketID, BYEmsg);
    close(s.socketID);

    freeaddrinfo(s.res); // free the linked-list

    //Temp, need to do proper clean up of stuff
    exit(1); 
}

void handleMessages()
{
    std::string msg;

    //std::cout << "Begin2" << std::endl;
    while (1) {
        msg = recvMessage(s.socketID);
        
        std::cout << msg << std::endl;
        //printf("%s", msg.c_str());
        //std::cout << "Begin5" << std::endl;
    }
    //std::cout << "Begin6" << std::endl;
}

int main(int argc, char* argv[]) 
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = closeConnection;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);


    setupSocket("127.0.0.1", &s, false);

    connect(s.socketID, s.res->ai_addr, s.res->ai_addrlen);

    std::thread incoming(handleMessages);

    while (1) {
        std::string msg;
        getline(std::cin, msg);
        //std::cout << "The messaged being send is: " << msg << std::endl;
        sendMessage(s.socketID, msg);
    }
}