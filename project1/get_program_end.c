#include "headers.h"

int get_program_end(SYMTAB table) {
    if (table == NULL) {
        printf("ERROR: Table Empty");
        return 0;
    }
    else {
        return table->address;
    }
}
