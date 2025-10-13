#include "headers.h"

int is_directive(char* token){

    size_t n = sizeof(DIRECTIVES) / sizeof(DIRECTIVES[0]); // gives the number of elements in the array
    
    for (size_t i = 0; i < n; i++) {
        if (same_word(token, DIRECTIVES[i])) {
            return 1; // it is an instruction
        }
    }

    return 0;
    // maybe swap out for a binary search later
}
