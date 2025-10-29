#include "headers.h"

void destroy_table(SYMTAB* table) {

    if(*table == NULL) {
        return;
    } else {
        destroy_table(&((*table)->next));
        free(*table);
        *table = NULL;
    }
}
