#include "./server_heart.h"

void* heartcheck(void * arg){
    while(true){
        sysPrint("System Heart Check");
        sleep(120);//每两分钟检查一次
        for(auto it = sockmap.begin(); it != sockmap.end();){
            std::string name = it->first;
            int sd = it->second->connfd;
            if(lastHeartTime.find(name) == lastHeartTime.end()){
                //第一次心跳
                lastHeartTime[name] = time(0);
                continue;
            }
            if(time(0) - lastHeartTime[name] > 90){
                sysPrint("[%s] heart check failed , close connect", name.c_str());
                closeSocket(it->second);
                FD_CLR(sd, &readfds);
                it = sockmap.erase(it);
                lastHeartTime.erase(lastHeartTime.find(name));
            }else{
                ++it;
            }
        }
        updateMaxSD();
    }
}