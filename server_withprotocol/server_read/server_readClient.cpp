#include "./server_read.h"
#include "../../header/stdhead.h"
#include "../../pkg/protocol/protocol.h"
#include "../../pkg/protocol/protocolhelper.h"
#include "../../pkg/protocol/protocoltransform.h"
#include "../../pkg/net/sockforprotocol.h"
#include "../server_cmd/server_cmd.h"
void dealClientMessage(SOCKNODE * socknode , char * buf){
    // std::string sockname = socknode->name;
    // std::string command(buf);
    // size_t pos1 = command.find(' ');
    // size_t pos2 = command.find(' ', pos1 + 1);
    // std::string action = command.substr(0, pos1);
    // std::string target = command.substr(pos1 + 1, pos2 - pos1 - 1);
    // std::string message = command.substr(pos2 + 1);

    // if (action == "/send") {
    //     std::string sysshow;
    //     sysshow += "[" + sockname + "]" + " -> " + "[" + target + "]" + " : " + message;
    //     printf("%s\n", sysshow.c_str());

    //     if (sockmap.find(target) != sockmap.end()) {
    //         sendMsg(sockmap[target], sysshow.c_str(), sysshow.size());
    //     } else {
    //         std::string retword = "No such user";
    //         sendMsg(socknode, retword.c_str(), retword.size());
    //     }
    // } else if(action == "/exit"){

    //     Disconnect(socknode);

    // } else if(action == "/heart"){

    //     lastHeartTime[sockname] = time(0);
    //     std::string retword = "/heart";
    //     sendMsg(socknode, retword.c_str(), retword.size());
    //     //用户 心跳
    //     sysPrint("[%s] hearting", sockname.c_str());
    
    // }else {
    //     std::string retword = "Invalid command";
    //     sendMsg(socknode, retword.c_str(), retword.size());
    // }
    CMD cmd;
    int ret = readProtoMSG(socknode, cmd, buf);
    if (ret == -1) {
        ERROR_INFO_ERRNO_SOCKNODE_ADD("readProtoMSG err", socknode);
        return;
    }
    if (ret == 0) {
        Disconnect(socknode);
        return;
    }
    switch (cmd)
    {
        // echo.cpp
        case CMD_ECHO:{
            sysPrint("CMD_ECHO from %s", socknode->name);
            dealCmdEcho(socknode , buf);break;
        }              
        case CMD_ECHO_RESP:{
            sysPrint("CMD_ECHO_RESP from %s", socknode->name);
            dealCmdEchoResp(socknode , buf);break;
        }         
        
        // login.cpp
        case CMD_USER_LOGIN:{
            sysPrint("CMD_USER_LOGIN from %s", socknode->name);
            dealCmdUserLogin(socknode , buf);break;
        }           
        case CMD_USER_LOGIN_RESP:{
            sysPrint("CMD_USER_LOGIN_RESP from %s", socknode->name);
            dealCmdUserLoginResp(socknode , buf);break;
        }   
        case CMD_DEV_LOGIN:{
            sysPrint("CMD_DEV_LOGIN from %s", socknode->name);
            dealCmdDevLogin(socknode , buf);break;
        }  
        case CMD_DEV_LOGIN_RESP:{
            sysPrint("CMD_DEV_LOGIN_RESP from %s", socknode->name);
            dealCmdDevLoginResp(socknode , buf);break;
        }
       
       // logout.cpp
        case CMD_USER_LOGOUT:{
            dealCmdUserLogout(socknode , buf);break;
        }
            
        case CMD_USER_LOGOUT_RESP:{
            dealCmdUserLogoutResp(socknode , buf);break;
        }
        case CMD_DEV_LOGOUT:{
            dealCmdDevLogout(socknode , buf);break;
        }
            
        case CMD_DEV_LOGOUT_RESP:{
            dealCmdDevLogoutResp(socknode , buf);break;
        }
            
        // register.cpp
        case CMD_USER_REGISTER:{
            dealCmdUserRegister(socknode , buf);break;
        }
            
        case CMD_USER_REGISTER_RESP:{
            dealCmdUserRegisterResp(socknode , buf);break;
        }
            
        // heart.cpp
        case CMD_HEART:{
            dealCmdHeart(socknode , buf);break;
        }
            
        case CMD_HEART_RESP:{
            dealCmdHeartResp(socknode , buf);break;
        }

        //msg.cpp 
        case CMD_MSG:{
            dealCmdMsg(socknode , buf);break;
        }
            
        case CMD_MSG_RESP:{
            dealCmdMsgResp(socknode , buf);break;
        }

        //notice.cpp   
        case CMD_NOTICE:{
            dealCmdNotice(socknode , buf);break;
        }
            
        case CMD_NOTICE_RESP:{
            dealCmdNoticeResp(socknode , buf);break;
        }
            
        //user_dev.cpp
        case CMD_USER_ADD_DEV:{
            dealCmdUserAddDev(socknode , buf);break;
        }
            
        case CMD_USER_ADD_DEV_RESP:{
            dealCmdUserAddDevResp(socknode , buf);break;
        }
            
        case CMD_USER_DEL_DEV:{
            dealCmdUserDelDev(socknode , buf);break;
        }
            
        case CMD_USER_DEL_DEV_RESP:{
            dealCmdUserDelDevResp(socknode , buf);break;
        }
            
        case CMD_GETLIST:{
            dealCmdGetList(socknode , buf);break;
        }
            
        case CMD_GETLIST_RESP:{
            dealCmdGetListResp(socknode , buf);break;
        }
            
        case CMD_GETSTATUS:{
            dealCmdGetStatus(socknode , buf);break;
        }
            
        case CMD_GETSTATUS_RESP:{
            dealCmdGetStatusResp(socknode , buf);break;
        }
           
        default: {
            // Handle unknown cmd;
            CMD_NOTICE_BODY body;
            memcpy(body.msg,"Invalid command", sizeof("Invalid command"));
            sendProtoMSG(socknode, CMD_NOTICE , (void *)&body);
            break;
        }
    }
}