#include <time.h>
#include "simulator.h"
int psize;
int winsize;

void printHeap(int size){
	int i;
	for (i = 0; i < size; i++){
		printf("%d\n", get(i));
	}
}

void makeMaxHeap(int size){
	int value, iCurrentNode, iCheckingNode, child;
	for(iCurrentNode = 1; iCurrentNode < size; iCurrentNode++){
		
		value = get(iCurrentNode);
		iCheckingNode = iCurrentNode;
		child = (iCheckingNode-1) / 2;
		
		int temp = get(child);
		while(iCheckingNode > 0 && get(child) < value){
			put(iCheckingNode, get(child));
			iCheckingNode = child;
			child = (iCheckingNode -1)/2;
		}

		put(iCheckingNode, value);
	}
}

//Re adjusts the array after we take the largest
void reAdjustArray(int range){
	int child, iCurrentNode, value;
	
	child = 1;
	value = get(0);
	iCurrentNode  = 0;
	
	while(child <= range -1){
		
		//find the largest child and make sure we arent going out of range
		if(child+1 <= range-1 && get(child) < get(child+1)){
			child++;
		}

		int temp = get(child);
		if(value < temp){
			put(iCurrentNode, temp);
			iCurrentNode = child;
			child = 2*iCurrentNode+1;
		}

		//If not we are now is a valid heap
		else{
			break;
		}
	}
	
	put(iCurrentNode, value);
}


void heapSort(int size){
	makeMaxHeap(size);
	int i, temp;
	for (i = size-1; i>0 ; i--){
	
		//Swap the first for end
		//Since we can gurantee our first is the largest as it is valid max heap
		temp = get(0);
		put(0, get(i));
		put(i, temp);
		
		reAdjustArray(i);
	}

}
void process(){
	/* This process function generates a number of integer */
	/* keys and sorts them using bubblesort.               */
	unsigned int N, i;
	// printf("Please enter the number of elements: \n");
	// scanf ("%d", &N);
	N=100000;
    init(psize,winsize);
    printf("got past init \n" );
	srand ( time(NULL) );
	/* Generate the sorting problem (just random numbers) */
	for (i = 0; i < N; i++){
	 	int randomNumber = rand();
	 	put(i, randomNumber % 10000);
	}

	heapSort(N);
	done();
}
int main(int argc, char **argv){
	if(argc!=3)return -1;
	psize=atoi(argv[1]);
	winsize=atoi(argv[2]);
	process();
}




