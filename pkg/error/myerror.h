#include "../net/socknode.h"
#include <stdio.h>

#define ERROR_BUF_SIZE 1024
#define ERROR_LIST_SIZE 1024

#define ERROR_SYSINFO_STR(file, function, line) "file:" #file " function:" #function " line:" #line
#define ERROR_SYSINFO ERROR_SYSINFO_STR(__FILE__, __FUNCTION__, __LINE__)

#define ERROR_INFO_ADD(str) sys_add_error(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str))
#define ERROR_INFO_ERRNO_ADD(str) sys_add_error_errno(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str) , errno)
#define ERROR_INFO_ERRNO_SOCKNODE_ADD(str) sys_add_error_errno(ERROR_SYSINFO , strlen(ERROR_SYSINFO) , str , strlen(str) , errno)

typedef struct ERRORNODE {
    char errBuf[ERROR_BUF_SIZE];
}ERRORNODE;

void sys_add_error(const char* sys , const int syslen, const char *err , const int len);
void sys_add_error_errno(const char* sys ,const int syslen, const char *err , const int len , int errnum);
void sys_add_error_errnoandsock(const char* sys ,const int syslen, const char *err , const int len , int errnum , SOCKNODE *node);
void show_error();
//添加到本地文件操作