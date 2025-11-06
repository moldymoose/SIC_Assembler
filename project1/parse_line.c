#include "headers.h"

int parse_line(SYMTAB* table, MODTAB* mod_table, char* line, int lineNumber, int* locationCounter, int* instructionNumber, int* endFlag, FILE* obj, int pass) {
  char* p = line;                   // pointer to current character parser is on
  char msg[256];                    // error message buffer
  char* symbol = NULL;
  char* inst = NULL;                // stores instruction (or directive)
  char* operand = NULL;             // stores operand for instructions
  
  int address = *locationCounter;   // address of current instruction

  int size;                         // stores size of object code (in bytes)
  char constant[256] = "";          // byte array from constant
  int op_address;

  // Check for comment
  if(*p == '#') {
      return 1;
  }
  // Check if END directive has already been seen
  else if (*endFlag > 0) {
      print_error(line, lineNumber, "Program includes non comment lines after END directive");
      return 0;
  }
  
  
  // Check for symbol
  if(isalpha(*p)){
      symbol = get_token(&p);
  }

  // Read instruction/directive
  inst = get_token(&p);

  // Verify line is not empty, and has instruction/directive
  if(inst == NULL) {
      if(symbol == NULL) {
          print_error(line, lineNumber, "Line cannot be empty.");
      } else {
          snprintf(msg, sizeof(msg), "Label %s has no instruction or directive.", symbol);
          print_error(line, lineNumber, msg);
          dangle_free((void**)&symbol);
      }
      return 0;
  }

  // we only care about adding symbols if we're on pass 1
  if((symbol != NULL) && (pass == 1)){
  // Check if symbol exists before adding to table
      if(!symbol_exists(*table, symbol)) {
  // Check if symbol is instruction or directive before adding to table
          if(is_directive(symbol) || is_instruction(symbol)) {
              snprintf(msg, sizeof(msg), "Label: %s is a reserved keyword.", symbol);
              print_error(line, lineNumber, msg);
              dangle_free((void**)&symbol);
              dangle_free((void**)&inst);
              return 0;
          } else {
              *table = insert_symbol(*table, symbol, *locationCounter, lineNumber);
          }
      } else {
          snprintf(msg, sizeof(msg), "Label: %s already exists in symbol table.", symbol);
          print_error(line, lineNumber, msg);
          dangle_free((void**)&symbol);
          dangle_free((void**)&inst);
          return 0;
      }
  }

  // Handle directives
  if(is_directive(inst)) {
      if(same_word(inst, "START")) {
          // If START appears as first directive the location counter is moved for the first symbol
          if(*instructionNumber == 0) {
              // Verify START directive is provided valid hexidecimal address
              if (get_address(&p, locationCounter)) {
                  if(pass == 1) {
                      // update first start address if you're on pass 1
                      (*table)->address = *locationCounter;
                  }
              } else {
                  print_error(line, lineNumber, "START directive recieved invalid operand.");
                  dangle_free((void**)&inst);
                  return 0;
              }
          } else if (pass == 1) {
              print_error(line, lineNumber, "START directive must occur at begining of program.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "BYTE")) {
          // Verify BYTE directive is provided valid character or hex constant
          if(get_constant(&p, constant, &size)) {
              *locationCounter += size;
          } else {
              print_error(line, lineNumber, "BYTE directive was not provided valid constant.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "WORD")) {
          int integer;  // will be stored in the word
          // Verify WORD directive is provided valid integer value
          if(get_integer(&p, &integer)) {
              if(integer >= -8388608 && integer <= 8388607) {
                  size = 3;
                  sprintf(constant, "%06X", integer);
                  *locationCounter += size;
              } else {
                  snprintf(msg, sizeof(msg), "%d cannot be represented with a 24-bit signed integer.", integer);
                  print_error(line, lineNumber, msg);
                  dangle_free((void**)&inst);
                  return 0;
              }

          } else {
              print_error(line, lineNumber, "WORD directive was not provided valid integer constant.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "RESB")) {
          int numBytes;
          // Verify RESB directive is provided valid integer value
          if(get_integer(&p, &numBytes)) {
              *locationCounter += numBytes;
          } else {
              print_error(line, lineNumber, "RESB directive was not provided valid number of bytes.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "RESW")) {
          int numWords;
          // Verify RESW directive is provided valid integer value
          if(get_integer(&p, &numWords)) {
              *locationCounter += (numWords * 3);
          } else {
              print_error(line, lineNumber, "RESW directive was not provided valid number of words.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "END")) {
          char* label = get_token(&p);
          // If no label is present the program begins at the start directive location
          // I think this error handling might be better handled in pass2
          if(label == NULL || label[0] == '#') {
              ;
          }
          // If label exists, but not in symbol table it is invalid
          else if(!symbol_exists(*table, label)) {
              snprintf(msg, sizeof(msg), "%s is not a valid label to start the program from.", label);
              print_error(line, lineNumber, msg);
              dangle_free((void**)&label);
              return 0;
          }
          dangle_free((void**)&label);
          *endFlag = 1;
      }
  // Instructions increment location counter by 3 bytes
  } else if(is_instruction(inst)) {
      size = 3;
      *locationCounter += size;
      operand = get_token(&p);
      
      if(pass == 2) {
          if(!parse_operand(*table, operand, &op_address)) {
              dangle_free((void**)&symbol);
              dangle_free((void**)&operand);
              dangle_free((void**)&inst);
              return 0;
          }
          *mod_table = insert_mrecord(*mod_table, address + 1);
      }
  // Print error for invalid instruction/directive
  } else {
      snprintf(msg, sizeof(msg), "%s is not a valid instruction or directive.", inst);
      print_error(line, lineNumber, msg);
      dangle_free((void**)&symbol);
      dangle_free((void**)&inst);
      return 0;
  }
  if (pass == 2) {
      write_record(obj, *table, *mod_table, symbol, inst, address, constant, size, op_address);
  }

  // Verify line only has one operand and optional comment
  if (*p != '#' && *p != '\0') {
      printf("%c\n",*p);
      print_error(line, lineNumber, "Line has too many operands.");
      dangle_free((void**)&symbol);
      dangle_free((void**)&inst);
      return 0;
  }

  (*instructionNumber)++; // We've seen an instruction
  dangle_free((void**)&symbol);
  dangle_free((void**)&inst);
  dangle_free((void**)&operand);
  return 1;
}
