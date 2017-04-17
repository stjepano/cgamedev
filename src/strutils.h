#ifndef STRUTILS_H_
#define STRUTILS_H_

/// Copy str into newly allocated string and return it
char* STR_strdup(const char* str);

/// Parse resolution in format WIDTHxHEIGHT, ex 1024x768
/// If string is in invalid format or WIDTH <= 0 or HEIGHT <= 0 error will be returned
/// If width is NULL it will not be set, string will still be parsed for height
/// If height is NULL it will not be set, string is still parsed for width
/// If both width and height are NULL they will not be set but string will still be parsed
error_t STR_ParseResolution(const char* str, int* width, int* height);

#endif