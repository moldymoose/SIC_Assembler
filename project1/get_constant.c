#include "headers.h"

int get_constant(char** line, char* constant, int* size) {
    char* p = *line;
    *size = 0;
    char string[128];

    while(*p != '\0' && isspace(*p)) {
        p++;
    }

    if(*p == 'C'){
        p++;
        if(*p == '\'') {
            p++;
            int i = 0;
            while(*p != '\'' && *p != '\0') {
                string[i] = (char) *p;
                i++;
                p++;
                *size += sizeof(char);
            }
            string[i] = '\0';
            if(*p == '\0') {
                return 0;
            } else {
                p++;
                char* newString = toAscii(string);
                string_to_hex(constant, newString);
                free(newString);
            }
        } else {
            return 0;
        }
    } else if(*p == 'X') {
        p++;
        if(*p == '\'') {
            p++;
            int val = (int)strtol(p, &p, 16);
            int digits = 0;
            sprintf(constant, "%X", val);
            do {
                digits++;
                val >>=4;
            } while (val != 0);
            *size = (digits + 1)/2;
            
            if(*p == '\''){
                p++;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    
    // consume trailing whitespace
    while (*p != '\0' && isspace(*p)) {
        p++;
    }
    *line = p;
    return 1;
}
