#include "headers.h"

int symbol_exists(SYMTAB table, char name[7]) {
    if (table == NULL) {
        return 0;
    } else {
        // printf("comparing %s and %s\n", table->name, name);
        if (same_word(table->name, name)) {
            return 1;
        } else {
            return 0 + symbol_exists(table->next, name);
        }
    }
}
