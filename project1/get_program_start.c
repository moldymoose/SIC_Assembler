#include "headers.h"

int get_program_start(SYMTAB table) {
    if (table == NULL) {
        printf("ERROR: Table Empty");
        return 0;
    }
    if (table->next == NULL) {
        return table->address;
    }
    else {
        return get_program_start(table->next);
    }
}
