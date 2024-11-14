#include "server_tools.h"

void updateMaxSD(){
    int t_max_sd = serverNode->connfd;
    for(auto it = sockmap.begin(); it != sockmap.end(); ++it){
        t_max_sd = std::max(t_max_sd, it->second->connfd);
    }
    for(auto it = sockmapUnlogin.begin(); it != sockmapUnlogin.end(); ++it){
        t_max_sd = std::max(t_max_sd, it->second->connfd);
    }
    max_sd = t_max_sd;
}