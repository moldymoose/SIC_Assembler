#include "headers.h"

int get_constant(char** line, int* constant, int* size) {
    char* p = *line;
    *size = 0;

    while(*p != '\0' && isspace(*p)) {
        p++;
    }

    if(*p == 'C'){
        p++;
        if(*p == '\'') {
            p++;
            while(*p != '\'' && *p != '\0') {
                *constant = (*constant << 8) | (unsigned char)*p;
                p++;
                *size += sizeof(char);
            }
            if(*p == '\0') {
                return 0;
            } else {
                p++;
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
            *constant = val;
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
