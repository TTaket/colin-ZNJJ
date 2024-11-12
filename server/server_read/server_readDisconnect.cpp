#include "./server_read.h"
#include "../../server/server_global/server_global.h"


void Disconnect(SOCKNODE * node){
    //close connection
    if(node->name[0] != '\0'){
        sysPrint("[%s] disconnected", node->name);
    }
    if(lastHeartTime.find(std::string(node->name)) != lastHeartTime.end()){
        lastHeartTime.erase(lastHeartTime.find(std::string(node->name)));
    }
    if(sockmap.find(std::string(node->name)) != sockmap.end()){
        sockmap.erase(sockmap.find(std::string(node->name)));
    }
    if(sockmapUnlogin.find(node->connfd) != sockmapUnlogin.end()){
        sockmapUnlogin.erase(sockmapUnlogin.find(node->connfd));
    }

    if(lastHeartTimeUnlogin.find(node->connfd) != lastHeartTimeUnlogin.end()){
        lastHeartTimeUnlogin.erase(lastHeartTimeUnlogin.find(node->connfd));
    }

    // fd
    FD_CLR(node->connfd, &readfds);

    closeSocket(node);
    updateMaxSD();
}