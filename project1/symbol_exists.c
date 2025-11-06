#include "headers.h"

SYMBOL* symbol_exists(SYMTAB table, char name[7]) {
    if (table == NULL) {
        return table;
    } else {
        // printf("comparing %s and %s\n", table->name, name);
        if (same_word(table->name, name)) {
            return table;
        } else {
            return symbol_exists(table->next, name);
        }
    }
}
