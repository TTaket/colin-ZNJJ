#include "../../server/server_tools/server_tools.h"
#include "../../pkg/protocol/protocol.h"
#include "../../pkg/net/sockforprotocol.h"
#include "../../pkg/net/socknode.h"

typedef struct WorkArg{
    SOCKNODE * sock;
    void * data;
}WorkArg;

// echo.cpp
int dealCmdEcho(SOCKNODE * socknode , void * data);
int dealCmdEchoResp(SOCKNODE * node , void * buf);

// login.cpp
int dealCmdUserLogin(SOCKNODE *node, void * data);
int dealCmdUserLoginResp(SOCKNODE * node , void * buf);
int dealCmdDevLogin(SOCKNODE * node , void * buf);
int dealCmdDevLoginResp(SOCKNODE * node , void * buf);

// logout.cpp
int dealCmdUserLogout(SOCKNODE * node , void * buf);
int dealCmdUserLogoutResp(SOCKNODE * node , void * buf);
int dealCmdDevLogout(SOCKNODE * node , void * buf);
int dealCmdDevLogoutResp(SOCKNODE * node , void * buf);

// register.cpp
int dealCmdUserRegister(SOCKNODE *node, void * data);
int dealCmdUserRegisterResp(SOCKNODE * node , void * buf);

// heart.cpp
int dealCmdHeart(SOCKNODE * node , void * buf);
int dealCmdHeartResp(SOCKNODE * node , void * buf);

//msg.cpp
int dealCmdMsg(SOCKNODE * node , void * buf);
int dealCmdMsgResp(SOCKNODE * node , void * buf);

//notice.cpp
int dealCmdNotice(SOCKNODE * node , void * buf);
int dealCmdNoticeResp(SOCKNODE * node , void * buf);

//user_dev.cpp
int dealCmdUserAddDev(SOCKNODE * node , void * buf);
int dealCmdUserAddDevResp(SOCKNODE * node , void * buf);
int dealCmdUserDelDev(SOCKNODE * node , void * buf);
int dealCmdUserDelDevResp(SOCKNODE * node , void * buf);
int dealCmdGetList(SOCKNODE * node , void * buf);
int dealCmdGetListResp(SOCKNODE * node , void * buf);
int dealCmdGetStatus(SOCKNODE * node , void * buf);
int dealCmdGetStatusResp(SOCKNODE * node , void * buf);