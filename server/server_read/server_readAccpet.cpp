#include "./server_read.h"


void * dealAcceptConn(void* arg){
    SOCKNODE *sock = (SOCKNODE *)arg;
    SOCKNODE *newnode = acceptConn(sock, "", strlen(""));
    sendMsg(newnode, "enter your name please", strlen("enter your name please"));
    int readlen = recvMsg(newnode, newnode->name, sizeof(newnode->name));
    while (sockmap.find(newnode->name) != sockmap.end() || readlen == 0 || newnode->name[0] == '/') {

        if (readlen == 0) 
        {
            closeSocket(newnode);
            return nullptr;
        }else if(strcmp(newnode->name, "/heart") == 0)
        {   
            //心跳包 继续接受
        }else if(newnode->name[0] == '/'){
            sendMsg(newnode, "Invalid name", strlen("Invalid name"));
        }
        else
        {
            sendMsg(newnode, "Name already exists", strlen("Name already exists"));
        }
        memset(newnode->name ,'\0' , sizeof newnode->name); 
        readlen = recvMsg(newnode, newnode->name, sizeof(newnode->name));
    }
    if(readlen == 0){
        closeSocket(newnode);
        return nullptr;
    }
    FullSocketInfo(newnode);
    sockmap[newnode->name] = newnode;
    FD_SET(newnode->connfd, &readfds);
    max_sd = std::max(max_sd, newnode->connfd);
    std::string retword = std::string("欢迎连接server : ") + newnode->name;
    sendMsg(newnode, retword.c_str(), retword.size());
    sysPrint("[%s] connected from %s", newnode->name , newnode->ip);
    return nullptr;
}

