#include "./server_cmd.h"
#include "../../pkg/error/myerror.h"
#include "../../pkg/protocol/protocol.h"

int dealCmdUserLogin(SOCKNODE *node, void * buf){
    struct CMD_USER_LOGIN_BODY * data = (CMD_USER_LOGIN_BODY *)buf;
    struct CMD_USER_LOGIN_RESP_BODY resp;
    if(node->name[0] != '\0'){
        resp.cmdstatus = CMD_HAS_LOGIN;
        sendProtoMSG(node, CMD_USER_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    if(usermap.find(std::string(data->name)) == usermap.end()){
        resp.cmdstatus = CMD_NO_SUCH_USER;
        sendProtoMSG(node, CMD_USER_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    if(usermap[std::string(data->name)] != std::string(data->pwd)){
        resp.cmdstatus = CMD_ERR_PWD;
        sendProtoMSG(node, CMD_USER_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    memcpy(node->name, data->name, strlen(data->name));
    resp.cmdstatus = CMD_OK_RESP;
    sendProtoMSG(node, CMD_USER_LOGIN_RESP, (void *)&resp);

    //处理登录信息
    sockmap[node->name] = node;
    lastHeartTime[node->name] = time(0);
    if(sockmapUnlogin.find(node->connfd) != sockmapUnlogin.end()){
        sockmapUnlogin.erase(sockmapUnlogin.find(node->connfd));
    }
    if(lastHeartTimeUnlogin.find(node->connfd) != lastHeartTimeUnlogin.end()){
        lastHeartTimeUnlogin.erase(lastHeartTimeUnlogin.find(node->connfd));
    }
    return 0;
}
int dealCmdDevLogin(SOCKNODE *node, void * buf){
    struct CMD_DEV_LOGIN_BODY * data = (CMD_DEV_LOGIN_BODY *)buf;
    struct CMD_DEV_LOGIN_RESP_BODY resp;
    if(node->name[0] != '\0'){
        resp.cmdstatus = CMD_HAS_LOGIN;
        sendProtoMSG(node, CMD_DEV_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    if(usermap.find(std::string(data->name)) == usermap.end()){
        resp.cmdstatus = CMD_NO_SUCH_DEV;
        sendProtoMSG(node, CMD_DEV_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    if(usermap[std::string(data->name)] != std::string(data->pwd)){
        resp.cmdstatus = CMD_ERR_PWD;
        sendProtoMSG(node, CMD_DEV_LOGIN_RESP, (void *)&resp);
        return -1;
    }
    memcpy(node->name, data->name, strlen(data->name));
    resp.cmdstatus = CMD_OK_RESP;
    sendProtoMSG(node, CMD_DEV_LOGIN_RESP, (void *)&resp);

    //处理登录信息
    sockmap[node->name] = node;
    lastHeartTime[node->name] = time(0);
    if(sockmapUnlogin.find(node->connfd) != sockmapUnlogin.end()){
        sockmapUnlogin.erase(sockmapUnlogin.find(node->connfd));
    }
    if(lastHeartTimeUnlogin.find(node->connfd) != lastHeartTimeUnlogin.end()){
        lastHeartTimeUnlogin.erase(lastHeartTimeUnlogin.find(node->connfd));
    }
    return 0;
}

int dealCmdUserLoginResp(SOCKNODE * node , void * buf){
    ERROR_INFO_ERRNO_SOCKNODE_ADD("server 不可能收到这样的请求", node);
    return 0;
}
int dealCmdDevLoginResp(SOCKNODE * node , void * buf){
    ERROR_INFO_ERRNO_SOCKNODE_ADD("server 不可能收到这样的请求", node);
    return 0;
}