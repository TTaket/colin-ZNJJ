#include "./server_cmd.h"


/**************具体协议处理  */
// 登录
// 发送登录请求
int sendLogin(SOCKNODE *node, const char *name, int namelen);
// 处理登录请求
int dealLogin(SOCKNODE *node, ProtocolBody &body);

// 登出
// 发送登出请求
int sendLogout(SOCKNODE *node, const char *name, int namelen);
// 处理登出请求
int dealLogout(SOCKNODE *node, ProtocolBody &body);

// 心跳
// 发送心跳包
int sendHeart(SOCKNODE *node);
// 处理心跳包
int dealHeart(SOCKNODE *node, ProtocolBody &body);

// 消息
// 发送消息
int sendMsg(SOCKNODE *node, const char *name, int namelen, const char *msg, int msglen);
// 处理消息
int dealMsg(SOCKNODE *node, ProtocolBody &body);