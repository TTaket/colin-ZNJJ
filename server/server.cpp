#include "../header/stdhead.h"
#include "../header/protocol.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <sys/select.h>
#include <unistd.h>

using namespace std;

SOCKNODE *serverNode;
std::map<std::string, SOCKNODE *> sockmap;
std::map<std::string, int> lastHeartTime;//记录上次心跳时间
int userNameCnt = 0;

fd_set readfds, tmpfds;
int max_sd;

void sysPrint(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("[SYS] : ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void updateMaxSD(){
    int t_max_sd = serverNode->connfd;
    for(auto it = sockmap.begin(); it != sockmap.end(); ++it){
        t_max_sd = std::max(t_max_sd, it->second->connfd);
    }
    max_sd = t_max_sd;
}

void* heartcheck(void * arg){
    while(true){
        sysPrint("heart check");
        sleep(120);//每两分钟检查一次
        for(auto it = sockmap.begin(); it != sockmap.end();){
            std::string name = it->first;
            int sd = it->second->connfd;
            if(lastHeartTime.find(name) == lastHeartTime.end()){
                //第一次心跳
                lastHeartTime[name] = time(0);
            }
            if(time(0) - lastHeartTime[name] > 90){
                sysPrint("user: %s heart check failed", name.c_str());
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

void * dealAcceptConn(void* arg){
    SOCKNODE *sock = (SOCKNODE *)arg;
    SOCKNODE *newnode = acceptConn(sock, "", strlen(""));
    sendMsg(newnode, "enter your name please", strlen("enter your name please"));
    int readlen = recvMsg(newnode, newnode->name, sizeof(newnode->name));
    while (sockmap.find(newnode->name) != sockmap.end() || readlen == 0 || newnode->name[0] == '/') {

        if (readlen == 0) 
        {
            closeSocket(newnode);
            return nullptr;
        }else if(strcmp(newnode->name, "/heart") == 0)
        {   
            //心跳包 继续接受
        }else if(newnode->name[0] == '/'){
            sendMsg(newnode, "Invalid name", strlen("Invalid name"));
        }
        else
        {
            sendMsg(newnode, "Name already exists", strlen("Name already exists"));
        }
        memset(newnode->name ,'\0' , sizeof newnode->name); 
        readlen = recvMsg(newnode, newnode->name, sizeof(newnode->name));
    }
    if(readlen == 0){
        closeSocket(newnode);
        return nullptr;
    }
    FullSocketInfo(newnode);
    sockmap[newnode->name] = newnode;
    FD_SET(newnode->connfd, &readfds);
    max_sd = std::max(max_sd, newnode->connfd);
    std::string retword = std::string("欢迎连接server : ") + newnode->name;
    sendMsg(newnode, retword.c_str(), retword.size());
    sysPrint("user: %s connected\n", newnode->name);
    return nullptr;
}

int main() {
    serverNode = createSocket("listen", strlen("listen"));
    bindListen(serverNode, SERVER_PORT);
    FullSocketInfo(serverNode);
    ERROR_CHECK_AND_CLOSE;
    sysPrint("Server start");

    //心跳定期清除
    pthread_t heartThread;
    pthread_create(&heartThread, nullptr, heartcheck, nullptr);
    pthread_detach(heartThread);

    char buf[1024] = {};
    FD_ZERO(&readfds);
    FD_SET(serverNode->connfd, &readfds);
    max_sd = serverNode->connfd;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100 ms

    while (1) {
        tmpfds = readfds;

        int nReadyFd = select(max_sd + 1, &tmpfds, NULL, NULL, &timeout);
        if (nReadyFd < 0 && errno != EINTR) {
            ERROR_INFO_ERRNO_ADD("select error");
            continue;
        }
        if (nReadyFd == 0) {
            continue;
        }

        if (FD_ISSET(serverNode->connfd, &tmpfds)) { // New connection
            pthread_t tid;
            pthread_create(&tid, nullptr, &dealAcceptConn, serverNode);
            pthread_detach(tid);
        }

        for (auto it = sockmap.begin(); it != sockmap.end(); ) {
            int sd = it->second->connfd;
            if (FD_ISSET(sd, &tmpfds)) {
                memset(buf, '\0', sizeof(buf));
                int n = recvMsg(it->second, buf, sizeof(buf));
                if (n == 0) {
                    //close connection
                    closeSocket(it->second);
                    FD_CLR(sd, &readfds);
                    sysPrint("user: %s disconnected\n", it->first.c_str());
                    it = sockmap.erase(it);
                
                } else {

                    printf("user: %s \n", buf);
                    std::string command(buf);
                    size_t pos1 = command.find(' ');
                    size_t pos2 = command.find(' ', pos1 + 1);
                    std::string action = command.substr(0, pos1);
                    std::string target = command.substr(pos1 + 1, pos2 - pos1 - 1);
                    std::string message = command.substr(pos2 + 1);

                    if (action == "/send") {

                        std::string sysshow;
                        sysshow += "[" + it->first + "]" + " -> " + "[" + target + "]" + " : " + message;
                        printf("%s\n", sysshow.c_str());

                        if (sockmap.find(target) != sockmap.end()) {
                            sendMsg(sockmap[target], sysshow.c_str(), sysshow.size());
                        } else {
                            std::string retword = "No such user";
                            sendMsg(it->second, retword.c_str(), retword.size());
                        }
                    } else if(action == "/exit"){
                        closeSocket(it->second);
                        FD_CLR(sd, &readfds);
                        sysPrint("user: %s disconnected\n", it->first.c_str());
                        it = sockmap.erase(it);
                    } else if(action == "/heart"){
                        lastHeartTime[it->first] = time(0);
                        std::string retword = "heart";
                        sendMsg(it->second, retword.c_str(), retword.size());
                        //打印用户收到了心跳包
                        sysPrint("user: %s recv heart", it->first.c_str());
                    }else {
                        std::string retword = "Invalid command";
                        sendMsg(it->second, retword.c_str(), retword.size());
                    }
                    ++it;

                    
                }
            } else {
                ++it;
            }
        }
        updateMaxSD();
    }
}