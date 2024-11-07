#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(){
    SOCKNODE* sock = createSocket("zhu",strlen("zhu"));
    ConnSocket(sock, SERVER_IP, SERVER_PORT);
    FullSocketInfo(sock);


    // 发送数据
    char strRecv[100] ={};
    std::string strSend =std::string("Hello I am client!") + sock->ip;
    
    recvMsg(sock, strRecv);
    printf("recv: %s\n", strRecv);
    sendMsg(sock , strSend.c_str(), strSend.size());

    // 关闭
    closeSocket(sock);
    return 0;
}