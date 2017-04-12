#ifndef DEFINES_H_
#define DEFINES_H_

#include <stdlib.h>
#include <stdio.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef int bool_t;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MALLOC(sz) malloc((sz))
#define FREE(ptr) if ((ptr) != NULL) { free((ptr)); ptr=NULL; }

#define OK(res) (res) == 0
#define NOTOK(res) (res) != 0
#define ISNULL(ptr) (ptr) == NULL

#ifndef LOGFILE
#define LOGFILE stdout
#endif

#define LOG(msg, ...) fprintf(stderr, (msg), ##__VA_ARGS__)
#define ABORT(msg, ...) { fprintf(stderr, msg, ##__VA_ARGS__); fflush(stderr); exit(222); }

#endif