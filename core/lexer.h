#ifndef __YAAC_CORE_LEXER_INCLUDED_H__
#define __YAAC_CORE_LEXER_INCLUDED_H__

typedef struct token token_t;

token_t *get_token(const char *src);

#endif // __YAAC_CORE_LEXER_INCLUDED_H__
