#include "./server_read.h"
#include "../../pkg/net/socknode.h"
#include "../../server/server_global/server_global.h"


void * dealAcceptConn(void* arg){
    SOCKNODE *sock = (SOCKNODE *)arg;
    SOCKNODE *newnode = acceptConn(sock, "", strlen(""));

    FullSocketInfo(newnode);
    newnode->name[0] = '\0';

    // 刚刚连接的时候放到池子里面不进行处理
    sockmapUnlogin[sock->connfd] = newnode;
    max_sd = std::max(max_sd, newnode->connfd);
    FD_SET(newnode->connfd, &readfds);
    return nullptr;
}
