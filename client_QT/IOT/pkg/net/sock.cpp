#include "../../header/stdhead.h"
#include "./sock.h"
#include <cstdio>
#include <cstring>
#include <QThread>
#include <QCoreApplication>
#include <QEventLoop>

//发送数据放入缓冲区
int sendMsg(SOCKNODE *node,const char *buf, int len ){
    //只提供阻塞方式 阻塞到吧len的信息放到缓冲区为止
    int ret = node->connfd->write(buf , len);
    if (ret == -1)
    {
        return -1;
    }
    return ret;
}

//接收数据并放入缓冲区
//会丢数据 不建议使用
int recvMsg(SOCKNODE *node, char *buf, int len) {
    qDebug() << "//会丢数据 不建议使用";
    //只提供阻塞方式
    QByteArray data = node->connfd->readAll();
    if (data.isEmpty()) {
        // 检查异常情况
        if (node->connfd->state() == QTcpSocket::UnconnectedState) {
            qDebug() << "Connection closed by the remote host.";
        } else if (node->connfd->error() != QAbstractSocket::UnknownSocketError) {
            qDebug() << "Socket error occurred:" << node->connfd->errorString();
        } else {
            qDebug() << "No data available to read.";
        }
    } else {
        qDebug() << "Data received:" << data;
    }
    int cplen = data.size() > len ? len :data.size() ;
    std::memcpy(buf, data.data(), cplen);

    return data.length();
}
int recvMsgWithLen(SOCKNODE *node, char *buf, int len) {
    if(len == -1) {
        return -1;
    }
    if(len == 0){
        return 0;
    }
    //指定 一定要读取len长的字节 不然就阻塞
    int totalBytesRead = 0;

    while (totalBytesRead < len) {

        if(node->connfd->bytesAvailable()){
            // 读取尽可能多的数据
            int bytesRead = node->connfd->read(buf + totalBytesRead, len - totalBytesRead);

            if (bytesRead == -1) {
                return -1;
            } else if (bytesRead == 0) {
                return 0;  // 对端关闭连接
            }

            totalBytesRead += bytesRead;
        }else{
             QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);

        }

    }
    // 成功读取len字节
    return totalBytesRead;
}

int recvMsgTwo(SOCKNODE *node, char *buf, int buflen){
    int buf_readlen = 0;
    int recvlen = 0;
    recvlen = recvMsgWithLen(node, (char *)&buf_readlen , 4); // 读取4个字节的int
    if (recvlen == 0) {
        return 0;
    }
    int readlen = buf_readlen;// 小端读
    if (readlen > buflen) {
        return -1;
    }
    recvlen = recvMsgWithLen(node, buf, readlen);
    if (recvlen == 0) {
        return 0;
    }
    return recvlen;
}

int sendMsgTwo(SOCKNODE *node, const char *buf, int len){
    int sendlen = len;
    int sendret = 0;
    sendret = sendMsg(node, (char * ) & sendlen ,  4);
    if(sendret == -1){
        return -1;
    }
    sendret = sendMsg(node, buf , sendlen);
    if(sendret == -1){
        return -1;
    }
    return sendret;
}


//创建套接字
SOCKNODE * createSocket( char* name , int namelen){
    SOCKNODE *node = new SOCKNODE();
    node->connfd = new QTcpSocket;
    if(node->connfd == nullptr){
        return NULL;
    }
    memcpy(node->name , name , namelen);
    node->name[namelen] = '\0';
    return node;
}

SOCKNODE * createSocketByConnfd(char* name , int namelen , QTcpSocket * connfd){
    SOCKNODE *node = new SOCKNODE(connfd);
    node->connfd = connfd;
    if(node->connfd == nullptr){
        return NULL;
    }
    memcpy(node->name , name , namelen);
    node->name[namelen] = '\0';
    return node;
}

int FullSocketInfo(SOCKNODE *node){
    if(node->connfd->state() != QAbstractSocket::ConnectedState){
        return -1;
    }

    //详细信息
    QString ipString = node->connfd->peerAddress().toString();
    char *tip = strdup(ipString.toStdString().c_str());
    memcpy(node->ip , tip , strlen(tip));
    node->port = node->connfd->peerPort();
    return 0;
}

//连接
int ConnSocket(SOCKNODE *node, const char *ip, int port){
    // 连接服务器
    node->connfd->connectToHost(ip, port);

    // 检查是否成功连接
    if (!node->connfd->waitForConnected(3000)) {  // 等待最多 3 秒
        qDebug() << "Connection failed!";
        return -1;
    }
    return 0;
}

//关闭连接
int closeSocket(SOCKNODE *node){
    node->connfd->close();
    delete node->connfd;
    node->connfd = nullptr;
    return 0;
}



