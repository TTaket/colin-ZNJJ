#include "net/base/stdhead.h"
#include "net/base/protocol.h"
#include <sys/socket.h>
#include <unistd.h>

int main(){

    // 创建socket
    int socfd = socket(AF_INET, SOCK_STREAM, 0);
    listen(socfd, 5);

    // 建立连接
    struct sockaddr_in addr_ser;
    addr_ser.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_port = htons(12345);
    int connfd = connect(socfd, (sockaddr * )&addr_ser, sizeof(addr_ser));
    
    // 获取自己的信息
    struct sockaddr_in addr_cli;
    socklen_t addr_len = sizeof(addr_ser);
    getsockname(socfd, (struct sockaddr *)&addr_cli, &addr_len);

    // 发送数据
    std::string strSend ="Hello I am client!";
    char strRecv[100];
    recv(connfd, strRecv, 100, 0);
    printf("recv: %s\n", strRecv);

    strSend.append(std::to_string(addr_cli.sin_addr.s_addr));
    send(connfd, strSend.c_str(), strSend.size(), 0);

    close(connfd);
    close(socfd);

    return 0;
}