#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>
#include <signal.h>
#include <unistd.h>
#include <mutex>
#include <algorithm>

#include "library.h"

struct Client {
    int socketID;
    std::string name;
};

bool isServerRunning = true;
std::mutex mtx;
std::vector<Client> socketIDs;

void handleClient(int socketID)
{
    //Nick name of this client
    std::string nickName;

    std::string HELLOmsg = "HELLO";
    sendMessage(socketID, HELLOmsg);

    std::string NICKmsg = "Please select a nickname (NICK <yourName>)";
    while (1) {
        //Nick name selection
        sendMessage(socketID, NICKmsg);
        //Wait for responce
        std::string res = recvMessage(socketID);
        //std::cout << "client: " << res.substr(0, 4) << std::endl;
        if (res.substr(0, 4) == "NICK") {
            nickName = res.substr(5, res.size());
            //Check if it is unique
            bool isUnique = true;
            mtx.lock();
            for (int i = 0; i < socketIDs.size(); i++) {
                if (socketIDs[i].name == nickName) {
                    sendMessage(socketID, "RETRY");
                    isUnique = false;
                    break;
                }
            }
            mtx.unlock();
            if (isUnique) {
                mtx.lock();
                //Set nickname
                for (int i = 0; i < socketIDs.size(); i++) {
                    if (socketIDs[i].socketID == socketID) {
                        socketIDs[i].name = nickName;
                    }
                }
                mtx.unlock();
                //READY response
                sendMessage(socketID, "READY");

                break;
            }
        }
        sendMessage(socketID, "invalid command, try again.");
    }

    //Loop forever getting messages
    std::string msg;
    while (1) {
        msg = recvMessage(socketID);
        if (msg == "BYE") {
            //Remove the client
            mtx.lock();
            for (int i = 0; i < socketIDs.size(); i++) {
                if (socketIDs[i].socketID != socketID) {
                    socketIDs.erase(socketIDs.begin() + i);
                }
            }
            mtx.unlock();
            close(socketID);
            break;
        }
        std::cout << msg << std::endl;
        //Send the message to all other clients
        mtx.lock();
        for (int i = 0; i < socketIDs.size(); i++) {
            if (socketIDs[i].socketID != socketID) {
                std::string namePlusMsg = nickName + ": " + msg;
                sendMessage(socketIDs[i].socketID, namePlusMsg);
            }
        }
        mtx.unlock();
    }
    while(1) {}
}

void closeServer(int s)
{
    printf("Caught signal %d\n",s);
    isServerRunning = false;

    //Temp, need to do proper clean up of stuff
    exit(1); 
}

int main() 
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = closeServer;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    struct sockaddr_storage their_addr;

    Socket s;

    setupSocket("NULL", &s, true);

    if (bind(s.socketID, s.res->ai_addr, s.res->ai_addrlen) == -1) {
        printf("Error at bind\n");
        exit(1);
    }

    if (listen(s.socketID, 10) == -1) {
        printf("Error at listen\n");
        exit(1);
    }

    std::vector<std::thread*> threads;
    socklen_t addr_size = sizeof(their_addr);
    while (isServerRunning) {
        int new_fd = accept(s.socketID, (struct sockaddr*)&their_addr, &addr_size);

        Client c;
        c.name = "Anonomous";
        c.socketID = new_fd;
        mtx.lock();
        socketIDs.push_back(c);
        mtx.unlock();

        std::thread* client = new std::thread(handleClient, new_fd);
        threads.push_back(client);
    }

    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }

    freeaddrinfo(s.res); // free the linked-list
    exit(0);
}