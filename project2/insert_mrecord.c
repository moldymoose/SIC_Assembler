#include "headers.h"

MODTAB insert_mrecord(MODTAB table, int addr) {
    MOD_RECORD* new;

    new = malloc(sizeof(MOD_RECORD));
    // sets the memory to 0
    memset(new, 0, sizeof(MOD_RECORD));
    new->start_address = addr;
    new->next = table;

    table = new;

    // Why wouldn't we return table?
    // They're both just addresses, now set to the same address so i guess it doesn't matter?
    return new; 
}
