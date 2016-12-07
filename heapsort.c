#include <time.h>
#include "simulator.h"

int psize;
int winsize;

//This makes a max heap of specific size using our simulator interface
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

//Re adjusts the array to be a max heap up to the range variable
//This is called after each time we pop the max value for a heap
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

		//We now have a valid heap
		else{
			break;
		}
	}
	
	//Do the final swap
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
		
		//After we pop first one off re make a valid heap
		reAdjustArray(i);
	}

}
void process(){

	unsigned int N, i;
	printf("Please enter the number of elements for our sort: \n");
    scanf ("%d", &N);

    init(psize, winsize);
    setTableSize(N);

	//We give it the time so the random numbers are actually random
	srand ( time(NULL) );
	for (i = 0; i < N; i++){
	 	int randomNumber = rand();
	 	put(i, randomNumber);
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




