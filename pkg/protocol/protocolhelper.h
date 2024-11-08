#include "../../header/protocol.h"
#include "../../header/stdhead.h"

// 解析协议头
int parseHeader(const char *buf, ProtocolHeader &header);

// 解析协议体
int parseBody(const char *bufbody, ProtocolBody &body);

//封装协议头
int packHeader(char *buf, const ProtocolHeader &header);

//封装协议体
int packBody(char *buf, const ProtocolBody &body);

//封装协议
int packProtocol(char *buf, const ProtocolHeader &header, const ProtocolBody &body);