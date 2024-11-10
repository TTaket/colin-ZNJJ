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

std::map<std::string, SOCKNODE *> sockmap;
int userNameCnt = 0;

fd_set readfds, tmpfds;
int max_sd;


void * dealAcceptConn(void* arg){
    char buf[1024] = {};
    SOCKNODE *sock = (SOCKNODE *)arg;
    SOCKNODE *newnode = acceptConn(sock, "", strlen(""));
    sendMsg(newnode, "enter your name please", strlen("enter your name please"));
    memset(buf, '\0', sizeof(buf));
    int readlen = recvMsg(newnode, newnode->name, sizeof(newnode->name));
    while (sockmap.find(newnode->name) != sockmap.end()) {
        memset(newnode->name ,'\0' , sizeof newnode->name); 
        memset(buf, '\0', sizeof(buf));
        sendMsg(newnode, "已经有这个名字了 请重试", strlen("已经有这个名字了 请重试"));
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
    printf("user: %s connected\n", newnode->name);
    return nullptr;
}

int main() {
    SOCKNODE *serverNode = createSocket("listen", strlen("listen"));
    bindListen(serverNode, SERVER_PORT);
    FullSocketInfo(serverNode);
    ERROR_CHECK_AND_CLOSE;

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
                    printf("user: %s disconnected\n", it->first.c_str());
                    it = sockmap.erase(it);
                
                } else {
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
                    } else {
                        
                        std::string retword = "Invalid command";
                        sendMsg(it->second, retword.c_str(), retword.size());
                    }
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }
}