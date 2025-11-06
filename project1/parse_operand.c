#include "headers.h"

int parse_operand(SYMTAB table, char* operand, int* op_address) {
    char* p = operand;
    char symbol[7];
    int i = 0;
    SYMBOL* label;

    while(*p != '\0' && *p !=',') {
        symbol[i] = *p;
        p++;
        i++;
    }
    symbol[i] = '\0';

    if(label = symbol_exists(table, symbol)) {
        *op_address = label->address;
    } else {
        printf("ASSEMBLY ERROR: Symbol %s does not exist in file.\n", symbol);
        return 0;
    }

    if(*p == ',') {
        p++;
        if(*p == 'X') {
            *op_address += 0x8000;
        }
    }

    return 1;
}

