#include "headers.h"

void print_error(char* line, int line_number, char* msg) {
    printf("ASSEMBLY ERROR: <Line:%d> <%s> <%s>\n", line_number, line, msg);
}
