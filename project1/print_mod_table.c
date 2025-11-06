#include "headers.h"

void print_mod_table(FILE* obj, MODTAB table, SYMBOL* start) {

    if(table == NULL) {
        return;
    } else {
        print_mod_table(obj, table->next, start);
        fprintf(obj, "M%06X 04+%s\n", table->start_address, start->name);
    }
}
