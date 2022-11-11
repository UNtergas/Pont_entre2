default: build 

.PHONY : build  clean  all  debug

clean:
	 ls | grep -v "\." | grep -v Makefile | xargs rm 
build:
	gcc -Wall $(filter-out $@,$(MAKECMDGOALS)).c -o $(filter-out $@,$(MAKECMDGOALS))
all:
	gcc -g -Wall *.c  -o main

debug:
	gdb ./main

memcheck:
	valgrind --leak-check=yes ./main 