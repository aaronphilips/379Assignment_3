all: quicksort htable heapsort
	
quicksort:quicksort.o 
	gcc -o quicksort quicksort.o

htable:htable.o
	gcc -o htable htable.o

heapsort:heapsort.o
	gcc -o heapsort heapsort.o

clean:
	rm -f quicksort.o
	rm -f quicksort
	rm -f htable.o
	rm -f htable
	rm -f heapsort.o
	rm -f heapsort
