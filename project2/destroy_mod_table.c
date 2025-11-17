#include "headers.h"

void destroy_mod_table(MODTAB* table) {

    if(*table == NULL) {
        return;
    } else {
        destroy_mod_table(&((*table)->next));
        free(*table);
        *table = NULL;
    }
}
