#include "../base/stdhead.h"
#include "../base/protocol.h"
#include <cstdio>
#include <unistd.h>
 
int sendInfo(int connfd, char * sInfo , int sLen){
    int bytes_sent = send(connfd, sInfo, sLen, 0);
    if (bytes_sent == -1) {
        perror("send failed");
        return -1;
    }
    return 0;
}


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
    }else{
        printf("bind successful\n");
    }
    
    if (listen(socfd, 5) == -1) {
        printf("listen error\n");
        return -1;
    }else{
        printf("listen successful\n");
    }

    // 接受连接
    struct sockaddr_in addr_cli;
    socklen_t len = sizeof(addr_cli);
    int connfd = accept(socfd, (struct sockaddr*)&addr_cli, &len);
    if(connfd == -1) {
        printf("connfd error\n");
        return -1;
    }else{
        printf("connfd successful\n");
    }

    // 收发数据
    char strRecv[100] = {};
    std::string strSend ="welcome to server!";
    std::string client_ip = inet_ntoa(addr_cli.sin_addr);
    strSend.append(client_ip);
    send(connfd, strSend.c_str(), strSend.size(), 0);
    int bytesReceived = recv(connfd, strRecv, 100, 0);
    if (bytesReceived <= 0) {
        printf("recv failed or connection closed\n");
        return -1;
    }
    printf("recv: %s\n", strRecv);

    // 关闭
    close(connfd);
    close(socfd);
    return 0;
}