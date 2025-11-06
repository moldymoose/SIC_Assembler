#include "headers.h"

char* get_token(char** line) {
    char* p = *line;
    char* start;
    char* token;
    int len;

    while(isspace(*p)) {
        p++;
    }
    if(*p == '\0' || *p == '#') {
        return NULL;
    }
    start = p;
    while(*p != '\0' && !isspace(*p)) {
        p++;
    }
    len = p - start;

    token = malloc(len + 1);
    strncpy(token, start, len);
    token[len] = '\0';

    while(isspace(*p)) {
        p++;
    }
    *line = p;

    return token;
}
