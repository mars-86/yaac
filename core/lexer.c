#include "lexer.h"
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

typedef struct token token_t;

struct symtab
{
    token_t token;
};

static token_t *gen_token(const char *name, const char *value, int n)
{
    token_t *tok = (token_t *)malloc(sizeof(token_t));
    memcpy(tok->name, name, strlen(name));
    memcpy(tok->val, value, n);
    // memccpy(sym->val, value, n, 64);
    tok->name[strlen(name)] = '\0';
    tok->val[n] = '\0';

#ifdef __DEBUG
    printf("SYM: %s,%s\n", tok->name, tok->val);
#endif
    return tok;
}

static int scan(const char *src, token_t **tokens)
{
    char __buff[MAX_BUFF], *__buff_p = __buff;
    int i;
    for (i = 0; *src != '\0'; ++src, ++i) {
        if (IS_SPEC_CHAR(*src))
            --i;
        else if (IS_EQUAL(*src))
            *(tokens + i) = gen_token("operator", src, 1);
        else if (IS_OPEN_BRACKET(*src))
            *(tokens + i) = gen_token("separator", src, 1);
        else if (IS_CLOSE_BRACKET(*src))
            *(tokens + i) = gen_token("separator", src, 1);
        else if (IS_LETTER(*src)) {
            COPY_BYTES(*__buff_p, *src, IS_IDENTIFIER(*src));
            *(tokens + i) = gen_token("identifier", __buff, strlen(__buff));
            __buff_p = __buff;
        }
        else if (IS_NUMBER(*src))
            *(tokens + i) = gen_token("literal", src, 1);
        else if (IS_MINUS(*src))
            *(tokens + i) = gen_token("operator", src, 1);
        else if (IS_SINGLE_QUOTE(*src))
            *(tokens + i) = gen_token("literal", ++src, 1), ++src;
        else if (IS_DOUBLE_QUOTE(*src))
            *(tokens + i) = gen_token("literal", src, 1);
    }
    *(tokens + i) = NULL;

    return 1;
}

static char *scan2(char *dest, const char *src)
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

int tokenize(const char *src, const symtab_t *symtab)
{
    token_t *__tokens[128];
    // scan(src, &__tokens[0]);
    char dest[MAX_BUFF];
    scan2(dest, src);

    printf("%s\n", dest);
    return 1;
    int i;
    printf("Tokens:\n");
    for (i = 0; __tokens[i] != NULL; ++i) {
        printf("%s,%s\n", __tokens[i]->name, __tokens[i]->val);
        free(__tokens[i]);
    }
}
