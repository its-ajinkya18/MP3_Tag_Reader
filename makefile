a.out: main.o view.o edit.o help.o
	gcc -o a.out main.o view.o edit.o help.o
main.o: main.c
	gcc -c main.c
view.o: view.c
	gcc -c view.c
edit.o: edit.c
	gcc -c edit.c
help.o: help.c
	gcc -c help.c
clear:
	rm *.out *.o
