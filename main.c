#include <stdio.h>
#include "files/handle.h"
#include "lib/string-manip/string_manip.h"
#include "core/lexer.h"

int main(void)
{
    char dest[256], dest2[256];
    read_def("./definitions", dest, 256);
    printf("%s\n", dest);
    tokenize(dest, NULL);
    // str_remove_char(dest2, dest, ' ');
    // printf("%s\n", dest2);

    return 0;
}
