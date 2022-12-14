#include "handle.h"

const char *read_def(const char *path, char *dest, size_t n)
{
    FILE *__fd;
    if (!(__fd = fopen(path, "r")))
        return NULL;

    int __i = 0, __c;
    char *__dest = dest;
    while ((__c = fgetc(__fd)) != EOF && __i++ < n)
        *__dest++ = __c;
    *__dest = '\0';
    
    return dest;
}

const char *rem_spaces(char *dest, const char *src)
{
    char *__dest;
    for (__dest = dest; *src != '\0'; src++)
        if (*src != ' ') *__dest++ = *src;
    *__dest = '\0';

    return dest;
}
