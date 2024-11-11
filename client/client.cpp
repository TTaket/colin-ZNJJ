#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>


bool isRunning = true;
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
        // 心跳包
        if (strcmp(buf, "/heart") == 0) {
            printf("recv heart\n");
            continue;
        }
        printf("recv from server: %s\n", buf);
    }
    isRunning = false;
    return nullptr;
}

void* sendHeart(void* arg) {
    SOCKNODE* sock = (SOCKNODE*)arg;
    srand(time(0));
    while (true) {
        int ret = sendMsg(sock, "/heart", strlen("/heart"));
        if(ret == -1){
            break;
        }
        int randomDelay = rand() % 10 + 25; // 25-35s
        sleep(randomDelay);
    }
    return nullptr;
}

int main(){
    SOCKNODE* sock = createSocket("zhu", strlen("zhu"));
    ConnSocket(sock, SERVER_IP, SERVER_PORT);
    FullSocketInfo(sock);
    ERROR_CHECK_AND_CLOSE;

    // 接受信息函数
    pthread_t readerThread;
    pthread_create(&readerThread, nullptr, readMessages, sock);
    // 心跳
    pthread_t heartThread;
    pthread_create(&heartThread, nullptr, sendHeart, sock);
    pthread_detach(heartThread);
    // 防止写管道关闭 导致崩溃
    signal(SIGPIPE, SIG_IGN);

    char buf[100] = {};
    
    isRunning = true;
    while (isRunning) {
        memset(buf, '\0', sizeof buf);
        //缺少输入检查
        scanf("%99[^\n]", buf);
        getchar();
        int ret = sendMsg(sock, buf, strlen(buf));
        if(ret == -1 ){
            if( errno == EPIPE){
                ERROR_INFO_ERRNO_SOCKNODE_ADD("server close", sock);
            }else {
                ERROR_INFO_ERRNO_SOCKNODE_ADD("client send err? ", sock);
            }
            break;
        }
    }

    pthread_join(readerThread, nullptr);

    closeSocket(sock);
    return 0;
}
