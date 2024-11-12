#include "../../server/server_tools/server_tools.h"
#include "../../pkg/protocol/protocol.h"
#include "../../pkg/net/sockforprotocol.h"
#include "../../pkg/net/socknode.h"

typedef struct WorkArg{
    SOCKNODE * sock;
    void * data;
}WorkArg;

// echo.cpp
void* dealCmdEcho(void * arg);