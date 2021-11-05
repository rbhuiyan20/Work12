all: hw12.o
	gcc -o ls hw12.o

hw12.o: hw12.c
	gcc -c hw12.c

run:
	./ls

clean:
	rm *.o
	rm ls

comprun: all
	./ls