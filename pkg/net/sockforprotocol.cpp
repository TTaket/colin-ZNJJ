#include "./sockforprotocol.h"
#include "../protocol/protocolhelper.h"
#include "../protocol/protocolhelper.h"
#include "../protocol/protocol.h"
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
    return n;
}

// 读出协议体
int readBody(SOCKNODE *node, const ProtocolHeader & header, ProtocolBody &body){
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
    return n;
}

// 发送协议头
int sendHeader(SOCKNODE *node,const ProtocolHeader &header){
    char buf[sizeof(ProtocolHeader)] = {};
    packHeader(buf, header);
    int n = sendMsg(node, buf, sizeof(ProtocolHeader));
    if (n != sizeof(ProtocolHeader)) {
        ERROR_INFO_ERRNO_SOCKNODE_ADD("send header error" ,  node);
        return -1;
    }
    return n;
}

// 发送协议体
int sendBody(SOCKNODE *node, const ProtocolHeader & header ,  const ProtocolBody &body){
    char buf[1024] = {};
    packBody(buf, body);
    int n = sendMsg(node, buf, header.len);
    if (n != header.len) {
        ERROR_INFO_ERRNO_SOCKNODE_ADD("send body error" ,  node);
        return -1;
    }
    return n;
}

// 读出一帧消息
int readProtoMSG(SOCKNODE *node, CMD &cmd , void* data){
    ProtocolHeader header;
    ProtocolBody body;
    int n1 = readHeader(node, header);
    if (n1 <= 0) {
        return n1;
    }
    int n2 = readBody(node, header, body);
    if (n2 <= 0) {
        return n2;
    }
    int ret = transformProtocolBody(body, header.cmd , data);
    if(ret != 0){
        return -1;
    }
    cmd = header.cmd;
    return n1 + n2 ;
}

// 发送一帧消息
int sendProtoMSG(SOCKNODE *node, CMD cmd , void* data){
    ProtocolHeader header;
    ProtocolBody body;
    int ret = transformProtocolBody(body, cmd , data);
    if(ret != 0){
        return -1;
    }
    header.cmd = cmd;
    header.len = sizeof(body);
    int n1 = sendHeader(node, header);
    if(n1 <= 0){
        return -1;
    }
    int n2 = sendBody(node , header, body);
    if(n2 <= 0){
        return -1;
    }
    return n1 + n2;
}