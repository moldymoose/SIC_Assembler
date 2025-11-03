#include "headers.h"

int get_program_length(SYMTAB table) {
    return get_program_end(table) - get_program_start(table);
}
