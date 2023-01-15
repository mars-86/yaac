#ifndef __YAAC_CORE_SYMTAB_INCLUDED_H__
#define __YAAC_CORE_SYMTAB_INCLUDED_H__

typedef struct symbol symbol_t;

void create_entry(const char *name, const char *value);
const void *get_entry(const char *name);

#endif // __YAAC_CORE_SYMTAB_INCLUDED_H__
