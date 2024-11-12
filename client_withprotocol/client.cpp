#include "../header/stdhead.h"
#include "../header/config.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include "../pkg/net/sockforprotocol.h"
#include "../pkg/protocol/protocolhelper.h"
#include "../pkg/protocol/protocoltransform.h"
#include "../pkg/protocol/protocol.h"
#include <cstring>
#include <unistd.h>

bool isRunning = true;
int lastHeartTime = 0;
int lastHeartZeroTime = 0;
void* readMessages(void* arg) {
    SOCKNODE* sock = (SOCKNODE*)arg;
    char buf[100] = {};
    while (isRunning) {
        CMD cmd;
        memset(buf,0 , sizeof buf);
        readProtoMSG(sock, cmd, buf);
        if (cmd == CMD_ECHO_RESP) {
            CMD_ECHO_RESP_BODY* body = (CMD_ECHO_RESP_BODY*)buf;
            if(body->cmdstatus == CMD_OK_RESP){
                printf("recv from server: %s\n", body->msg);
            }else{
                printf("recv from server: echo err %d\n", body->cmdstatus);
            }
        } else if (cmd == CMD_USER_LOGIN_RESP) {
            CMD_USER_LOGIN_RESP_BODY* body = (CMD_USER_LOGIN_RESP_BODY*)buf;
            if (body->cmdstatus == CMD_OK_RESP) {
                printf("login success\n");
            } else {
                printf("login failed\n");
                break;
            }
        } else {
            printf("recv from server: %s\n", buf);
        }
    }
    isRunning = false;
    return nullptr;
}

void* sendHeart(void* arg) {
    SOCKNODE* sock = (SOCKNODE*)arg;
    srand(time(0));
    while (isRunning) {
        int ret = sendMsg(sock, "/heart", strlen("/heart"));
        if(ret == -1){
            break;
        }
        int randomDelay = rand() % 10 + 25; // 25-35s
        sleep(randomDelay);
    }
    return nullptr;
}

void* checkHeart(void* arg) {
    SOCKNODE* sock = (SOCKNODE*)arg;
    srand(time(0));
    while (isRunning) {
        if (lastHeartTime == 0) {
            lastHeartZeroTime++;
            if (lastHeartZeroTime > 3) {
                printf("server heart check failed\n");
                break;
            }
        }
        if (time(0) - lastHeartTime > 90 && lastHeartTime != 0) {
            printf("server heart check failed\n");
            break;
        }
        int randomDelay = rand() % 10 + 120; //120-130s
        sleep(randomDelay);
    }
    isRunning = false;
    return nullptr;
}

int main(){
    //启动错误日志
    sys_err_init();

    SOCKNODE* sock = createSocket("", strlen(""));
    ConnSocket(sock, SERVER_IP, SERVER_PORT);
    FullSocketInfo(sock);
    ERROR_CHECK_AND_CLOSE;

    // 接受信息函数
    pthread_t readerThread;
    pthread_create(&readerThread, nullptr, readMessages, sock);
    pthread_detach(readerThread);
    // 心跳
    // pthread_t heartThread;
    // pthread_create(&heartThread, nullptr, sendHeart, sock);
    // pthread_detach(heartThread);
    // server心跳检查
    pthread_t checkHeartThread;
    pthread_create(&checkHeartThread, nullptr, checkHeart, sock);
    pthread_detach(checkHeartThread);
    // 防止写管道关闭 导致崩溃
    signal(SIGPIPE, SIG_IGN);

    char buf[100] = {};
    
    isRunning = true;

    sleep(2);
    CMD_USER_LOGIN_BODY body;
    memcpy(body.name, "litest", strlen("litest"));
    memcpy(body.pwd, "123456", strlen("123456"));
    sendProtoMSG(sock, CMD_USER_LOGIN, (void*)&body);
    sleep(2);
    
    while (isRunning) {
        memset(buf, '\0', sizeof buf);
        //缺少输入检查
        scanf("%99[^\n]", buf);
        getchar();
        CMD_ECHO_BODY ebody;
        memset(&ebody, 0, sizeof(ebody));
        memcpy(ebody.devname, "litest", strlen("litest"));
        memcpy(ebody.msg, buf, strlen(buf));
        int ret = sendProtoMSG(sock, CMD_ECHO, (void*)&ebody);
        //int ret = sendMsg(sock, buf, strlen(buf));
        if(ret == -1 ){
            if( errno == EPIPE){
                ERROR_INFO_ERRNO_SOCKNODE_ADD("server close", sock);
            }else {
                ERROR_INFO_ERRNO_SOCKNODE_ADD("client send err? ", sock);
            }
            break;
        }
        if (strcmp("/exit", buf) == 0) {
            isRunning = false;
            break;
        }
    }

    closeSocket(sock);
    return 0;
}
