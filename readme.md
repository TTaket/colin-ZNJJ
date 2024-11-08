# 智能家居 QT 以及服务器

## 介绍

科林姜南老师完成的智能家居项目

## 迭代计划

v1.

- 局域网实现简单的客户端服务端 并实现转发
- 客户端 A B 端分离 A 为嵌入式"家居" B 为 PC 命令窗口
- 实现多用户多客户端

v2.

- 协议制定
- 客户端 -> QT
- 服务端上云

v3.

- QT 登录界面
- 数据库
- 服务端增加网页

## 使用说明

#### 关于 socket 封装包的使用说明

服务端： create -> bindandlisten -> accept -> 收发信息 -> close

客户端： create -> connect -> 收发信息 -> close

收发信息：

- sendMsg/recvMsg 用户最直观的直接通讯的方式 因为实现方式是经过缓冲区 所以是连着缓冲区里面的内容一起使用

填充：

- FullSocketInfo 把端口信息和 ip 信息填充到结构体内 可以直接读出来

#### 关于 myerror 的使用方式

- ERROR_INFO_ADD 把自定义的错误信息填充到错误列表里面
- ERROR_INFO_ERRNO_ADD 把自定义的错误信息填充到错误列表里面 同时带有 errno
- ERROR_INFO_ERRNO_SOCKNODE_ADD 把自定义的错误信息填充到错误列表里面 同时带有 socknode 的名字和 errno
- sys_show_error() 按顺序打印错误链表中的错误 错误链表不会删除
- sys_error_clear() 清楚错误链表
