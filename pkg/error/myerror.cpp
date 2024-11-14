#include "./myerror.h"
#include "../net/socknode.h"
#include <stdio.h>

int errlistcnt = 0;
FILE * errlogFile ;
ERRORNODE errlist[ERROR_LIST_SIZE];

void sys_err_init() { 
  errlistcnt = 0; 
  errlogFile = fopen("/Users/lijingyang/working/net/pkg/error/error.log", "a");
  if (errlogFile == NULL) {
    perror("Failed to open log file");
    exit(EXIT_FAILURE);
  }
}
void sys_add_error(const char *sys, const int syslen, const char *err,
                   const int len) {
  if (errlistcnt >= ERROR_LIST_SIZE) {
    return;
  }
  snprintf(errlist[errlistcnt].errBuf, syslen + len + 1, "%s:%s", sys, err);
  fprintf(errlogFile, "%s\n", errlist[errlistcnt].errBuf);
  errlistcnt++;
}
void sys_add_error_errno(const char *sys, const int syslen, const char *err,
                         const int len, int errnum) {
  if (errlistcnt >= ERROR_LIST_SIZE) {
    return;
  }
  char *errstr = strerror(errnum);
  snprintf(errlist[errlistcnt].errBuf, syslen + len + strlen(errstr) + 2,
           "%s:%s:%s", sys, err, strerror(errnum));
  fprintf(errlogFile, "%s\n", errlist[errlistcnt].errBuf);
  errlistcnt++;
}
void sys_add_error_errnoandsock(const char *sys, const int syslen,
                                const char *err, const int len, int errnum,
                                SOCKNODE *node) {
  if (errlistcnt >= ERROR_LIST_SIZE) {
    return;
  }
  char *errstr = strerror(errnum);
  char *sockname = node->name;
  snprintf(errlist[errlistcnt].errBuf, syslen + len + strlen(errstr) + strlen(sockname) + 3,
           "%s:%s:%s:%s", sys, err,sockname ,  strerror(errnum));
  fprintf(errlogFile, "%s\n", errlist[errlistcnt].errBuf);
  errlistcnt++;
}

void sys_show_error() {
  int len = errlistcnt;
  for (int i = 0; i < len; i++) {
    printf("%s\n", errlist[i].errBuf);
  }
}

void sys_error_clear() { errlistcnt = 0; }

int sys_error_size() { return errlistcnt; }