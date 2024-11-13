#pragma once
#include "../../header/stdhead.h"

#define SEND_BUF_SIZE 1024
#define RECV_BUF_SIZE 1024
typedef struct SOCKNODE{
    QTcpSocket * connfd;

    // 详细信息
    SOCKNODE(){
        connfd = nullptr;
    }
    SOCKNODE(QTcpSocket * that){
        connfd = that;
    }
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
int ConnSocket(SOCKNODE *node, const char *ip, int port);

/**
 * @brief 关闭连接
 *
 * 该函数用于关闭指定SOCKNODE节点的连接。
 *
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @return int 返回0表示成功，返回负值表示失败。
 */
int closeSocket(SOCKNODE *node);



/***************套接字读写操作**************************/
/**
 * @brief 发送数据
 *
 * 该函数用于将数据放入指定SOCKNODE节点的发送缓冲区并执行发送操作。
 *
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向需要发送的数据缓冲区。
 * @param len 需要发送的数据长度。
 * @return int 返回字节数
 * @note 阻塞模式和非阻塞模式下均保证数据完整性
 */
int sendMsg(SOCKNODE *node,const char *buf, int len );

/**
 * @brief 接收数据
 *
 * 该函数用于刷新指定SOCKNODE节点的接收缓冲区数据并从缓冲区中取出数据。
 *
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向存储取出数据的缓冲区。
 * @param len 缓冲区的最大长度
 * @return int 返回字节数
 */
int recvMsg(SOCKNODE *node, char *buf, int len);

/**
 * @brief 接收数据
 *
 * 该函数用于刷新指定SOCKNODE节点的接收缓冲区数据并从缓冲区中取出数据。
 *
 * @param node 指向SOCKNODE结构体的指针，表示需要操作的节点。
 * @param buf 指向存储取出数据的缓冲区。
 * @param len 指定长度 如果不够一直阻塞
 * @return int 返回字节数
 */
int recvMsgWithLen(SOCKNODE *node, char *buf, int len);
int recvMsgTwo(SOCKNODE *node, char *buf, int buflen);
int sendMsgTwo(SOCKNODE *node, const char *buf, int len);

