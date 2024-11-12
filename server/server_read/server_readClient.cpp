#include "./server_read.h"
void dealClientMessage(SOCKNODE * socknode , char * buf){
    std::string sockname = socknode->name;
    std::string command(buf);
    size_t pos1 = command.find(' ');
    size_t pos2 = command.find(' ', pos1 + 1);
    std::string action = command.substr(0, pos1);
    std::string target = command.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string message = command.substr(pos2 + 1);

    if (action == "/send") {
        
        std::string sysshow;
        sysshow += "[" + sockname + "]" + " -> " + "[" + target + "]" + " : " + message;
        printf("%s\n", sysshow.c_str());

        if (sockmap.find(target) != sockmap.end()) {
            sendMsg(sockmap[target], sysshow.c_str(), sysshow.size());
        } else {
            std::string retword = "No such user";
            sendMsg(socknode, retword.c_str(), retword.size());
        }
    } else if(action == "/exit"){

        Disconnect(socknode);

    } else if(action == "/heart"){

        lastHeartTime[sockname] = time(0);
        std::string retword = "/heart";
        sendMsg(socknode, retword.c_str(), retword.size());
        //用户 心跳
        sysPrint("[%s] hearting", sockname.c_str());
    
    }else {
        std::string retword = "Invalid command";
        sendMsg(socknode, retword.c_str(), retword.size());
    }
}