#include "headers.h"

void strip_newline(char* line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\n' || line[i] == '\r') {
            line[i] = '\0';
            break;
        }
    }
}
