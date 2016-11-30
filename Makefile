all: quicksort
	
quicksort:quicksort.o quicksort.h
	gcc -o quicksort quicksort.o
quicksort.o:quicksort.c quicksort.h
	gcc -c quicksort.c


clean:
	rm -f quicksort.o
	rm -f quicksort