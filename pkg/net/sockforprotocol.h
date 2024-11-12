#pragma once
#include "./socknode.h"
#include "../error/myerror.h"
#include "../protocol/protocolhelper.h"
#include "../protocol/protocol.h"
#include "../protocol/protocoltransform.h"

// 读出协议头
int readHeader(SOCKNODE *node, ProtocolHeader &header);

// 读出协议体
int readBody(SOCKNODE *node, const ProtocolHeader &header, ProtocolBody &body);

// 读出一帧消息
int readProtoMSG(SOCKNODE *node, CMD &cmd , void* data);

// 发送协议头
int sendHeader(SOCKNODE *node, const ProtocolHeader & header);

// 发送协议体
int sendBody(SOCKNODE *node, const ProtocolHeader & header ,  const ProtocolBody &body);

// 发送一帧消息
int sendProtoMSG(SOCKNODE *node, CMD cmd , void* data);
