project1: main.o print_table.o insert_symbol.o symbol_exists.o destroy_table.o is_instruction.o is_directive.o parse_line.o get_token.o get_address.o print_error.o get_constant.o same_word.o get_integer.o strip_newline.o dangle_free.o
	gcc -m64 -o project1 main.o print_table.o insert_symbol.o symbol_exists.o destroy_table.o is_instruction.o is_directive.o parse_line.o get_token.o get_address.o print_error.o get_constant.o same_word.o get_integer.o strip_newline.o dangle_free.o

main.o: main.c headers.h
	gcc -m64 -c -g main.c

print_table.o: print_table.c headers.h
	gcc -m64 -c -g print_table.c

insert_symbol.o: insert_symbol.c headers.h
	gcc -m64 -c -g insert_symbol.c

symbol_exists.o: symbol_exists.c headers.h
	gcc -m64 -c -g symbol_exists.c

destroy_table.o: destroy_table.c headers.h
	gcc -m64 -c -g destroy_table.c

is_instruction.o: is_instruction.c headers.h
	gcc -m64 -c -g is_instruction.c

is_directive.o: is_directive.c headers.h
	gcc -m64 -c -g is_directive.c
	
parse_line.o: parse_line.c headers.h
	gcc -m64 -c -g parse_line.c

get_token.o: get_token.c headers.h
	gcc -m64 -c -g get_token.c

get_address.o: get_address.c headers.h
	gcc -m64 -c -g get_address.c

get_constant.o: get_constant.c headers.h
	gcc -m64 -c -g get_constant.c

print_error.o: print_error.c headers.h
	gcc -m64 -c -g print_error.c

same_word.o: same_word.c headers.h
	gcc -m64 -c -g same_word.c

get_integer.o: get_integer.c headers.h
	gcc -m64 -c -g get_integer.c

strip_newline.o: strip_newline.c headers.h
	gcc -m64 -c -g strip_newline.c

dangle_free.o: dangle_free.c headers.h
	gcc -m64 -c -g dangle_free.c

clean:
	rm -f *.o *.dbg project1
