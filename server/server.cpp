#include "net/base/stdhead.h"
#include "net/base/protocol.h"
#include <unistd.h>
 
int main(){

    // 创建socket
    int socfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 绑定 & 监听
    struct sockaddr_in addr_ser;
    addr_ser.sin_addr.s_addr = INADDR_ANY;
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_port = htons(SERVER_PORT);
    int ret = bind(socfd , (struct sockaddr*)&addr_ser , sizeof(addr_ser));
    if(ret == -1){
        printf("bind error\n");
        return -1;
    }
    listen(socfd, 5);

    // 接受连接
    struct sockaddr_in addr_cli;
    socklen_t len = sizeof(addr_cli);
    int connfd = accept(socfd, (struct sockaddr*)&addr_cli, &len);

    // 发送数据
    std::string strSend ="welcome to server!";
    char strRecv[100] = {};
    strSend.append(std::to_string(addr_cli.sin_addr.s_addr));
    send(connfd, strSend.c_str(), strSend.size(), 0);
    recv(connfd, strRecv, 100, 0);
    printf("recv: %s\n", strRecv);

    // 回收资源
    close(connfd);
    close(socfd);

    return 0;
}