#ifndef DEFINES_H_
#define DEFINES_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "err.h"

#define ABORT_EXIT_CODE 222

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

#define MALLOC(sz) malloc((sz))
#define FREE(ptr) if ((ptr) != NULL) { free((ptr)); ptr=NULL; }

#define OK(res) (res) == NO_ERROR
#define FAILED(res) (res) != NO_ERROR
#define ISNULL(ptr) (ptr) == NULL

#ifndef LOGFILE
#define LOGFILE stdout
#endif

#define LOG(msg, ...) fprintf(LOGFILE, (msg), ##__VA_ARGS__)
#define ABORT(msg, ...) { fprintf(LOGFILE, msg, ##__VA_ARGS__); fflush(LOGFILE); exit(ABORT_EXIT_CODE); }

#endif