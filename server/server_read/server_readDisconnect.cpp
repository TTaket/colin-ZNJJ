#include "./server_read.h"


void Disconnect(SOCKNODE * node){
    //close connection
    sysPrint("[%s] disconnected", node->name);
    if(lastHeartTime.find(std::string(node->name)) != lastHeartTime.end()){
        lastHeartTime.erase(lastHeartTime.find(std::string(node->name)));
    }
    if(sockmap.find(std::string(node->name)) != sockmap.end()){
        sockmap.erase(sockmap.find(std::string(node->name)));
    }

    // fd
    FD_CLR(node->connfd, &readfds);

    closeSocket(node);
}