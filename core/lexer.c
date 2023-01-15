#include "lexer.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF 4096

#define IS_LINE_FEED(s) (s == 0x0A)
#define IS_SPACE(s) (s == 0x20)
#define IS_SPEC_CHAR(s) (IS_SPACE(s) || IS_LINE_FEED(s))

#define IS_EQUAL(s) (s == 0x3D)
#define IS_MINUS(s) (s == 0x2D)

#define IS_OPEN_BRACKET(s) (s == 0x7B)
#define IS_CLOSE_BRACKET(s) (s == 0x7D)

#define IS_LOWERCASE(s) (s > 0x60 && s < 0x7B)
#define IS_UPPERCASE(s) (s > 0x40 && s < 0x5B)

#define IS_LETTER(s) (IS_LOWERCASE(s) || IS_UPPERCASE(s)) 
#define IS_NUMBER(s) (s >= 0x30 && s <= 0x39)

#define IS_IDENTIFIER(s) (IS_LETTER(s) || IS_NUMBER(s))

#define IS_SINGLE_QUOTE(s) (s == 0x27)
#define IS_DOUBLE_QUOTE(s) (s == 0x22)

#define COPY_BYTES(d, s, cond)  \
    do {                        \
        while(cond)             \
            d++ = s++;          \
        d = '\0';               \
    } while(0)

struct token
{
    char name[64];
    char val[64];
};

static token_t *gen_token(const char *name, const char *value, int n)
{
    token_t *token = (token_t *)malloc(sizeof(token_t));
    memcpy(token->name, name, strlen(name));
    memcpy(token->val, value, n);
    // memccpy(sym->val, value, n, 64);
    token->name[strlen(name)] = '\0';
    token->val[n] = '\0';

#ifdef __DEBUG
    printf("SYM: %s,%s\n", token->name, token->val);
#endif
    return token;
}

static char *scan(char *dest, const char *src)
{
    char *__dest_p = dest;
    while (*src != '\0') {
        if (IS_SPACE(*src) && IS_SPACE(*(src + 1))) {
            src += 2;
            while (IS_SPACE(*src)) ++src;
            --src;
        }
        *__dest_p++ = *src++;
    }
    *__dest_p = '\0';

    return dest;
}

token_t *get_token(const char *src)
{
    char __buff[MAX_BUFF], *__buff_p = __buff;
    int i;
    for (i = 0; *src != '\0'; ++src, ++i) {
        if (IS_SPEC_CHAR(*src))
            --i;
        else if (IS_EQUAL(*src))
            return gen_token("operator", src, 1);
        else if (IS_OPEN_BRACKET(*src))
            return gen_token("separator", src, 1);
        else if (IS_CLOSE_BRACKET(*src))
            return gen_token("separator", src, 1);
        else if (IS_LETTER(*src)) {
            COPY_BYTES(*__buff_p, *src, IS_IDENTIFIER(*src));
            return gen_token("identifier", __buff, strlen(__buff));
            __buff_p = __buff;
        }
        else if (IS_NUMBER(*src))
            return gen_token("literal", src, 1);
        else if (IS_MINUS(*src))
            return gen_token("operator", src, 1);
        else if (IS_SINGLE_QUOTE(*src))
            return gen_token("literal", ++src, 1), ++src;
        else if (IS_DOUBLE_QUOTE(*src))
            return gen_token("literal", src, 1);
    }
}
