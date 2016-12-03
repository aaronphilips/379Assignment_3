all: heapsort
	
heapsort.o: heapsort.c htable.h
	gcc -c heapsort.c

heapsort: heapsort.o htable.o htable.h
	gcc -o  heapsort heapsort.o htable.o

htable.o: htable.c htable.h
	gcc -c htable.c

clean:
	rm -f quicksort.o
	rm -f quicksort
	rm -f htable.o
	rm -f htable
	rm -f heapsort.o
	rm -f heapsort
