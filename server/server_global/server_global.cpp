#include "./server_global.h"

SOCKNODE *serverNode;
std::map<std::string, SOCKNODE *> sockmap;
std::map<std::string, int> lastHeartTime;//记录上次心跳时间

fd_set readfds, tmpfds;
int max_sd;