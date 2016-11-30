all: quicksort
	
quicksort:quicksort.o 
	gcc -o quicksort quicksort.o

clean:
	rm -f quicksort.o
	rm -f quicksort
