all: heapsort quicksort
	
heapsort.o: heapsort.c simulator.h
	gcc -c heapsort.c

heapsort: heapsort.o simulator.o simulator.h
	gcc -o  heapsort heapsort.o simulator.o

quicksort.o: quicksort.c simulator.h
	gcc -c quicksort.c

quicksort: quicksort.o simulator.o simulator.h
	gcc -o  quicksort quicksort.o simulator.o

simulator.o: simulator.c simulator.h
	gcc -c simulator.c


clean:
	rm -f quicksort.o
	rm -f quicksort
	rm -f simulator.o
	rm -f simulator
	rm -f heapsort.o
	rm -f heapsort
