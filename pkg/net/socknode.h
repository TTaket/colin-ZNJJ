#pragma once
#include "../../base/stdhead.h"

#define SEND_BUF_SIZE 1024
#define RECV_BUF_SIZE 1024
typedef struct SOCKNODE{
    int connfd;
    struct sockaddr_in addr;
    socklen_t addr_len;

    //环形队列 这里2倍的长度是可以避免数据拷贝 （stringview）但是还没有使用
    char sendBuf[2 * SEND_BUF_SIZE];
    char recvBuf[2 * RECV_BUF_SIZE];
    int sendHead, sendTail;
    int recvHead, recvTail;
    SOCKNODE(){
        connfd = -1;
        addr_len = -1;//未初始化
        sendHead = sendTail = 0;
        recvHead = recvTail = 0;
    }

    // 详细信息
    char name[100];
    char ip[100];
    int port;
}SOCKNODE;

/***************套接字基础操作**************************/
/**
 * @brief 创建套接字
 * 
 * 该函数用于创建一个新的SOCKNODE节点。
 * 
 * @return SOCKNODE* 返回指向新创建的SOCKNODE节点的指针。
 */
SOCKNODE * createSocket(char* name , int namelen);
/**
 * @brief 创建套接字
 * 
 * 该函数用于创建一个新的SOCKNODE节点，并指定连接文件描述符。
 * 
 * @param connfd 指定的连接文件描述符。
 * @return SOCKNODE* 返回指向新创建的SOCKNODE节点的指针。
 */
SOCKNODE * createSocketByConnfd(char* name , int namelen , int connfd);

//填充套接字的信息
int FullSocketInfo(SOCKNODE *node);

/**
 * @brief 创建一个连接到指定IP和端口的SOCKNODE节点。
 * 
 * 该函数用于创建一个连接到指定IP和端口的SOCKNODE节点。
 * 
 * @param node 指向SOCKNODE结构体的指针，用于存储连接信息。
 * @param ip 目标服务器的IP地址。
 * @param port 目标服务器的端口号。
 * @return int 返回0表示成功，返回负值表示失败。
 * 
 * @note 使用此函数可以建立与指定服务器的连接，适用于需要网络通信的场景。
 */
int createConn(SOCKNODE *node, const char *ip, int port);

/**
 * @brief 绑定监听
 * 
 * 该函数用于将指定SOCKNODE节点绑定到指定端口并开始监听。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param port 需要绑定的端口号。
 * @return int 返回0表示成功，返回负值表示失败。
 */
int bindListen(SOCKNODE *node, int port);

/**
 * @brief 接受连接
 * 
 * 该函数用于接受指定SOCKNODE节点的连接请求。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @return SOCKNODE* 返回指向新接受的连接的SOCKNODE节点的指针。
 */
SOCKNODE * acceptConn(SOCKNODE *node);

/**
 * @brief 关闭连接
 * 
 * 该函数用于关闭指定SOCKNODE节点的连接。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @return int 返回0表示成功，返回负值表示失败。
 */
int closeConn(SOCKNODE *node);



/***************套接字读写操作**************************/
/**
 * @brief 获取指定SOCKNODE的发送缓冲区大小。
 *
 * 该函数用于获取指定SOCKNODE对象的发送缓冲区大小。
 *
 * @param node 指向SOCKNODE对象的指针。
 * @return 返回发送缓冲区的大小（以字节为单位）。
 */
int getSendBufSize(SOCKNODE *node);

/**
 * @brief 获取接收缓冲区的大小。
 *
 * 该函数用于获取指定SOCKNODE节点的接收缓冲区大小。
 *
 * @param node 指向SOCKNODE结构体的指针。
 * @return 返回接收缓冲区的大小（以字节为单位）。
 */
int getRecvBufSize(SOCKNODE *node);

/**
 * @brief 获取发送缓冲区剩余空间
 * 
 * 该函数用于获取指定SOCKNODE节点的发送缓冲区中剩余的空间大小。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要查询的节点。
 * @return int 返回发送缓冲区的剩余空间大小，单位为字节。
 */
