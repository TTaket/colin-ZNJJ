#pragma once
#include "../../pkg/net/socknode.h"


extern SOCKNODE *serverNode;
extern std::map<std::string, SOCKNODE *> sockmap;
extern std::map<std::string, int> lastHeartTime;//记录上次心跳时间

extern fd_set readfds, tmpfds;
extern int max_sd;

