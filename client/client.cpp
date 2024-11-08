#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

void* readMessages(void* arg) {
    SOCKNODE* sock = (SOCKNODE*)arg;
    char buf[100] = {};
    while (true) {
        memset(buf, '\0', sizeof buf);
        int len = recvMsg(sock, buf, sizeof(buf));
        if (len == 0) {
            printf("server close\n");
            break;
        }
        printf("recv from server: %s\n", buf);
    }
    return nullptr;
}

int main(){
    SOCKNODE* sock = createSocket("zhu", strlen("zhu"));
    ConnSocket(sock, SERVER_IP, SERVER_PORT);
    FullSocketInfo(sock);
    ERROR_CHECK_AND_CLOSE;

    pthread_t readerThread;
    pthread_create(&readerThread, nullptr, readMessages, sock);

    char buf[100] = {};
    
    while (true) {
        memset(buf, '\0', sizeof buf);
        //缺少输入检查
        scanf("%99[^\n]", buf);
        getchar();
        sendMsg(sock, buf, strlen(buf));
    }

    pthread_join(readerThread, nullptr);

    closeSocket(sock);
    return 0;
}
