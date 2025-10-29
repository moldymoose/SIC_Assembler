#include "headers.h"

SYMTAB insert_symbol(SYMTAB table, char name[7], int addr, int srcline) {
    SYMBOL* new;

    new = malloc(sizeof(SYMBOL));
    // sets the memory to 0
    memset(new, 0, sizeof(SYMBOL));
    strcpy(new->name, name);
    new->address = addr;
    new->sourceline = srcline;
    new->next = table;

    table = new;

    // Why wouldn't we return table?
    // They're both just addresses, now set to the same address so i guess it doesn't matter?
    return new; 
}
