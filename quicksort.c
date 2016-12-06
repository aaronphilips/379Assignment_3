#include <time.h>
#include "simulator.h"

int psize;
int winsize;

int inPlacePartitioning( int begin, int end){
        int pivotIndex= end;
        int pivotValue=get(pivotIndex);
        int i=begin;
        int scan;

        for(scan=begin;scan<end;scan++){
         
                int scanValue=get(scan);
                if(scanValue<pivotValue){
                      int temp=get(i);
                      put(i,scanValue);
                      put(scan,temp);
                      i++;  
                }
        }

        int temp= get(i);
        put(i,get(end));
        put(end,temp);
        return i;
}

void quickSort( int begin, int end){

        while(begin<end){
                int pivot = inPlacePartitioning( begin, end);
                if(pivot-begin<end-pivot){
                        quickSort( begin, pivot-1);
                        begin=pivot+1;    
                }
                else{
                        quickSort( pivot+1, end);
                        end=pivot-1;
                }       
                     
        }
        
}

void process(){
        unsigned int N, i;
        printf("Please enter the number of elements for our sort: \n");
        scanf ("%d", &N);

        init(psize, winsize);
        setTableSize(N);

        srand ( time(NULL) );

        /* Generate the sorting problem (just random numbers) */
        for (i = 0; i < N; i++){
                int randomNumber = rand();
                put(i, randomNumber);
        }

        quickSort(0,N-1);
        done();       
}

int main(int argc, char **argv){
        if(argc!=3)return -1;
        psize=atoi(argv[1]);
	winsize=atoi(argv[2]);
	process(); 
}
	