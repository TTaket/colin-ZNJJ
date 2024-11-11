#include "../../header/stdhead.h"
#include "../error/myerror.h"
#include "./socknode.h"
#include <cstdio>
#include <cstring>
#include <algorithm>

bool setBlock(SOCKNODE *node){
    int flags = fcntl(node->connfd, F_GETFL, 0);
    fcntl(node->connfd, F_SETFL, flags & ~O_NONBLOCK);
    
    return isblock(node);
}
bool setNoBlock(SOCKNODE *node){
    int flags = fcntl(node->connfd, F_GETFL, 0);
    fcntl(node->connfd, F_SETFL, flags | O_NONBLOCK);

    return !isblock(node);
}
bool isblock(SOCKNODE *node){
    int flags = fcntl(node->connfd, F_GETFL, 0);
    if(flags & O_NONBLOCK){
        return false;
    }
    return true;
}

//发送数据
int sendMsg(SOCKNODE *node,const char *buf, int len ){
    if (isblock(node)) {
        int ret = send(node->connfd, buf, len , 0);
        if (ret == -1)
        {
            ERROR_INFO_ERRNO_SOCKNODE_ADD("send block err", node);
            return -1;
        }
        return ret;
    }else{
        //非阻塞的send 行为会是一直写 写到写完
        int sent_bytes = 0;
        int ret = 0;
        while (true)
        {
            ret = send(node->connfd, buf + sent_bytes, len - sent_bytes , 0);
            if(ret > 0){
                usleep(1);
                sent_bytes += ret;
                if (sent_bytes == len){
                    return sent_bytes;
                }
            }
            else if (ret == 0)
            {
                ERROR_INFO_ERRNO_SOCKNODE_ADD("send err 0 ", node);
                return -1;
            }else{
                if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
                {
                    usleep(1);
                    continue;
                }             
                else{
                    ERROR_INFO_ERRNO_SOCKNODE_ADD("send err", node);
                    return -1;
                }
            }
        }
    }
}
//接收数据并放入缓冲区
int recvMsg(SOCKNODE *node, char *buf, int len) {
    if (isblock(node)) {
        int ret = recv(node->connfd, buf, len, 0);
        if (ret == -1) {
            ERROR_INFO_ERRNO_SOCKNODE_ADD("recv block err", node);
            return -1;
        } else if (ret == 0) {// 对端关闭连接
            return 0;
        }
        return ret;
    } else { 
        //非阻塞的读 可能读不完
        int recv_bytes = 0;
        int ret = 0;
        while (true)
        {
            ret = recv(node->connfd, buf + recv_bytes, len - recv_bytes, 0);
            if (ret > 0) {
                recv_bytes += ret;
                if (recv_bytes == len){
                    return recv_bytes;
                }
            } else if (ret == 0) {// 对端关闭连接
                return 0;
            } else {
                if (errno == EAGAIN || errno == EWOULDBLOCK){
                    break; //非阻塞的读取干净了
                } else if(errno == EINTR){
                    continue;
                } else {
                    // 其他错误，返回失败
                    ERROR_INFO_ERRNO_SOCKNODE_ADD("recv err", node);
                    return -1;
                }
            }
        }
    }
}



//创建套接字
SOCKNODE * createSocket( char* name , int namelen){
    SOCKNODE *node = new SOCKNODE();
    node->connfd = socket(AF_INET, SOCK_STREAM, 0);
    if(node->connfd == -1){
        ERROR_INFO_ERRNO_ADD("err create socket");
        return NULL;
    }
    memcpy(node->name , name , namelen);
    node->name[namelen] = '\0';
    return node;
}

SOCKNODE * createSocketByConnfd(char* name , int namelen , int connfd){
    SOCKNODE *node = new SOCKNODE();
    node->connfd = connfd;
    if(node->connfd == -1){
        ERROR_INFO_ADD("Inited connfd is -1");
        return NULL;
    }
    memcpy(node->name , name , namelen);
    node->name[namelen] = '\0';
    return node;
}


int FullSocketInfo(SOCKNODE *node){
    if(node->connfd == -1){
        ERROR_INFO_ADD("Init connfd is -1");
        return -1;
    }

    //初始化 addr
    if(node->addr_len == -1){
        node->addr_len = sizeof(node->addr);
        int ret = getsockname(node->connfd, (struct sockaddr *)&node->addr, &node->addr_len);
        if(ret == -1){
            ERROR_INFO_ERRNO_ADD("getsockname error");
            return -1;
        }
    }
    
    //详细信息
    
    char * tip = inet_ntoa(node->addr.sin_addr);
    memcpy(node->ip , tip , strlen(tip));

    node->port = ntohs(node->addr.sin_port);
    
    return 0;
}

//连接
int ConnSocket(SOCKNODE *node, const char *ip, int port){
    struct sockaddr_in addr_ser;
    addr_ser.sin_addr.s_addr = inet_addr(ip);
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_port = htons(port);
    int ret = connect(node->connfd, (struct sockaddr*)&addr_ser, sizeof(addr_ser));
    if(ret == -1){
        ERROR_INFO_ERRNO_ADD("socket conn error");
        return -1;
    }
    return 0;
}

//绑定监听
int bindListen(SOCKNODE *node, int port){
    int opt = 1;
    if (setsockopt(node->connfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return -1;
    }

    if(node->connfd == -1){
        ERROR_INFO_ERRNO_ADD("invalid socket");
        return -1;
    }
    struct sockaddr_in addr_ser;
    addr_ser.sin_addr.s_addr = INADDR_ANY;
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_port = htons(port);
    int ret = bind(node->connfd , (struct sockaddr*)&addr_ser , sizeof(addr_ser));
    if(ret == -1){
        ERROR_INFO_ERRNO_ADD("socket bind error");
        return -1;
    }
    if (listen(node->connfd, 5) == -1) {
        ERROR_INFO_ERRNO_ADD("socket listen error");
        return -1;
    }
    return 0;
}

//接受连接
SOCKNODE * acceptConn(SOCKNODE *node , char *name, int namelen){
    struct sockaddr_in addr_cli;
    socklen_t len = sizeof(addr_cli);
    int connfd = accept(node->connfd, (struct sockaddr*)&addr_cli, &len);
    if(connfd == -1) {
        ERROR_INFO_ERRNO_ADD("socket accept error");
        return NULL;
    }
    SOCKNODE *newNode = createSocketByConnfd(name , namelen, connfd);
    if(newNode == NULL){
        ERROR_INFO_ADD("createSocketByConnfd error");
        return NULL;
    }
    return newNode;
}

//关闭连接
int closeSocket(SOCKNODE *node){
    node->connfd = -1;
    close(node->connfd);
    return 0;
}



