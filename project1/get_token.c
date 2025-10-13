#include "headers.h"

char* get_token(char** line) {
    char* p = *line;
    char* start;
    char* token;
    int len;

    while(*p != '\0' && isspace(*p)) {
        p++;
    }
    if(*p == '\0') {
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

    while(*p != '\0' && isspace(*p)) {
        p++;
    }
    *line = p;

    return token;
}
