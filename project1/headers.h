#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct symbol {
    char name[7];
    int address;
    int sourceline;
    struct symbol* next;
} SYMBOL;

typedef SYMBOL* SYMTAB;

char* search = " \t\n\r";

const char* DIRECTIVES[] = {"START", "END", "BYTE", "WORD", "RESB", "RESW", "RESR", "EXPORT"};

const char* INSTRUCTIONS[] = {"ADD", "AND", "COMP", "DIV", "J", "JEQ", "JLT", "JSUB", "LDA", "LDCH", "LDL", "LDX", "MUL", "OR", "RD", "RSUB", "STA", "STCH", "STL", "STSW", "STX", "SUB", "TD", "TIX", "WD"};

const char* REQOP[] = {"ADD", "AND", "BYTE", "COMP", "DIV", "EXPORT", "J", "JEQ", "JLT", "JSUB", "LDA", "LDCH", "LDL", "LDX", "MUL", "OR", "RD", "RESB", "RESW", "RESR", "STA", "START", "STCH", "STL", "STSW", "STX", "SUB", "TD", "TIX", "WD" "WORD"};

SYMTAB insert_symbol(SYMTAB table, char name[7], int addr, int srcline);

void print_table(SYMTAB table);

void destroy_table(SYMTAB* table);

int symbol_exists(SYMTAB table, char name[7]);

int is_directive(char token[7]);

int is_instruction(char token[7]);

char* get_token(char** line);

int get_address(char** line, int* address);

int get_constant(char** line, int* constant, int* size);

int parse_line(SYMTAB* table, char line[1025], int lineNumber, int* locationCounter, int* instructionNumber, int* endFlag);

void print_error(char* line, int line_number, char* msg);

int same_word(const char* a, const char* b);

int get_integer(char** line, int* integer);

void strip_newline(unsigned char* line);

void dangle_free(void** ptr);
