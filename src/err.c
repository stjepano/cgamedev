#include "err.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERROR_BUF_SZ 1024

static char error_buf[ERROR_BUF_SZ] = {0};



error_t Error(error_t error_code, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(error_buf, ERROR_BUF_SZ, fmt, args);
    va_end(args);
    return error_code;
}


const char* GetError() 
{
    return error_buf;
}

void ClearError()
{
    memset(error_buf, 0, sizeof(char) * ERROR_BUF_SZ);
}