int getSendBufRemain(SOCKNODE *node);

/**
 * @brief 获取接收缓冲区剩余空间
 * 
 * 该函数用于获取指定SOCKNODE节点的接收缓冲区中剩余的空间大小。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要查询的节点。
 * @return int 返回接收缓冲区的剩余空间大小，单位为字节。
 */
int getRecvBufRemain(SOCKNODE *node);

/**
 * @brief 将数据放入发送缓冲区
 * 
 * @param node 指向SOCKNODE结构体的指针，表示当前的连接节点
 * @param buf 指向要发送的数据缓冲区的指针
 * @param len 要发送的数据长度
 * @return int 实际放入的长度，失败返回-1（缓冲区满）
 * 
 * @note 该函数将数据放入发送缓冲区，如果缓冲区剩余空间不足以容纳数据，则返回-1。
 *       如果数据可以放入缓冲区，则将数据复制到缓冲区相应位置，并更新发送缓冲区的尾部指针。
 */
int putSendBuf(SOCKNODE *node, char *buf, int len);

/**
 * @brief 将接收到的数据放入接收缓冲区
 *
 * 该函数用于将接收到的数据放入指定的SOCKNODE节点的接收缓冲区中。
 * 如果缓冲区剩余空间不足以容纳新数据，则返回错误。
 *
 * @param node 指向SOCKNODE结构体的指针，表示目标节点
 * @param buf 指向接收到的数据缓冲区的指针
 * @param len 接收到的数据长度
 * @return int 实际放入的长度，失败返回-1（缓冲区满）
 */
int putRecvBuf(SOCKNODE *node, char *buf, int len);

/**
 * @brief 从发送缓冲区取出数据
 * 
 * 该函数用于从指定SOCKNODE节点的发送缓冲区中取出数据。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向存储取出数据的缓冲区。
 * @param len 需要取出的数据长度。-1表示取出所有数据。
 * @return int 返回实际取出发送缓冲区的数据长度，单位为字节。
 */
int getSendBuf(SOCKNODE *node, char *buf, int len = -1);

/**
 * @brief 从接收缓冲区取出数据
 * 
 * 该函数用于从指定SOCKNODE节点的接收缓冲区中取出数据。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向存储取出数据的缓冲区。
 * @param len 需要取出的数据长度。-1表示取出所有数据。
 * @return int 返回实际取出接收缓冲区的数据长度，单位为字节。
 */
int getRecvBuf(SOCKNODE *node, char *buf, int len = -1);

/**
 * @brief 执行发送
 * 
 * 该函数用于执行指定SOCKNODE节点的发送操作。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param slen 需要发送的数据长度，默认为-1表示发送缓冲区中的所有数据。
 * @return int 返回实际发送的数据长度，单位为字节。
 */
int doSend(SOCKNODE *node , int slen = -1);

/**
 * @brief 执行接收
 * 
 * 该函数用于执行指定SOCKNODE节点的接收操作。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param rlen 需要接收的数据长度，默认为-1表示接收缓冲区中的所有数据。
 * @return int 返回实际接收的数据长度，单位为字节。
 */
int doRecv(SOCKNODE *node , int rlen = -1);

/**
 * @brief 发送数据 放入缓冲区并发送
 * 
 * 该函数用于将数据放入指定SOCKNODE节点的发送缓冲区并执行发送操作。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向需要发送的数据缓冲区。
 * @param len 需要发送的数据长度。
 * @return int 返回实际发送的数据长度，单位为字节。
 */
int sendMsg(SOCKNODE *node, char *buf, int len);

/**
 * @brief 接收数据 刷新缓冲区数据 并且从缓冲区取出
 * 
 * 该函数用于刷新指定SOCKNODE节点的接收缓冲区数据并从缓冲区中取出数据。
 * 
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向存储取出数据的缓冲区。
 * @param len 需要取出的数据长度。
 * @return int 返回实际取出接收缓冲区的数据长度，单位为字节。
 */
int recvMsg(SOCKNODE *node, char *buf, int len);