#include <stdio.h>
//literally copy pasted from notes
//John look at this: http://alienryderflex.com/quicksort/
//didn't use it tho
void swap(int * firstIndex,int * secondIndex);
void quickSort(int a[], int begin, int end);
int main( int argc, char *argv[] ) {
        int arr[6] ={3,2,1,4,5,6};
        quickSort(arr,0,5);
        
        int i;
        for (i=0;i < 6 ;i++) {
        printf("%d\n",arr[i]);
        }

        return 0;
}

int inPlacePartitioning(int A[], int begin, int end){
        int pivotIndex= end;
        int pivotValue=A[pivotIndex];
        printf("pivotIndex:%d\n",pivotIndex);
        printf("pivotValue:%d\n",pivotValue);
        //for swapping
        int i=begin;
        int scan;
        for(scan=begin;scan<end;scan++){
                if(A[scan]<pivotValue){
                      int temp=A[i];
                      A[i]=A[scan];
                      A[scan]=temp;
                      i++;  
                }
        }
        int temp=A[i];
        A[i]=A[end];
        A[end]=temp;
        return i;
}


void quickSort(int A[], int begin, int end){
        //You may want to swap (A[pivotIndex], A[end]) and
        //start from end-1, then return it to its place.
        while(begin<end){
                int pivot = inPlacePartitioning(A, begin, end);
                if(pivot-begin<end-pivot){
                        quickSort(A, begin, pivot-1);
                        begin=pivot+1;    
                }
                else{
                        quickSort(A, pivot+1, end);
                        end=pivot-1;
                }       
                     
        }
        
}