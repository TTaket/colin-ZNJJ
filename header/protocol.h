
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 8159
#define SERVER_IP "106.54.203.31"
//#define SERVER_IP "127.0.0.1"

#define PROTOCOL_MAX_PARTLEN 10
#define PROTOCOL_MAX_PARTSIZE 1024
// 协议的格式
// 8字节的包头
struct ProtocolHeader {
    uint32_t len; // 包体的长度
    uint32_t cmd; // 命令
};

struct ProtocolBody {
    uint32_t numParts; // 分为几部分
    int lenParts[PROTOCOL_MAX_PARTLEN]; // 每部分的长度
    char data[PROTOCOL_MAX_PARTLEN][PROTOCOL_MAX_PARTSIZE]; // 每部分的内容
};

// 命令的定义
enum CMD {
    //控制信号
    CMD_OK,
    CMD_ERROR,
    
    //系统信号
    CMD_HEART,

    //功能信号
    CMD_LOGIN,
    CMD_LOGOUT,
    CMD_MSG,
};

// 命令的具体内容
// TODO可以加jwt身份验证
struct CMD_LOGIN_BODY {
    char name[256];
};

struct CMD_LOGOUT_BODY {
    char name[256];
};

struct CMD_MSG_BODY {
    char tarname[256];
    char msg[1024];
};
