default: all

.PHONY : build  clean  all  debug

clean:
	 ls | grep -v "\." | grep -v Makefile | xargs rm 
build:
	gcc -Wall $(filter-out $@,$(MAKECMDGOALS)).c -o $(filter-out $@,$(MAKECMDGOALS))
all:
	gcc -g -Wall mini_io.c mini_string.c mini_memory.c mini_systeme.c main.c  -o main
	gcc -g -Wall mini_io.c mini_string.c mini_memory.c mini_systeme.c mini_shell.c  -o mini_shell

debug:
	gdb ./main

memcheck:
	valgrind --leak-check=yes ./main 