#include "headers.h"

const char* INSTRUCTIONS[] = {"ADD", "AND", "COMP", "DIV", "J", "JEQ", "JLT", "JSUB", "LDA", "LDCH", "LDL", "LDX", "MUL", "OR", "RD", "RSUB", "STA", "STCH", "STL", "STSW", "STX", "SUB", "TD", "TIX", "WD"};

int is_instruction(char* token){

    size_t n = sizeof(INSTRUCTIONS) / sizeof(INSTRUCTIONS[0]); // gives the number of elements in the array
    
    for (size_t i = 0; i < n; i++) {
        if (same_word(token, INSTRUCTIONS[i])) {
            return 1; // it is an instruction
        }
    }

    return 0;
    // maybe swap out for a binary search later
}
