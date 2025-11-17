#include "headers.h"

void string_to_hex(char* constant, char* string) {
    char* p = string;
    constant[0] = '\0';

    while(*p != '\0') {
        char byte[3];
        sprintf(byte, "%02X", *p);
        strcat(constant, byte);
        p++;
    }
}
