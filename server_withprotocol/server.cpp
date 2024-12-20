#include "../header/stdhead.h"
#include "../header/config.h"
#include "../pkg/error/myerror.h"
#include "../pkg/net/socknode.h"

#include "./server_tools/server_tools.h"
#include "./server_heart/server_heart.h"
#include "./server_read/server_read.h"
#include "./server_write/server_write.h"
#include "./server_global/server_global.h"

using namespace std;


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

    pthread_t writeThread;
    pthread_create(&writeThread, nullptr, control, nullptr);
    pthread_detach(writeThread);

     // 防止写管道关闭 导致崩溃
    signal(SIGPIPE, SIG_IGN);

    // 初始化日志和错误文件
    sys_err_init();

    char buf[1024] = {};
    FD_ZERO(&readfds);
    FD_SET(serverNode->connfd, &readfds);
    max_sd = serverNode->connfd;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100 ms
    isRunning = true;

    while (isRunning) {
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
                auto dealIte = it++;
                dealClientMessage(dealIte->second, buf);
            } else {
                ++it;
            }
        }
        for (auto it = sockmapUnlogin.begin(); it != sockmapUnlogin.end(); ) {
            int sd = it->second->connfd;
            if (FD_ISSET(sd, &tmpfds)) {
                auto dealIte = it++;
                dealClientMessage(dealIte->second, buf);
            } else {
                ++it;
            }
        }
        updateMaxSD();
    }
}