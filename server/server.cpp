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
    sendMsg(newnode, std::string("welcome to server!" + std::string(newnode->ip)).c_str(), strlen("welcome to server!") + std::string(newnode->ip).length() );
    recvMsg(newnode, strRecv);
    printf("%s\n" , strRecv);
    
    // 关闭
    closeSocket(newnode);
    closeSocket(node);
    return 0;
}