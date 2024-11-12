#include "./protocol.h"
#include "./protocolhelper.h"
#include "./protocoltransform.h"
/*
    一些工具函数
*/
// 获取协议体的大小
int getBodySize(const ProtocolBody &body) {
    int size = 4;
    for (int i = 0; i < body.numParts; i++) {
        size += 4 + body.lenParts[i];
    }
    return size;
}

// 打印协议信息
void printProtocol(const ProtocolHeader &header, const ProtocolBody &body){
    printf("ProtocolHeader:\n");
    printf("len: %d\n", header.len);
    printf("cmd: %d\n", header.cmd);
    printf("ProtocolBody:\n");
    printf("numParts: %d\n", body.numParts);
    for (int i = 0; i < body.numParts; i++) {
        printf("lenParts[%d]: %d\n", i, body.lenParts[i]);
        printf("data[%d]: %s\n", i, body.data[i]);
    }
    printf("\n");
}

// 打印协议信息
void printProtocol(CMD cmd , void * data){
    ProtocolBody body;
    packProtocolBody(body , cmd , data);
    printf("ProtocolBody:\n");
    printf("numParts: %d\n", body.numParts);
    for (int i = 0; i < body.numParts; i++) {
        printf("lenParts[%d]: %d\n", i, body.lenParts[i]);
        printf("data[%d]: %s\n", i, body.data[i]);
    }
}

