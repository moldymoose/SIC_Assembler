#include "headers.h"

int parse_line(SYMTAB* table, char* line, int lineNumber, int* locationCounter, int* instructionNumber, int* endFlag) {
  char* p = line;                   // pointer to current character parser is on
  char msg[256];                    // error message
  char* symbol = NULL;
  char* inst = NULL;                // stores instruction (or directive)

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

  if(symbol != NULL) {
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
              dangle_free((void**)&symbol);
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
      int constant, size;
      if(same_word(inst, "START")) {
          // If START appears as first directive the location counter is moved for the first symbol
          if(*instructionNumber == 0) {
              // Verify START directive is provided valid hexidecimal address
              if (get_address(&p, locationCounter)) {
                  (*table)->address = *locationCounter;
              } else {
                  print_error(line, lineNumber, "START directive recieved invalid operand.");
                  dangle_free((void**)&inst);
                  return 0;
              }
          } else {
              print_error(line, lineNumber, "START directive must occur at begining of program.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "BYTE")) {
          // Verify BYTE directive is provided valid character or hex constant
          if(get_constant(&p, &constant, &size)) {
              *locationCounter += size;
          } else {
              print_error(line, lineNumber, "BYTE directive was not provided valid constant.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "WORD")) {
          // Verify WORD directive is provided valid integer value
          if(get_integer(&p, &constant)) {
              if(constant >= -8388608 && constant <= 8388607) {
                  *locationCounter += 3;
              } else {
                  snprintf(msg, sizeof(msg), "%d cannot be represented with a 24-bit signed integer.", constant);
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
          // Verify RESB directive is provided valid integer value
          if(get_integer(&p, &constant)) {
              *locationCounter += constant;
          } else {
              print_error(line, lineNumber, "RESB directive was not provided valid number of bytes.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "RESW")) {
          // Verify RESW directive is provided valid integer value
          if(get_integer(&p, &constant)) {
              *locationCounter += (constant * 3);
          } else {
              print_error(line, lineNumber, "RESW directive was not provided valid number of words.");
              dangle_free((void**)&inst);
              return 0;
          }
      } else if(same_word(inst, "END")) {
          char* label = get_token(&p);
          // If no label is present the program begins at the start directive location
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
      *locationCounter += 3;
      dangle_free((void**)&inst);
      return 1;
      // Print error for invalid instruction/directive
  } else {
      snprintf(msg, sizeof(msg), "%s is not a valid instruction or directive.", inst);
      print_error(line, lineNumber, msg);
      dangle_free((void**)&inst);
      return 0;
  }

  // Verify line only has one operand and optional comment
  if (*p != '#' && *p != '\0') {
      printf("%c\n",*p);
      print_error(line, lineNumber, "Line has too many operands.");
      dangle_free((void**)&inst);
      return 0;
  }

  (*instructionNumber)++; // We've seen an instruction
  dangle_free((void**)&inst);
  return 1;
}
