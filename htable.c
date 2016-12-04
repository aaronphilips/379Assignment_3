#include "htable.h"


#define table_size 2000
#define window_size 20
#define page_size 2

int current_window_usage = -1; 
FILE * fp;

void opertation(unsigned int address){
	if(current_window_usage == -1){
		current_window_usage = window_size;
	}

	int pageNumber = address / page_size;
	char buff[20];
	sprintf(buff, "%d", pageNumber);

	if(current_window_usage == 1){
		fprintf(fp, "%s\n", buff);
		current_window_usage = window_size;
	}
	
	else{
		fprintf(fp, "%s,",buff);
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
	fclose(fp);

	//Not Certain as to why i need to do this
	fp = fopen("filename.csv", "r");

	if(fp == NULL){
		printf("Failed to open file \n");
	}

	char buff[1024];
	int windowArray[window_size];
	memset(windowArray, -1, sizeof(int) * window_size);
	int windowSet = 0;
	
	while(fgets(buff, 1024, fp))
    {
    	int numberOfPages = 0;
    	char* token;
    	memset(windowArray, -1, sizeof(int) * window_size);
    	token =  strtok(buff, ",");
    	while(token != NULL){
    		
    		int num = strtol(token, NULL, 10);
    		if(!doesNumberExistInArray(windowArray, num, window_size)){
    			numberOfPages++;
    		}
    		
    		//Get next token
    		token = strtok(NULL, ",");
    	}

    	printf("%d window has working set size of %d\n", windowSet , numberOfPages);
    	windowSet++;

    }
}

int doesNumberExistInArray(int * array, int number, int size){
	int i;
	for(i = 0; i < size; i++){
		int temp = array[i];
		if (number == temp){
			return 1;
		}
	}

	insertIntoArray(array, number, size);
	return 0;
}

void insertIntoArray(int* array, int number, int size){
	int i;
	for(i = 0; i < size; i++){
		int temp = array[i];
		if (temp == -1){
			array[i] = number;
			return;
		}
	}
	printf("Array is full that you are inserting into.\n");
}

void done(){
	int i;
	printStatistics();
	for(i=0; i<table_size; i++){
		linked_list* head = table[i];
		//Clean up all linked list elements
		freeLinkedList(head);
	}

	free(table);
	fclose(fp);
}

void freeLinkedList(linked_list* head){
	
	while(head != NULL){
		linked_list* temp = head;
		head = head->next;
		free(temp);
	}
}
void init(){
	
	fp = fopen("filename.csv","w+");

	table = (linked_list **)calloc(table_size,sizeof(linked_list*));
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
	opertation(address);
}

int get(unsigned int address){
	
	linked_list* head = table[address%table_size];
	linked_list* list = ll_search(head,address);
	opertation(address);
	return list->data;
	
}

// int main(){
// 	/* This process function generates a number of integer */
// /* keys and sorts them using bubblesort.               */
// 	int N, i, j, k, t, min, f;
// 	scanf ("%d", &N);
// 	init ();

// 	/* Generate the sorting problem (just random numbers) */
// 	for (i = 0; i < N; i++){
// 	 	int randomNumber = lrand48();
// 	 	put(i, randomNumber);
// 	}

// 	/* Sort the numbers */
// 	for (i = 0; i < N-1; i++) {
// 		for (j = i+1, f = min = get (i), k = i; j < N; j++){
			
// 			if ((t = get (j)) < min) {
// 			k = j;
// 			min = t;
// 			}
// 		}

// 		put (i, min);
// 		put (k, f);
// 	}
// 	done ();
// }



