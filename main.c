#include <stdio.h>
#include "files/handle.h"

int main(void)
{
    char dest[256], dest2[256];
    read_def("./definitions", dest, 256);
    printf("%s\n", dest);
    rem_spaces(dest, dest);
    printf("%s\n", dest);

    return 0;
}
