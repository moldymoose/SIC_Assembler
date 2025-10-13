#include "headers.h"

int get_integer(char** line, int* integer) {
    char* p;
    long val = strtol(*line, &p, 10);

    if (p == *line) {
        return 0;
    }

    *integer = (int)val;
    
    // consume trailing whitespace
    while (*p != '\0' && isspace(*p)) {
        p++;
    }
    *line = p;
    return 1;
}
