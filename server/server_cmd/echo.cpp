#include "./server_cmd.h"
#include "../../pkg/net/socknode.h"
#include "../../pkg/protocol/protocol.h"

void* dealCmdEcho(void * arg){
    WorkArg * workarg = (WorkArg *) arg;
    SOCKNODE * sock = workarg->sock;

    struct CMD_ECHO_RESP_BODY respbody;
    struct CMD_ECHO_BODY * body = (CMD_ECHO_BODY * )workarg->data;

    //没有对应dev
    if(sockmap.find(std::string(body->devname)) == sockmap.end()){
        respbody.cmdStatus = CMD_ERROR_RESP;
        memcpy(respbody.msg , "no such dev ", sizeof("no such dev "));
        sendProtoMSG(sock,CMD_ECHO_RESP ,(void *)&respbody);
    }

    //
    // SOCKNODE * tarSock = sockmap[std::string(body->devname)];
    // sendProtoMSG(tarSock , CMD_ECHO , (void *)&body);

    //test
    respbody.cmdStatus = CMD_OK_RESP;
    memcpy(respbody.msg , body->msg, strlen(body->msg));
    sendProtoMSG(sock,CMD_ECHO_RESP ,(void *)&respbody);
    return nullptr;
}
