#include <stdio.h>
//literally copy pasted...
void swap(int array[], int firstIndex,int secondIndex);
void quickSort(int a[], int begin, int end);
int main( int argc, char *argv[] ) {
        int arr[6] ={3,2,1,4,5,6};
        quickSort(arr,0,5);
        
        int i;
        for (i=0;i < sizeof (arr)/sizeof(int) ;i++) {
        printf("%d\n",arr[i]);
        }

        return 0;
}

int inPlacePartitioning(int A[], int begin, int end){
        int pivotIndex= begin + end/2;
        int pivotValue=A[pivotIndex];
        while(begin <= end){
                if(A[begin] >= pivotValue && A[end] < pivotValue){
                swap(A,begin,end);
                }
                if(A[begin] < pivotValue) begin++;
                if(A[end] >= pivotValue) end--;
        }
        return begin;
}

void swap(int array[], int firstIndex,int secondIndex){
        int tmp= array[firstIndex];
        array[firstIndex]=array[secondIndex];
        array[secondIndex]=tmp;
}

void quickSort(int A[], int begin, int end){
        //You may want to swap (A[pivotIndex], A[end]) and
        //start from end-1, then return it to its place.
       
        int pivot = inPlacePartitioning(A, begin, end);
        quickSort(A, begin, pivot-1);
        quickSort(A, pivot+1, end);
}