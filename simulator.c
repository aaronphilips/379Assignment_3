#include "simulator.h"

int table_size;
int window_size;
int page_size;
int current_window_usage; 
int * current_window;
int number_of_pages = 0;
int working_set_total = 0;
int number_of_windows = 0;

void recordOperation(unsigned int address){
	
	int pageNumber = address / page_size;
	insertIntoWindowArray(current_window, pageNumber, window_size);
	
	if(current_window_usage == 1){
		current_window_usage = window_size;
		working_set_total += number_of_pages;
		number_of_windows++;

		printf("Window %d had size of %d\n", number_of_windows, number_of_pages);
		
		//Reset the array and reset the number of pages used to 0
		memset(current_window, -1, sizeof(int) * window_size);
		number_of_pages = 0;
	}

	else{
		current_window_usage--;
	}
}


linked_list* ll_insert(linked_list* head, linked_list* new){
	
	new->next=head;
	if(head != NULL)
		head->previous=new;
	
	head=new;
	return head;
}

linked_list* ll_delete(linked_list* head, linked_list* item){
	
	if(item->previous != NULL)
		item->previous->next=item->next;
	if(item->next!=NULL)
		item->next->previous=item->previous;
	if(item==head)
		head=item->next;
	
	return head ;
}

linked_list* ll_search(linked_list* head, unsigned int key){
	for(;head!=NULL; head=head->next)
	{
		if(head->key==key)
			return head;
	}

	return NULL;
}

linked_list* ll_new(int key, int data){	
	
	linked_list* new =(linked_list *) malloc(sizeof(linked_list));
	new->key = key;
	new->data = data;
	new->next = NULL;
	new->previous = NULL;
	return new;
}

void printStatistics(){

	double average_working_set_size = (double)working_set_total/number_of_windows;
	printf("Average working set size over time of execution: %lf\n", average_working_set_size);
}

void printArray(){
	//Start of array
	int i;
	printf("Starting Array: ");
	for(i = 0; i < window_size; i++){
		int temp = current_window[i];
		printf("%d ", temp);
	}
	printf(" Ending Array\n");
}
//Tries to insert that page number into current list if its not already in there
// If it is in there it returns
void insertIntoWindowArray(int* array, int number, int size){
	
	int i;
	for(i = 0; i < size; i++){
		int temp = array[i];
		
		//If it is unitialized insert our new element in there
		if(temp == -1){
			array[i] = number;
			number_of_pages++;
			return;
		}

		if (number == temp){
			return;
		}
	}

	printf("Array is full that you are inserting into. This should not happen.\n");
}

void done(){
	printf("Got to done.\n");
	int i;
	printStatistics();
	for(i=0; i<table_size; i++){
		linked_list* head = table[i];
		//Clean up all linked list elements
		freeLinkedList(head);
	}

	free(table);
	free(current_window);
}

void freeLinkedList(linked_list* head){
	
	while(head != NULL){
		linked_list* temp = head;
		head = head->next;
		free(temp);
	}
}
void init(int psize,int winsize){
	page_size=psize;
	window_size = winsize;
	current_window_usage = winsize;

	current_window = (int *)malloc(sizeof(int)* winsize);
	memset(current_window, -1, sizeof(int) * window_size);
}

void setTableSize(int numOfEntries){
	
	//Simple formula for determining a decent sized table
	table_size = numOfEntries/2 + 1;	
	table = (linked_list **)calloc(table_size, sizeof(linked_list*));
}

//Insert it if it is not in there and swap values if it is
void ht_insert(linked_list** table, int size, linked_list* item){
	
	//Key we are searching for
	int key=item->key;
	table[key%size] = ll_insert(table[key%size],item);
}

void ht_delete(linked_list** table, int size, linked_list* item){
	//log
	int key= item->key;
	table[key%size]=ll_delete(table[key%size],item);
}

void put(unsigned int address, int value){
	linked_list* item = ll_new(address, value);
	ht_insert(table, table_size, item); 
	recordOperation(address);
}

int get(unsigned int address){
	linked_list* head = table[address%table_size];
	linked_list* list = ll_search(head,address);
	recordOperation(address);
	return list->data;
	
}



