#makefile
hw5: main.o animal.o
	gcc -o rescuebin main.o animal.o

main.o: main.c
	gcc -c main.c

animal.o: animal.c animal.h
	gcc -c animal.c