play: first.o
	gcc -Wall -pedantic -g -o play first.o

first.o: first.c
	gcc -c -Wall -pedantic -g first.c