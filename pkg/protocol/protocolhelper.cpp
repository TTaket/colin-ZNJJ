#include "./protocolhelper.h"
#include "./protocol.h"
#include <cstring>

// 解析协议头
int parseHeader(const char *bufheader, ProtocolHeader &header) {
    header.len = *(uint32_t*)bufheader;
    header.cmd = *(CMD*)(bufheader + 4);
    return 0;
}

// 解析协议体
int parseBody(const char *bufbody, ProtocolBody &body) {
    body.numParts = *(int*)bufbody;
    int offset = 4;
    for (int i = 0; i < body.numParts; i++) {
        body.lenParts[i] = *(int*)(bufbody + offset);
        offset += 4;
    }
    for (int i = 0; i < body.numParts; i++) {
        memcpy(body.data[i], bufbody + offset, body.lenParts[i]);
        offset += body.lenParts[i];
    }
    return 0;
}


//封装协议头
int packHeader(char *buf, const ProtocolHeader &header) {
    memcpy(buf, &header, sizeof(ProtocolHeader));
    return 0;
}

//封装协议体
int packBody(char *buf, const ProtocolBody &body) {
    memcpy(buf, &body.numParts, 4);
    int offset = 4;
    for (int i = 0; i < body.numParts; i++) {
        memcpy(buf + offset, &body.lenParts[i], 4);
        offset += 4;
    }
    for (int i = 0; i < body.numParts; i++) {
        memcpy(buf + offset, body.data[i], body.lenParts[i]);
        offset += body.lenParts[i];
    }
    return 0;
}

//封装协议
int packProtocol(char *buf, const ProtocolHeader &header, const ProtocolBody &body) {
    packHeader(buf, header);
    packBody(buf + sizeof(ProtocolHeader), body);
    return 0;
}

