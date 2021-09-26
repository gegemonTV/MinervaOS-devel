#include <string.h>

size_t strlen(
	const char *s)
{
    size_t count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}
