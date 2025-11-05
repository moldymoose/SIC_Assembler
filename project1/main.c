#include "headers.h"

int main(int argc, char* argv[]) {
    FILE* fp;
    FILE* obj;
    char objFilename[256];

    int lineNumber = 1;
    int instructionNumber = 0;
    char line[1024];

    int locationCounter = 0;
    int endFlag = 0;    // End directive has not been seen yet.

    SYMTAB table = NULL;

    // If there are more or less than two arguments passed when running the program throw an error;
    if (argc != 2) {
        printf("PROGRAM USAGE ERROR: Program usage is \"%s <filename>\"\n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("FILE ERROR: %s could not be opened for reading\n", argv[1]);
        return -1;
    }
    
    // fgets reads in a line from the file
    while(fgets(line, sizeof(line), fp) != NULL) {
        strip_newline(line);

        // attempts to parse the line, increments line number
        if(parse_line(&table, line, lineNumber, &locationCounter, &instructionNumber, &endFlag, obj, 1)) {
            // make sure program is still within valid SIC memory;
            if(locationCounter <= 32768) {
                lineNumber++;
            } else {
                print_error(line, lineNumber, "Program has reached end of SIC memory.");
                fclose(fp);
                destroy_table(&table);
                return -1;
            }
        } else {
            // invalid line closes file and clears table memory
            fclose(fp);
            destroy_table(&table);
            table = NULL;
            return -1;
        }
    }

    // verify END directive exists in program
    if(endFlag == 0) {
        printf("ASSEMBLY ERROR: <Program has no END directive.>\n");
        destroy_table(&table);
        fclose(fp);
        return -1;
    }

    print_table(table);

    // rewind file pointer back to beginning for second pass
    rewind(fp);
    lineNumber = 1;
    locationCounter = 0;
    instructionNumber = 0;
    endFlag = 0;


    snprintf(objFilename, sizeof(objFilename), "%s.obj", argv[1]);
    obj = fopen(objFilename, "w");

    if (obj == NULL) {
        printf("FILE ERROR: %s could not be opened for writing\n", objFilename);
        return -1;
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
        strip_newline(line);
        if(parse_line(&table, line, lineNumber, &locationCounter, &instructionNumber, &endFlag, obj, 2)) {
           ;
            // line valid
        }
    }

    destroy_table(&table);
    fclose(fp);
    fclose(obj);
    return 0;
}
