#include "strutils.h"

#include <stdlib.h>
#include <string.h>

#define STR_ERR_CODE 1177
#define RESOLUTION_DIVIDER_CHAR 'x'

char* STR_strdup(const char* str)
{
    char* newstr = (char*) malloc(sizeof(char)*(strlen(str)+1));
    newstr[0] = 0;
    strcpy(newstr, str);
    return newstr;
}

error_t STR_ParseResolution(const char* str, int* width, int* height)
{
    const char* resptr = strchr(str, RESOLUTION_DIVIDER_CHAR);
    if (resptr == NULL)
    {
        return Error(STR_ERR_CODE, "Invalid resolution string, expected WIDTHxHEIGHT but got '%s'", str);
    }
    
    resptr++;
    
    int h = atoi(resptr);
    int w = atoi(resptr);
    
    if (height != NULL) (*height) = h;
    if (width != NULL) (*width) = w;

    if ( h <= 0 )
    {
        return Error(STR_ERR_CODE, "Invalid resolution string, expected WIDTHxHEIGHT but got '%s'", str);
    }
    if ( w <= 0 )
    {
        return Error(STR_ERR_CODE, "Invalid resolution string, expected WIDTHxHEIGHT but got '%s'", str);
    }

    return NoError();
}