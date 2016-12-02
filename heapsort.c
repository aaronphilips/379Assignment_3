#include <stdio.h>
#include <time.h>


void printHeap(int heap[], int size){
	int i;
	for (i = 0; i < size; i++){
		printf("%d\n", heap[i]);
	}
}

void makeMaxHeap(int heap[], int size){
	int value, iCurrentNode, iCheckingNode, child;
	for(iCurrentNode = 1; iCurrentNode < size; iCurrentNode++){
		
		value = heap[iCurrentNode];
		iCheckingNode = iCurrentNode;
		child = (iCheckingNode-1) / 2;
		
		while(iCheckingNode > 0 && heap[child] < value){
			heap[iCheckingNode] = heap [child];
			iCheckingNode = child;
			child = (iCheckingNode-1)/2;
		}

		heap[iCheckingNode] = value;
	}
}

//Re adjusts the array after we take the largest
void reAdjustArray(int heap[], int range){
	int child, iCurrentNode, value;
	child = 1;
	value = heap[0];
	iCurrentNode  = 0;
	while(child <= range -1){
		//find the largest child and make sure we arent going out of range
		if(child+1 <= range-1 && heap[child] < heap[child+1]){
			child++;
		}
		//if we find a larger value swap it out
		if(value < heap[child]){
			heap[iCurrentNode] = heap[child];
			iCurrentNode = child;
			child = 2*iCurrentNode+1;
		}
		//If not we are now is a valid heap
		else{
			break;
		}
	}
	heap[iCurrentNode] = value;
}


void heapSort(int heap[], int size){
	makeMaxHeap(heap, size);

	int i, temp;
	for (i = size-1; i>0 ; i--){
	
		//Swap the first for end
		//Since we can gurantee our first is the largest as it is valid max heap
		temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		
		reAdjustArray(heap,i);
	}

}

int main(){
	/* This process function generates a number of integer */
	/* keys and sorts them using bubblesort.               */
	int N, i, j, k, t, min, f;
	printf("Please enter the number of elements: \n");
	scanf ("%d", &N);

	int arr[N];
	srand ( time(NULL) );
	/* Generate the sorting problem (just random numbers) */
	for (i = 0; i < N; i++){
	 	int randomNumber = rand();
	 	arr[i] = randomNumber;
	}

	heapSort(arr, N);
	printf("Sorted from smallest to largest random numbers between 0 - 10000:");
	printHeap(arr, N);
}




