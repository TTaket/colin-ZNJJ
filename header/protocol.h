#include <stdio.h>
#include <cstdint>
#include <vector>
#include <string>

#define SERVER_PORT 8159
#define SERVER_IP "192.168.10.115"

// 协议的格式
// 8字节的包头
struct ProtocolHeader {
    uint32_t len; // 包体的长度
    uint32_t cmd; // 命令
};

struct ProtocolBody {
    uint32_t numParts; // 分为几部分
    std::vector<int> lenParts; // 每部分的长度
    std::vector<std::string > data; // 每部分的内容
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
    std::string name;
};

struct CMD_LOGOUT_BODY {
    std::string name;
};

struct CMD_MSG_BODY {
    std::string tarname;
    std::string msg;
};