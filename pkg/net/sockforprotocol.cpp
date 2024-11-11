#include "sockforprotocol.h"
#include <cstring>

// 读出协议头
int readHeader(SOCKNODE *node, ProtocolHeader &header) {
    char buf[sizeof(ProtocolHeader)] = {};
    int n = recvMsg(node, buf, sizeof(ProtocolHeader));
    if (n == 0) {
        return 0;
    }
    if (n != sizeof(ProtocolHeader)) {
        ERROR_INFO_ERRNO_SOCKNODE_ADD("recv header error" ,  node);
        return -1;
    }
    parseHeader(buf, header);
    return 0;
}

// 读出协议体
int readBody(SOCKNODE *node, ProtocolHeader &header, ProtocolBody &body){
    char buf[1024] = {};
    int n = recvMsg(node, buf, header.len);
    if (n == 0) {
        return 0;
    }
    if (n != header.len) {
        ERROR_INFO_ERRNO_SOCKNODE_ADD("recv body error" ,  node);
        return -1;
    }
    parseBody(buf, body);
    return 0;
}

// 处理协议
int dealProtocol(SOCKNODE *node , ProtocolHeader &header, ProtocolBody &body){
    switch (header.cmd) {
        case CMD_LOGIN:
            return dealLogin(node, body);
        case CMD_LOGOUT:
            return dealLogout(node, body);
        case CMD_HEART:
            return dealHeart(node, body);
        case CMD_MSG:
            return dealMsg(node, body);
        default:
            ERROR_INFO_ADD("unknow cmd" );
            return -1;
    }
}






/**************具体协议处理  */
// 登录
// 发送登录请求
int sendLogin(SOCKNODE *node, const char *name, int namelen){
    ProtocolBody body;
    body.numParts = 1;
    body.lenParts.push_back(namelen);
    body.data.push_back(std::string(name, namelen));

    ProtocolHeader header;
    header.len = sizeof(body);
    header.cmd = CMD_LOGIN;
    
    char buf[1024] = {};
    packProtocol(buf, header, body);
    sendMsg(node, buf, sizeof(header) + sizeof(body) );
    return 0;
}
// 处理登录请求
int dealLogin(SOCKNODE *node, ProtocolBody &body){
    return 0;
}

// 登出
// 发送登出请求
int sendLogout(SOCKNODE *node, const char *name, int namelen){
    ProtocolBody body;
    body.numParts = 1;
    body.lenParts[0] = namelen;
    memcpy(body.data[0],name , namelen);

    ProtocolHeader header;
    header.len = sizeof(body);
    header.cmd = CMD_LOGOUT;
    
    char buf[1024] = {};
    packProtocol(buf, header, body);
    sendMsg(node, buf, sizeof(header) + sizeof(body) );
    return 0;
}
// 处理登出请求
int dealLogout(SOCKNODE *node, ProtocolBody &body){
    return 0;

}

// 心跳
// 发送心跳包
int sendHeart(SOCKNODE *node){
    ProtocolBody body;
    body.numParts = 0;

    ProtocolHeader header;
    header.len = sizeof(body);
    header.cmd = CMD_HEART;
    
    char buf[1024] = {};
    packProtocol(buf, header, body);
    sendMsg(node, buf, sizeof(header) + sizeof(body) );
    return 0;
}
// 处理心跳包
int dealHeart(SOCKNODE *node, ProtocolBody &body){
    return 0;
}

// 消息
// 发送消息
int sendMsg(SOCKNODE *node, const char *name, int namelen, const char *msg, int msglen){
    ProtocolBody body;
    body.numParts = 2;
    body.lenParts[0] = namelen;
    body.lenParts[1] = msglen;
    memcpy(body.data[0], name , namelen);
    memcpy(body.data[1], msg , msglen);

    ProtocolHeader header;
    header.len = sizeof(body);
    header.cmd = CMD_MSG;
    
    char buf[1024] = {};
    packProtocol(buf, header, body);
    sendMsg(node, buf, sizeof(header) + sizeof(body) );
    return 0;
}

// 处理消息
int dealMsg(SOCKNODE *node, ProtocolBody &body){
    return 0;
}