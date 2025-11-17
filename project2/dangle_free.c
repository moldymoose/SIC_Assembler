#include "headers.h"

void dangle_free(void** ptr) {
    if(ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}
