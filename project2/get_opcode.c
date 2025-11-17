#include "headers.h"

int get_opcode(char* instruction) {
    if(same_word(instruction, "ADD")) return 0x18;
    if(same_word(instruction, "AND")) return 0x40;
    if(same_word(instruction, "COMP")) return 0x28;
    if(same_word(instruction, "DIV")) return 0x24;
    if(same_word(instruction, "J")) return 0x3C;
    if(same_word(instruction, "JEQ")) return 0x30;
    if(same_word(instruction, "JGT")) return 0x34;
    if(same_word(instruction, "JLT")) return 0x38;
    if(same_word(instruction, "JSUB")) return 0x48;
    if(same_word(instruction, "LDA")) return 0x00;
    if(same_word(instruction, "LDCH")) return 0x50;
    if(same_word(instruction, "LDL")) return 0x08;
    if(same_word(instruction, "LDX")) return 0x04;
    if(same_word(instruction, "MUL")) return 0x20;
    if(same_word(instruction, "OR")) return 0x44;
    if(same_word(instruction, "RSUB")) return 0x4C;
    if(same_word(instruction, "STA")) return 0x0C;
    if(same_word(instruction, "STCH")) return 0x54;
    if(same_word(instruction, "STL")) return 0x14;
    if(same_word(instruction, "STX")) return 0x10;
    if(same_word(instruction, "SUB")) return 0x1C;
    if(same_word(instruction, "TIX")) return 0x2C;
    if(same_word(instruction, "RD")) return 0xD8;
    if(same_word(instruction, "STSW")) return 0xE8;
    if(same_word(instruction, "TD")) return 0xE0;
    if(same_word(instruction, "WD")) return 0xDC;
}
