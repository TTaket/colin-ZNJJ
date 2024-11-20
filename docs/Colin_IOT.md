# Colin_IOT

## 导航

1. 整体架构
2. 开发目标
3. 开发日志
4. 文件结构

## 整体架构

整体使用TCP  CS架构

服务器为设立在公网上的TCP服务端 处理TCP连接

分为三种客户端 分别是命令行客户端 QT客户端 stm32下的设备客户端

其中命令行和QT客户端主要执行的是用户的控制下发

stm32起到的作用是作为设备执行用户的命令

![image-20241114195918186](/Users/lijingyang/Library/Application Support/typora-user-images/image-20241114195918186.png)

## 开发目标

1. 命令行版本实现通讯的需求
2. 服务端多线程处理多人接入 用户区分的功能
3. 添加心跳等服务端的维护
4. 添加QT界面的客户端 和 stm32对应的接入方式
5. 准备扩展协议 服务端添加隔离性 用户鉴权 接入数据库 【进行中】
6. 添加网页前端界面 QT扩展为支持移动端【进行中】

## 开发过程

1. 首先实现的是简单版的Tcp cs通讯  在命令行下写出来单线程的客户端服务端通讯
2. 考虑到可扩展性和重复利用的角度 把TCP常用的函数按逻辑分别封装 形成完整对套接字的控制结构 SOCKNODE
3. 对错误处理的逻辑进行了封装 允许进行错误处理 并且同步到本地
4. 编写makefile 自动化进行编译
5. 简化socket的封装
6. 允许服务端连接多个客户端 并且根据name进行管理
7. 协议的添加 添加了协议包（新版 但是还没有）
8. 添加心跳机制 分为两部分 客户端到服务端的心跳
9. 添加服务端到客户端的心跳
10. 添加gitingore文件
11. 大量更新协议 包括协议 - struct - buf的转换函数
12. 添加QT的客户端
13. QT添加按钮 封装cmd的方法
14. 扩充sock包 支持sendMsgTwo 和 recvMsgTwo 即先发大小后发内容
15. 处理stm32 的接入 写出demo 打包

## 文件结构

![image-20241115184654684](/Users/lijingyang/Library/Application Support/typora-user-images/image-20241115184654684.png)

- bak下面是一些可执行的二进制文件 是历史版本 现在已经不维护了
- bin目录下是makefile指定的生成位置 存放每一次编译后的生成二进制文件
- client_qt 是QT版本的客户端
- client_simple 是不带有protocol的简易版本 也是现在的主要版本
- docs中填装的是文档
- header中填装的是一些标准的头文件 比如标准的头文件以及约定好的 ip port 的配置相关的信息
- pkg中是一些项目中用到的包 比如net负责网络相关 error负责错误相关 protocol负责自定协议
- server_simple同上
- server_withprotocol同上
- gitignore 是git的忽略文件 用于描述那些文件是不被git跟踪的
