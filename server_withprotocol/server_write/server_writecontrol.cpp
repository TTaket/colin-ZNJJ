#include "./server_write.h"

void * control(void * arg){
    char buf[SEND_BUF_SIZE];
    sysPrint("Control start");
    while(true){
        memset(buf, 0, SEND_BUF_SIZE);
        scanf("%99[^\n]" , buf);
        getchar();
        std::string command(buf);
        size_t pos1 = command.find(' ');
        size_t pos2 = command.find(' ', pos1 + 1);
        std::string action = command.substr(0, pos1);
        std::string target = command.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string message = command.substr(pos2 + 1);

        if(action == "/send"){
            if(sockmap.find(target) != sockmap.end()){
                sendMsg(sockmap[target], message.c_str(), message.size());
            }else{
                sysPrint("No such user");
            }
        }
        else if(action == "/exit"){
            isRunning = false;
            break;
        }else if(action == "/add"){
            usermap[target] = message;
            sysPrint("Add user [%s] pwd [%s] success", target.c_str() , message.c_str());
        }
        else{
            sysPrint("aInvalid command[%s] [%s] [%s]" , action.c_str(), target.c_str(), message.c_str());
        }
    }
    return nullptr;
}