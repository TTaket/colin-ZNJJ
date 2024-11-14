#ifndef CLIENT_SIMPLE_H
#define CLIENT_SIMPLE_H
#include "../pkg/net/sock.h"
#include "../header/stdhead.h"
#include "../header/config.h"
#include "../pkg/net/sock.h"
#include <QThread>
#include <QTimer>
#include <QObject>
#include <QDebug>


class SendHeartThread : public QThread {
    Q_OBJECT

public:
    explicit SendHeartThread(QObject* parent = nullptr)
        : QThread(parent), timer(this) {
        // 设置定时器每5秒发出信号
        connect(&timer, &QTimer::timeout, this, &SendHeartThread::onTimeout);
        timer.start(30000);  // 每30秒 触发一次timeout信号
    }

protected:
    void run() override {
        // 这里的 run 方法不再负责发送心跳，而是空的或进行其他后台处理
        exec();  // 进入事件循环，等待定时器的信号
    }

signals:
    void sig_sendHeartSignal();  // 定义一个信号，通知父线程发送心跳

private:
    QTimer timer;  // 定时器

    void onTimeout() {
        // 定时器超时时，发出信号
        emit sig_sendHeartSignal();
    }
};

class CheckHeartThread : public QThread {
    Q_OBJECT

public:
    explicit CheckHeartThread(QObject* parent = nullptr)
        : QThread(parent), timer(this) {
        // 设置定时器每5秒发出信号
        connect(&timer, &QTimer::timeout, this, &CheckHeartThread::onTimeout);
        timer.start(500000);  // 每500000ms（500秒）触发一次timeout信号
    }

protected:
    void run() override {
        // 这里的 run 方法不再负责发送心跳，而是空的或进行其他后台处理
        exec();  // 进入事件循环，等待定时器的信号
    }

signals:
    void sig_checkHeartSignal();  // 定义一个信号，通知父线程checkHeart

private:
    QTimer timer;  // 定时器

    void onTimeout() {
        // 定时器超时时，发出信号
        emit sig_checkHeartSignal();
    }
};

class CheckRunningThread : public QThread {
    Q_OBJECT

public:
    explicit CheckRunningThread(QObject* parent = nullptr)
        : QThread(parent), timer(this) {
        // 设置定时器每5秒发出信号
        connect(&timer, &QTimer::timeout, this, &CheckRunningThread::onTimeout);
        timer.start(5000);  // 每5000ms（5秒）触发一次timeout信号
    }

protected:
    void run() override {
        // 这里的 run 方法不再负责发送心跳，而是空的或进行其他后台处理
        exec();  // 进入事件循环，等待定时器的信号
    }

signals:
    void sig_checkRunningSignal();  // 定义一个信号，通知父线程checkHeart

private:
    QTimer timer;  // 定时器

    void onTimeout() {
        // 定时器超时时，发出信号
        emit sig_checkRunningSignal();
    }
};

class CheckReadThread : public QThread {
    Q_OBJECT

public:
    explicit CheckReadThread(SOCKNODE * sock, QObject* parent = nullptr)
        : QThread(parent), m_sock(sock) {}

signals:
    // 定义信号，向父线程通知读取到的数据
    void sig_checkReadSignal();

protected:
    void run() override {
        while (true) {
            if (m_sock->connfd->bytesAvailable() > 0) {
                emit sig_checkReadSignal();  // 发送信号通知父线程
            }
            QThread::msleep(500);
        }
    }

private:
    SOCKNODE * m_sock;
};




class Client_simple : public QObject {
    Q_OBJECT

public:
    Client_simple(){
        memset(readbuf , 0 , sizeof readbuf);
        memset(sendbuf , 0 , sizeof sendbuf);
        m_isRunning = false;
        lastHeartTime = 0;
        lastHeartZeroTime = 0;
        sock = createSocket("", strlen(""));
        ConnSocket(sock, SERVER_IP, SERVER_PORT);
        FullSocketInfo(sock);

        //线程们
        if(sock->connfd->isOpen()){
            m_readThread = new CheckReadThread(sock);
            connect(m_readThread, &CheckReadThread::sig_checkReadSignal,
                    this, &Client_simple::slots_checkReadSignal);

            m_checkRunningthread = new CheckRunningThread();
            connect(m_checkRunningthread, &CheckRunningThread::sig_checkRunningSignal ,
                    this, &Client_simple::slots_checkRunningSignal);

            m_checkHeartThread = new CheckHeartThread();
            connect(m_checkHeartThread, &CheckHeartThread::sig_checkHeartSignal ,
                    this, &Client_simple::slots_checkHeartSignal);

            m_sendHeartThread = new SendHeartThread();
            connect(m_sendHeartThread, &SendHeartThread::sig_sendHeartSignal ,
                    this, &Client_simple::slots_sendHeartSignal);

        }else{
            m_readThread = nullptr;
            m_checkRunningthread = nullptr;
            m_checkHeartThread = nullptr;
            m_sendHeartThread = nullptr;
        }

    }
public:
    int clientSimpleStart();
    int clientSimpleClose();
    int sendMessages(const char * s , int len);
    bool IsRunning();



signals:
    void sig_recvInfoToUpdataUi(char * s , int len );

//线程函数
private:
    void checkHeart();
    void checkRunning();
    void sendHeart();
    int readMessages();

private slots:
    void slots_sendHeartSignal();
    void slots_checkHeartSignal();
    void slots_checkRunningSignal();
    void slots_checkReadSignal();

private:
    char readbuf[1005];
    char sendbuf[1005];
    bool m_isRunning;
    int lastHeartTime;
    int lastHeartZeroTime;
    SOCKNODE* sock;

private:
    CheckReadThread * m_readThread;
    CheckRunningThread * m_checkRunningthread;
    CheckHeartThread* m_checkHeartThread ;
    SendHeartThread* m_sendHeartThread;
};




#endif // CLIENT_SIMPLE_H

