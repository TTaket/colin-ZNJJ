#include "../server_tools/server_tools.h"

//server_readAccpet.cpp
void * dealAcceptConn(void* arg);

//server_readDisconnect.cpp
void Disconnect(SOCKNODE * node);

//server_readClient.cpp
void dealClientMessage(SOCKNODE * socknode , char * buf);