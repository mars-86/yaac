#ifndef __YAAC_CORE_LEXER_INCLUDED_H__
#define __YAAC_CORE_LEXER_INCLUDED_H__

typedef struct symtab symtab_t;

int tokenize(const char *src, const symtab_t *symtab);

#endif // __YAAC_CORE_LEXER_INCLUDED_H__
