all:
	gcc -ansi -pedantic -Wall -Wextra lexer.c main.c
debug:
	gcc -g3 -ansi -pedantic -Wall -Wextra lexer.c main.c
