default: build 

.PHONY : build  clean

clean:
	 ls | grep -v "\." | grep -v Makefile | xargs rm 
build:
	gcc -Wall $(filter-out $@,$(MAKECMDGOALS)).c -o $(filter-out $@,$(MAKECMDGOALS))
all:
	gcc -Wall *.c  -o main

