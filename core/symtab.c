#include "symtab.h"

struct symbol {
    char name[128];
    char type[64];
    void *addr;
};

struct symtab {
    symbol_t sym;
    struct symtab *next;
};

typedef struct symtab symtab_t;

void create_entry(const char *name, const char *value)
{

}

const void *get_entry(const char *name)
{

}
