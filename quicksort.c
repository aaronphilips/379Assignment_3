#include <time.h>
#include "htable.h"







int inPlacePartitioning( int begin, int end){
        int pivotIndex= end;

        //int pivotValue=A[pivotIndex];
        int pivotValue=get(pivotIndex);
        int i=begin;
        int scan;
        for(scan=begin;scan<end;scan++){
                // if(A[scan]<pivotValue){
                //       int temp=A[i];
                //       A[i]=A[scan];
                //       A[scan]=temp;
                //       i++;  
                // }
                int scanValue=get(scan);
                if(scanValue<pivotValue){
                      int temp=get(i);
                      put(i,scanValue);
                      put(scan,temp);
                      i++;  
                }
        }
        // int temp=A[i];
        // A[i]=A[end];
        // A[end]=temp;

        
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

int main(){
        int N, i;
        printf("Please enter the number of elements: \n");
        scanf ("%d", &N);

        init();
        printf("got past init \n" );
        srand ( time(NULL) );
        /* Generate the sorting problem (just random numbers) */
        for (i = 0; i < N; i++){
                int randomNumber = rand();
                put(i, randomNumber % 10000);
        }

        quickSort(0,N-1);
        done();
}