CC = gcc
CFLAGS = -m64


SRC = main.c print_table.c insert_symbol.c symbol_exists.c destroy_table.c is_instruction.c is_directive.c parse_line.c get_token.c get_address.c print_error.c get_constant.c same_word.c get_integer.c strip_newline.c dangle_free.c get_program_length.c get_program_start.c get_program_end.c write_record.c string_to_hex.c get_opcode.c parse_operand.c insert_mrecord.c print_mod_table.c print_erecord.c destroy_mod_table.c
OBJ = $(SRC:.c=.o)
DBG = $(SRC:.c=.dbg)

project2: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c headers.h
	$(CC) $(CFLAGS) -c -g $<

clean:
	rm -f $(OBJ) $(DBG) project2
