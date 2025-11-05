#ifndef HEADERS_H
#define HEADERS_H

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

SYMTAB insert_symbol(SYMTAB table, char name[7], int addr, int srcline);

void print_table(SYMTAB table);

void destroy_table(SYMTAB* table);

int symbol_exists(SYMTAB table, char name[7]);

int is_directive(char token[7]);

int is_instruction(char token[7]);

char* get_token(char** line);

int get_address(char** line, int* address);

int get_constant(char** line, char* constant, int* size);

int parse_line(SYMTAB* table, char* line, int lineNumber, int* locationCounter, int* instructionNumber, int* endFlag, FILE* obj, int pass);

void print_error(char* line, int line_number, char* msg);

int same_word(const char* a, const char* b);

int get_integer(char** line, int* integer);

void strip_newline(char* line);

void dangle_free(void** ptr);

int get_program_start(SYMTAB table);

int get_program_end(SYMTAB table);

int get_program_length(SYMTAB table);

void write_record(FILE* obj, SYMTAB table,  char* symbol, char* inst, int address, char* constant, int size);

void string_to_hex(char* constant, char* string);

#endif
