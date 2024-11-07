#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <cstring>
#include <string>

int main(){
    SOCKNODE * node = createSocket("li",strlen("li"));
    bindListen(node , 8159);
    SOCKNODE * newnode = acceptConn(node ,"zi" , strlen("zi"));
    FullSocketInfo(node);
    FullSocketInfo(newnode);
    ERROR_CHECK_AND_CLOSE;

    // 收发数据
    char buf[100] = {};
    while(1){
        printf("-----------------\n");
        memset(buf, '\0', sizeof buf);
        int len = recvMsg(newnode, buf , sizeof(buf));
        if(len == 0){
            printf("client close\n");
            break;
        }
        printf("recv: %s", buf);
        sendMsg(newnode, buf, strlen(buf));
    }

    // 关闭
    closeSocket(newnode);
    closeSocket(node);
    return 0;
}