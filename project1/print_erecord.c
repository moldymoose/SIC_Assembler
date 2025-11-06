#include "headers.h"

void print_erecord(FILE* obj, int firstInstruction) {
    fprintf(obj, "E%06X\n", firstInstruction);
}
