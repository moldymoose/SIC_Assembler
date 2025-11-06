#include "headers.h"

SYMBOL* get_program_start(SYMTAB table) {
    if (table == NULL) {
        printf("ERROR: Table Empty");
        return table;
    }
    if (table->next == NULL) {
        return table;
    }
    else {
        return get_program_start(table->next);
    }
}
