#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(){
    SOCKNODE* sock = createSocket("zhu",strlen("zhu"));
    ConnSocket(sock, SERVER_IP, SERVER_PORT);
    FullSocketInfo(sock);
    ERROR_CHECK_AND_CLOSE;

    // 收发数据
    char buf[100] = {};
    while(1){
        printf("-----------------\n");
        memset(buf, '\0', sizeof buf);
        fgets(buf, sizeof(buf), stdin);
        sendMsg(sock, buf, strlen(buf));
        int len = recvMsg(sock, buf);
        if(len == 0){
            printf("server close\n");
            break;
        }
        printf("recv from server :%s" , buf);
    }


    // 关闭
    closeSocket(sock);
    return 0;
}