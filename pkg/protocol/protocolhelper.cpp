#include "./protocolhelper.h"

// 解析协议头
int parseHeader(const char *bufheader, ProtocolHeader &header) {
    header.len = *(uint32_t*)bufheader;
    header.cmd = *(uint32_t*)(bufheader + 4);
    return 0;
}

// 解析协议体
int parseBody(const char *bufbody, ProtocolBody &body) {
    int bodypartnum = 0;
    if (body.data.size() >= 4) {
        bodypartnum = *(int*)bufbody;
    }
    for (int i = 0; i < bodypartnum; i++) {
        int partlen = *(int*)(bufbody + 4 + i * 4);
        body.lenParts.push_back(partlen);
    }
    int offset = 4 + 4 * bodypartnum;
    for (int i = 0; i < bodypartnum; i++) {
        body.data.push_back(std::string(bufbody + offset, body.lenParts[i]));
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
    int bodypartnum = body.data.size();
    memcpy(buf, &bodypartnum, 4);
    int offset = 4;
    for (int i = 0; i < bodypartnum; i++) {
        int partlen = body.data[i].size();
        memcpy(buf + offset, &partlen, 4);
        offset += 4;
    }
    for (int i = 0; i < bodypartnum; i++) {
        memcpy(buf + offset, body.data[i].c_str(), body.data[i].size());
        offset += body.data[i].size();
    }
    return 0;
}

//封装协议
int packProtocol(char *buf, const ProtocolHeader &header, const ProtocolBody &body) {
    packHeader(buf, header);
    packBody(buf + sizeof(ProtocolHeader), body);
    return 0;
}