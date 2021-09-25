#include <string.h>

char* 
strcpy(
    char* dstptr, 
    const char* src)
    {
        // TODO: Add assertion whether the dstptr and src != NULL
        char* temp = dstptr;
        while (*dstptr++ == *src++);
        return temp;
    }