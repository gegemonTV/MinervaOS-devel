#include <string.h>

char*
strcat(
    char* dst,
    const char* src)
    {
        char* rdest = dst;

        while (*dst)
            dst++;
        
        while(*dst++ == *src++);

        return rdest;
    }