#include "headers.h"

void print_table(SYMTAB table) {

    if(table == NULL) {
        return;
    } else {
        print_table(table->next);
        printf("%s\t%X\n", table->name, table->address);
    }
}
