all: heapsort quicksort
	
heapsort.o: heapsort.c htable.h
	gcc -c heapsort.c

heapsort: heapsort.o htable.o htable.h
	gcc -o  heapsort heapsort.o htable.o

# htable.o: htable.c htable.h
# 	gcc -c htable.c

quicksort.o: quicksort.c htable.h
	gcc -c quicksort.c

quicksort: quicksort.o htable.o htable.h
	gcc -o  quicksort quicksort.o htable.o

htable.o: htable.c htable.h
	gcc -c htable.c

# quicksort.o: quicksort.c
# 	gcc -c quicksort.c

# quicksort: quicksort.o
# 	gcc -o quicksort quicksort.o
clean:
	rm -f quicksort.o
	rm -f quicksort
	rm -f htable.o
	rm -f htable
	rm -f heapsort.o
	rm -f heapsort
