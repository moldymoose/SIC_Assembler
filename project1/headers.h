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

typedef struct mod_record {
    int start_address;
    struct mod_record* next;
} MOD_RECORD;
typedef MOD_RECORD* MODTAB;


SYMTAB insert_symbol(SYMTAB table, char name[7], int addr, int srcline);

void print_table(SYMTAB table);

void destroy_table(SYMTAB* table);

SYMBOL* symbol_exists(SYMTAB table, char name[7]);

int is_directive(char token[7]);

int is_instruction(char token[7]);

char* get_token(char** line);

int get_address(char** line, int* address);

int get_constant(char** line, char* constant, int* size);

int parse_line(SYMTAB* table, MODTAB* mod_table, char* line, int lineNumber, int* locationCounter, int* instructionNumber, int* endFlag, FILE* obj, int pass);

void print_error(char* line, int line_number, char* msg);

int same_word(const char* a, const char* b);

int get_integer(char** line, int* integer);

void strip_newline(char* line);

void dangle_free(void** ptr);

SYMBOL* get_program_start(SYMTAB table);

SYMBOL* get_program_end(SYMTAB table);

int get_program_length(SYMTAB table);

void write_record(FILE* obj, SYMTAB table, MODTAB mods,  char* symbol, char* inst, int address, char* constant, int size, int op_address);

void string_to_hex(char* constant, char* string);

int get_opcode(char* instruction);

int parse_operand(SYMTAB table, char* operand, int* op_address);

MODTAB insert_mrecord(MODTAB table, int addr);

void print_mod_table(FILE* obj, MODTAB table, SYMBOL* start);

#endif
