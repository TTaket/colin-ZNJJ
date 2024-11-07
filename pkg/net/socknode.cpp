#include "../../header/stdhead.h"
#include "../error/myerror.h"
#include "./socknode.h"
#include <cstring>

//获取发送缓冲区大小
int getSendBufSize(SOCKNODE *node){
    if(node->sendTail >= node->sendHead){
        return node->sendTail - node->sendHead;
    } else {
        return SEND_BUF_SIZE - node->sendHead + node->sendTail;
    }
}
//获取接收缓冲区大小
int getRecvBufSize(SOCKNODE *node){
    if(node->recvTail >= node->recvHead){
        return node->recvTail - node->recvHead;
    } else {
        return RECV_BUF_SIZE - node->recvHead + node->recvTail;
    }
}
//获取发送缓冲区剩余空间
int getSendBufRemain(SOCKNODE *node){
    return SEND_BUF_SIZE - getSendBufSize(node) - 1;//-1是为了区分满和空
}
//获取接收缓冲区剩余空间
int getRecvBufRemain(SOCKNODE *node){
    return RECV_BUF_SIZE - getRecvBufSize(node) - 1;//-1是为了区分满和空
}
//数据放入到发送缓冲区
int putSendBuf(SOCKNODE *node, const char *buf, int len){
    int len1 = getSendBufSize(node);
    if(getSendBufRemain(node) < len){
        ERROR_INFO_ADD("send buffer is full");
        return -1;//缓冲区满
    }
    if(node->sendTail + len < SEND_BUF_SIZE){
        memcpy(node->sendBuf + node->sendTail, buf, len);
        memcpy(node->sendBuf + SEND_BUF_SIZE + node->sendTail, buf, len);
        node->sendTail += len;
    } else {
        int len1 = SEND_BUF_SIZE - node->sendTail;
        memcpy(node->sendBuf + node->sendTail, buf, len1);
        memcpy(node->sendBuf + SEND_BUF_SIZE + node->sendTail, buf, len1);
        int len2 = len - len1;
        memcpy(node->sendBuf, buf + len1, len2);
        memcpy(node->sendBuf + SEND_BUF_SIZE, buf + len1, len2);
        node->sendTail = len2;
    }
    int len2 = getSendBufSize(node);
    return len2 - len1;
}
//数据放入到接收缓冲区
int putRecvBuf(SOCKNODE *node, const char *buf, int len){
    int len1 = getRecvBufSize(node);
    if(getRecvBufRemain(node) < len){
        return -1;//缓冲区满
    }
    if(node->recvTail + len < RECV_BUF_SIZE){
        memcpy(node->recvBuf + node->recvTail, buf, len);
        memcpy(node->recvBuf + RECV_BUF_SIZE + node->recvTail, buf, len);
        node->recvTail += len;
    } else {
        int len1 = RECV_BUF_SIZE - node->recvTail;
        memcpy(node->recvBuf + node->recvTail, buf, len1);
        memcpy(node->recvBuf + RECV_BUF_SIZE + node->recvTail, buf, len1);
        int len2 = len - len1;
        memcpy(node->recvBuf, buf + len1, len2);
        memcpy(node->recvBuf + RECV_BUF_SIZE, buf + len1, len2);
        node->recvTail = len2;
    }
    int len2 = getRecvBufSize(node);
    return len2 - len1;
}
//从发送缓冲区取出数据
int getSendBuf(SOCKNODE *node, char *buf, int len){
    int len1 = getSendBufRemain(node);
    if(len == -1){
        len = getSendBufSize(node);
    }
    if(getSendBufSize(node) < len){
        return -1;//缓冲区数据不足
    }
    if(node->sendHead + len < SEND_BUF_SIZE){
        memcpy(buf, node->sendBuf + node->sendHead, len);
        node->sendHead += len;
    } else {
        int len1 = SEND_BUF_SIZE - node->sendHead;
        memcpy(buf, node->sendBuf + node->sendHead, len1);
        int len2 = len - len1;
        memcpy(buf + len1, node->sendBuf, len2);
        node->sendHead = len2;
    }
    int len2 = getSendBufRemain(node);
    return len1 - len2;
}
//从接收缓冲区取出数据
int getRecvBuf(SOCKNODE *node, char *buf, int len){
    int len1 = getRecvBufRemain(node);
    if(len == -1){
        len = getRecvBufSize(node);
    }
    if(getRecvBufSize(node) < len){
        return -1;//缓冲区数据不足
    }
    if(node->recvHead + len < RECV_BUF_SIZE){
        memcpy(buf, node->recvBuf + node->recvHead, len);
        node->recvHead += len;
    } else {
        int len1 = RECV_BUF_SIZE - node->recvHead;
        memcpy(buf, node->recvBuf + node->recvHead, len1);
        int len2 = len - len1;
        memcpy(buf + len1, node->recvBuf, len2);
        node->recvHead = len2;
    }
    int len2 = getRecvBufRemain(node);
    return len1 - len2;
}

//执行发送
int doSend(SOCKNODE *node , int slen){
    int len = (slen == -1) ? getSendBufSize(node) : slen;
    if(len == 0) return 0;
    char buf[SEND_BUF_SIZE]={};//这里的空间可以优化 现在有太多拷贝
    getSendBuf(node, buf, len);
    buf[len] = '\0';
    int ret = send(node->connfd, buf, len, 0);
    return ret;
}

//执行接收
int doRecv(SOCKNODE *node , int rlen){
    int len = (rlen == -1) ? getRecvBufRemain(node) : rlen;
    if(len == 0) return 0;
    char buf[RECV_BUF_SIZE]={};//这里的空间可以优化 现在有太多拷贝
    int ret = recv(node->connfd, buf, len, 0);
    if(ret <= 0) return -1;
    putRecvBuf(node, buf, ret);
    return 0;
}

//发送数据 放入缓冲区并发送
int sendMsg(SOCKNODE *node,const char *buf, int len ){
    if(putSendBuf(node, buf, len) == -1){
        return -1;
    }
    return doSend(node);
}

//接收数据 刷新缓冲区数据 并且从缓冲区取出
int recvMsg(SOCKNODE *node, char *buf, int len){
    if(doRecv(node) == -1){
        return -1;
    }
    if(getRecvBuf(node, buf, len) == -1){
        return -1;
    }
    return 0;
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
    if(node->sendHead != node->sendTail || node->recvHead != node->recvTail){
        ERROR_INFO_ADD("Init send or recv buffer is not empty");
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
    node->sendHead = node->sendTail = 0;
    node->recvHead = node->recvTail = 0;
    close(node->connfd);
    return 0;
}



