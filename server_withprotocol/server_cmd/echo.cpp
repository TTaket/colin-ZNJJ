#include "./server_cmd.h"


int dealCmdEcho(SOCKNODE * socknode , void * data){
    struct CMD_ECHO_RESP_BODY respbody;
    struct CMD_ECHO_BODY * body = (CMD_ECHO_BODY * )data;
    if(socknode->name[0] == '\0'){
        sysPrint("no name request %s from %s", __func__, socknode->ip);
        respbody.cmdstatus = CMD_NO_LOGIN;
        return -1 ;
    }

    //没有对应dev
    if(sockmap.find(std::string(body->devname)) == sockmap.end()){
        sysPrint("no such dev %s from %s", __func__, socknode->ip);
        respbody.cmdstatus = CMD_NO_SUCH_DEV;
        memcpy(respbody.msg , "no such dev ", sizeof("no such dev "));
        sendProtoMSG(socknode,CMD_ECHO_RESP ,(void *)&respbody);
        return -1;
    }

    //test
    sysPrint("Echo ok %s from %s", __func__, socknode->ip);
    respbody.cmdstatus = CMD_OK_RESP;
    memset(respbody.msg , 0 , sizeof(respbody.msg));
    memcpy(respbody.msg , body->msg, strlen(body->msg));
    if(sendProtoMSG(socknode,CMD_ECHO_RESP ,(void *)&respbody) == -1){
        std::cout << "send echo resp failed" <<std::endl;
        return -1;
    }
    //printProtocol(CMD_ECHO_RESP , (void *)&respbody);
    return 0;
}

int dealCmdEchoResp(SOCKNODE * node , void * buf){
    return 0;
}