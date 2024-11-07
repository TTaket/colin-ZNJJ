#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <string>

int main(){
    SOCKNODE * node = createSocket("li",strlen("li"));
    bindListen(node , 8159);
    SOCKNODE * newnode = acceptConn(node ,"zi" , strlen("zi"));
    FullSocketInfo(node);
    FullSocketInfo(newnode);

    // 收发数据
    char strRecv[100] = {};
    char strRecv2[100] = {};
    putSendBuf(newnode, "welcome to server!", strlen("welcome to server!"));
    putSendBuf(newnode, newnode->ip, strlen(newnode->ip));
    putSendBuf(newnode, std::to_string(newnode->port).c_str(), std::to_string(newnode->port).size());
    doSend(newnode);
    
    recvMsg(newnode, strRecv);
    printf("%s\n" , strRecv);
    recvMsg(newnode, strRecv2);
    printf("%s\n" , strRecv2);

    ERROR_INFO_ERRNO_SOCKNODE_ADD("nihao" , node);
    ERROR_INFO_ERRNO_SOCKNODE_ADD("nihao" , newnode);
    sys_show_error();
    // 关闭
    closeSocket(newnode);
    closeSocket(node);
    return 0;
}