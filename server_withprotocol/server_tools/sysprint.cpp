#pragma once
#include "../../header/stdhead.h"

void sysPrint(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("[SYS] : ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}
