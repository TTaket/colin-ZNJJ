#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define PROTOCOL_MAX_PARTLEN 10
#define PROTOCOL_MAX_PARTSIZE 1024


// 命令的定义
enum CMD {
    //功能信号
    //用户登录
    CMD_USER_LOGIN,
    CMD_USER_LOGIN_RESP,
    //用户登出
    CMD_USER_LOGOUT,
    CMD_USER_LOGOUT_RESP,
    //设备登录（设备登录 有设备名 设备密码）
    CMD_DEV_LOGIN,
    CMD_DEV_LOGIN_RESP,
    //设备登出
    CMD_DEV_LOGOUT,
    CMD_DEV_LOGOUT_RESP,
    //设备和用户和服务器的心跳
    CMD_HEART,
    CMD_HEART_RESP,
    //消息 从用户到设备 ,用户自定义消息
    CMD_MSG,
    CMD_MSG_RESP,
    //服务器给用户和设备的通知 ,服务器自定义消息
    CMD_NOTICE,
    CMD_NOTICE_RESP,

    //用户添加设备（用户把某一个名字的设备绑定在自己名下）
    CMD_USER_ADD_DEV,
    CMD_USER_ADD_DEV_RESP,
    //用户删除设备（用户把某一个名字的设备从自己名下删除）
    CMD_USER_DEL_DEV,
    CMD_USER_DEL_DEV_RESP,
    //用户获取设备列表
    CMD_GETLIST,
    CMD_GETLIST_RESP,
    //用户获取设备状态
    CMD_GETSTATUS,
    CMD_GETSTATUS_RESP,

    //echo
    CMD_ECHO,
    CMD_ECHO_RESP,
};
enum CMD_STATUS {
    CMD_OK_RESP,
    CMD_ERROR_RESP,
};
enum CMD_DEV_STATUS {
    CMD_DEV_ONLINE,
    CMD_DEV_OFFLINE,
};

// 协议的格式
// 8字节的包头
typedef struct ProtocolHeader {
    uint32_t len; // 包体的长度
    CMD cmd; // 命令
}ProtocolHeader;

typedef struct ProtocolBody {
    uint32_t numParts; // 分为几部分
    int lenParts[PROTOCOL_MAX_PARTLEN]; // 每部分的长度
    char data[PROTOCOL_MAX_PARTLEN][PROTOCOL_MAX_PARTSIZE]; // 每部分的内容
}ProtocolBody;


// 命令的具体内容
// TODO可以加jwt身份验证
struct CMD_USER_LOGIN_BODY{
    char name[256];
    char pwd[256];
};
struct CMD_USER_LOGIN_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_USER_LOGOUT_BODY {
    char name[256];
};
struct CMD_USER_LOGOUT_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_DEV_LOGIN_BODY {
    char name[256];
    char pwd[256];
};
struct CMD_DEV_LOGIN_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_DEV_LOGOUT_BODY {
    char name[256];
};
struct CMD_DEV_LOGOUT_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_HEART_BODY {
    //心跳包没有内容
};
struct CMD_HEART_RESP_BODY {
    //心跳包没有内容
};
struct CMD_MSG_BODY {
    char name[256];
    char msg[1024];
};
struct CMD_MSG_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_NOTICE_BODY {
    char msg[1024];
};
struct CMD_NOTICE_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_USER_ADD_DEV_BODY {
    char devname[256];
};
struct CMD_USER_ADD_DEV_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_USER_DEL_DEV_BODY {
    char devname[256];
};
struct CMD_USER_DEL_DEV_RESP_BODY {
    CMD_STATUS cmdstatus;
    char msg[256];
};
struct CMD_GETLIST_BODY {
};
struct CMD_GETLIST_RESP_BODY {
    CMD_STATUS cmdstatus;
    int num;
    char devname[256][256];
};
struct CMD_GETSTATUS_BODY {
};
struct CMD_GETSTATUS_RESP_BODY {
    CMD_STATUS cmdstatus;
    int num;
    char devname[256][256];
    CMD_DEV_STATUS devStatus[256];
};
struct CMD_ECHO_BODY {
    char devname[256];
    char msg[1024];
};
struct CMD_ECHO_RESP_BODY {
    CMD_STATUS cmdStatus;
    char msg[1024];
};

