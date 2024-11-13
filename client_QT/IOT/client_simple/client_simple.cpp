#include "./client_simple.h"
#include <QThread>
#include <QMutex>

int Client_simple::readMessages() {
    memset(readbuf, '\0', sizeof readbuf);
    int len = 0;
    len = recvMsgTwo(sock , readbuf , sizeof readbuf);
    if(len == 0 ){
        return 0;
    }
    if(len == -1 ){
        return -1;
    }
    printf("recv from server: %s\n", readbuf);
    emit sig_recvInfoToUpdataUi(readbuf , len);
    return len;
}

void Client_simple::sendHeart() {
    int ret = sendMsgTwo(sock, "/heart", strlen("/heart"));
    if(ret == -1){
        return;
    }
}

void Client_simple::checkHeart() {
    if (lastHeartTime == 0) {
        lastHeartZeroTime++;
        if (lastHeartZeroTime > 3) {
            printf("server heart check failed\n");
            m_isRunning = false;
            return;
        }
    }
    if (time(0) - lastHeartTime > 90 && lastHeartTime != 0) {
        printf("server heart check failed\n");
        m_isRunning = false;
        return;
    }
}

void Client_simple::checkRunning() {

    if(IsRunning() == false){
        clientSimpleClose();//关闭
        return;
    }

}

bool Client_simple::IsRunning(){
    return m_isRunning;
}


int Client_simple::sendMessages(const char * s , int len ){
    int ret = sendMsgTwo(sock, s, len);
    if(ret == -1 ){
        if( errno == EPIPE){
            return -1;
        }else {
            return -1;
        }
    }
    if (strcmp("/exit", s) == 0) {
        m_isRunning = false;
    }
    return ret;
}

int Client_simple::clientSimpleClose(){
    //回收所有子线程
    if (m_readThread) {
        m_readThread->quit();
        m_readThread->wait();
        delete m_readThread;
        m_readThread = nullptr;
    }

    if (m_checkRunningthread) {
        m_checkRunningthread->quit();
        m_checkRunningthread->wait();
        delete m_checkRunningthread;
        m_checkRunningthread = nullptr;
    }

    if (m_checkHeartThread) {
        m_checkHeartThread->quit();
        m_checkHeartThread->wait();
        delete m_checkHeartThread;
        m_checkHeartThread = nullptr;
    }

    if (m_sendHeartThread) {
        m_sendHeartThread->quit();
        m_sendHeartThread->wait();
        delete m_sendHeartThread;
        m_sendHeartThread = nullptr;
    }

    closeSocket(sock);
    return 0;
}

int Client_simple::clientSimpleStart(){
    // 防止写管道关闭 导致崩溃
    signal(SIGPIPE, SIG_IGN);

    if(! sock->connfd->isOpen()){
        return -1;
    }

    m_isRunning = true;

    // 发送心跳
    m_sendHeartThread->start();

    // 心跳检查
    m_checkHeartThread->start();

    //系统存活检查
    m_checkRunningthread->start();

    //读线程
    m_readThread->start();

    return 0;

}

void Client_simple::slots_sendHeartSignal(){
    sendHeart();
}

void Client_simple::slots_checkHeartSignal(){
    checkHeart();
}

void Client_simple::slots_checkRunningSignal(){
    checkRunning();
}

void Client_simple::slots_checkReadSignal(){
    readMessages();
}

