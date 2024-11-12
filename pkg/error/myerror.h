#pragma once
#include "../net/socknode.h"
#include <stdio.h>

#define ERROR_BUF_SIZE 1024
#define ERROR_LIST_SIZE 1024

#define ERROR_SYSINFO std::string(std::string(__FILE__)+":"+std::string(__FUNCTION__)+":"+std::to_string(__LINE__)).c_str()

#define ERROR_INFO_ADD(str) sys_add_error(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str))
#define ERROR_INFO_ERRNO_ADD(str) sys_add_error_errno(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str) , errno)
#define ERROR_INFO_ERRNO_SOCKNODE_ADD(str,node) sys_add_error_errnoandsock(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str) , errno , node)

#define ERROR_CHECK_AND_CLOSE if(sys_error_size()){sys_show_error();return -1;}
typedef struct ERRORNODE {
    char errBuf[ERROR_BUF_SIZE];
}ERRORNODE;

void sys_add_error(const char* sys , const int syslen, const char *err , const int len);
void sys_add_error_errno(const char* sys ,const int syslen, const char *err , const int len , int errnum);
void sys_add_error_errnoandsock(const char* sys ,const int syslen, const char *err , const int len , int errnum , SOCKNODE *node);
void sys_show_error();
void sys_error_clear();
int sys_error_size();
//添加到本地文件操作