#include "../../pkg/net/socknode.h"

SOCKNODE *serverNode;
std::map<std::string, SOCKNODE *> sockmap;
std::map<int , SOCKNODE * > sockmapUnlogin;
std::map<std::string, int> lastHeartTime;//记录上次心跳时间
std::map<int, int> lastHeartTimeUnlogin;//记录上次心跳时间
std::map<std::string , std::string> usermap;// 用户名和密码

fd_set readfds, tmpfds;
int max_sd;
bool isRunning;