#include "./protocol.h"
#include "../../header/stdhead.h"

/*
    这里提供的函数支持把 buf 和 协议 之间互相转换
*/
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


/*
    一些工具函数
*/
// 获取协议体的大小
int getBodySize(const ProtocolBody &body);
void printProtocol(const ProtocolHeader &header, const ProtocolBody &body);
void printProtocol(CMD cmd , void * data);