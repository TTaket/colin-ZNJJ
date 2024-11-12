#pragma once
#include "../../pkg/net/socknode.h"


extern SOCKNODE *serverNode;
extern std::map<std::string, SOCKNODE *> sockmap;
extern std::map<int , SOCKNODE * > sockmapUnlogin;

extern std::map<int, int> lastHeartTimeUnlogin;//记录上次心跳时间
extern std::map<std::string, int> lastHeartTime;//记录上次心跳时间

extern std::map<std::string , std::string> usermap;// 用户名和密码
extern fd_set readfds, tmpfds;
extern int max_sd;
extern bool isRunning;

