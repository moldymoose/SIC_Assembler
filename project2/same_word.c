#include "headers.h"


// Aparently the standard C library contains no function to compare strings without case sensitivity so i'll include this one
// Since SIC is not case sensitive
int same_word(const char* a, const char* b) {
    while (*a && *b) {
        if(tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}
