#include "../base/stdhead.h"
#include "../base/protocol.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){

    // 创建socket
    int socfd = socket(AF_INET, SOCK_STREAM, 0);

    // 建立连接
    struct sockaddr_in addr_ser;
    addr_ser.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_port = htons(SERVER_PORT);
    int ret = connect(socfd, (sockaddr * )&addr_ser, sizeof(addr_ser));
    if(ret == -1) {
        printf("connfd error\n");
        return -1;
    }else{
        printf("connfd successful\n");
    }

    // 获取自己的信息
    struct sockaddr_in addr_cli;
    socklen_t addr_len = sizeof(addr_ser);
    getsockname(socfd, (struct sockaddr *)&addr_cli, &addr_len);

    // 发送数据
    std::string strSend ="Hello I am client!";
    std::string client_ip = inet_ntoa(addr_cli.sin_addr);
    strSend.append(client_ip);
    char strRecv[100] ={};
    int bytesReceived = recv(socfd, strRecv, 100, 0);
    if(bytesReceived <= 0) {
        printf("recv failed or connection closed\n");
        return -1;
    }
    printf("recv: %s\n", strRecv);
    send(socfd, strSend.c_str(), strSend.size(), 0);

    // 关闭
    close(socfd);
    return 0;
}