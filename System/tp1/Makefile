default: shell

.PHONY : build  clean  all  debug

clean:
	 ls | grep -v "\." | grep -v Makefile | xargs rm 
build:
	gcc -g -Wall mini_io.c mini_string.c mini_memory.c $(filter-out $@,$(MAKECMDGOALS)).c   -o ./executable/$(filter-out $@,$(MAKECMDGOALS))
shell:
	gcc -g -Wall mini_io.c mini_string.c mini_memory.c mini_shell_2.c  -o ./executable/mini_shell

debug:
	gdb ./main
	
memcheck:
	valgrind --leak-check=yes ./main 
