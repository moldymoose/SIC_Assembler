#include "headers.h"

int get_address(char** line, int* address) {
    char* p;
    long val = strtol(*line, &p, 16);

    if (p == *line) {
        return 0;
    }

    *address = (int)val;
    
    // consume trailing whitespace
    while (*p != '\0' && isspace(*p)) {
        p++;
    }
    *line = p;
    return 1;
}
