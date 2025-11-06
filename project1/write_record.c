#include "headers.h"

void write_record(FILE* obj, SYMTAB table, MODTAB mods, char* symbol, char* inst, int address, char* constant, int size, int op_address) {
    if(is_directive(inst)) {
        if(same_word(inst, "START")) {
            int start = get_program_start(table)->address;
            int length = get_program_length(table);

            fprintf(obj, "H%-6.6s%06X%06X\n", symbol, start, length);
        } else if (same_word(inst, "BYTE") || same_word(inst, "WORD")) {
            char* string = constant;
            while (size > 30) {
                fprintf(obj, "T%06X %02X %.60s\n",address,30,string);
                string += 60;
                address += 30;
                size -= 30;
            }
            fprintf(obj, "T%06X %02X %.60s\n",address,size,string);
        }
    } else if (is_instruction(inst)) {
        fprintf(obj, "T%06X %02X %02X %0X\n",address,size,get_opcode(inst), op_address);
    }
}
