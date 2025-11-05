#include "headers.h"

void write_record(FILE* obj, SYMTAB table,  char* symbol, char* inst, int address, char* constant, int size) {
    if(same_word(inst, "START")) {
        int start = get_program_start(table);
        int length = get_program_length(table);

        fprintf(obj, "H%-6.6s%06X%06X\n", symbol, start, length);
    } else if (same_word(inst, "BYTE")) {
        fprintf(obj, "T%06X %02X %s\n",address,size,constant);
    } else if (same_word(inst, "WORD")) {
        fprintf(obj, "T%06X %02X %s\n",address,size,constant);
    }
}
