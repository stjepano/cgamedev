#include "strutils.h"

#include <stdlib.h>
#include <string.h>

char* STR_strdup(const char* str)
{
    char* newstr = (char*) malloc(sizeof(char)*(strlen(str)+1));
    newstr[0] = 0;
    strcpy(newstr, str);
    return newstr;
}