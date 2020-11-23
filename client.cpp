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
#define DEFAULT_PORT "3490"

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
	
	char* portnumber;
	std::string def_port = DEFAULT_PORT;
	
	//if 2 arguments set argument 2 to the port number
	//if 1 argument, use default port number
	//if too many arguments, print usage statement and quit
	if (argc == 2){
	portnumber = argv[1];	
	}
	else if (argc > 2){
	printf("\nusage: %s <portnumber>\n\n", argv[0]);
	exit(1);
	}
	else if (argc <2){
	portnumber = strcpy(new char[def_port.length() + 1], def_port.c_str());
	}

    setupSocket("127.0.0.1", &s, false, portnumber);

	//added error checking for connect
    if (connect(s.socketID, s.res->ai_addr, s.res->ai_addrlen) < 0){
		perror("Error at connect:");
		exit(1);
	}
		
    std::thread incoming(handleMessages);

    while (1) {
        std::string msg;
        getline(std::cin, msg);
        //std::cout << "The messaged being send is: " << msg << std::endl;
        sendMessage(s.socketID, msg);
    }
}
