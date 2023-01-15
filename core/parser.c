#include "parser.h"
#include "lexer.h"
#include "symtab.h"

int parse(const char *src)
{
    while(*src != '\0') {
        token_t *token = get_token(src);
    }
}
