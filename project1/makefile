UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CC = gcc
	CFLAGS = -m64
else ifeq ($(UNAME), AIX)
	CC = xlc
	CFLAGS = -g64
endif

SRC = main.c print_table.c insert_symbol.c symbol_exists.c destroy_table.c is_instruction.c is_directive.c parse_line.c get_token.c get_address.c print_error.c get_constant.c same_word.c get_integer.c strip_newline.c dangle_free.c
OBJ = $(SRC:.c=.o)

project1: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c headers.h
	$(CC) $(CFLAGS) -c -g $<

clean:
	rm -f $(OBJ) project1
