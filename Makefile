all: quicksort htable
	
quicksort:quicksort.o 
	gcc -o quicksort quicksort.o

htable:htable.o
	gcc -o htable htable.o

clean:
	rm -f quicksort.o
	rm -f quicksort
