#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define table_size 2000
#define window_size 10

int current_window_usage = -1; 



typedef struct $linked_list{
	int key; int data; struct $linked_list *next; struct $linked_list *previous;
} linked_list;

//Current table
linked_list** table;

void opertation(int read, int address){
	//unitialized
	if(current_window_usage == -1){
		current_window_usage = 10;
	}
	current_window_usage--;
	if(!read){
		printf("Read from address %d\n", address);
	}
	else{
		printf("Wrote to address %d\n", address);
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

void done(){
	int i;
	for(i=0; i<table_size; i++){
		linked_list* currentNode = table[i];
		while(currentNode != NULL){
			// printf("Current Memory:%d:  Current Value:%d\n", i, currentNode->data);
			// sleep(1);
			currentNode = currentNode->next;
		}

		free(currentNode);
	}
}

void init(){
	
	table =(linked_list **) calloc(table_size,sizeof(linked_list*));
}

//Insert it if it is not in there and swap values if it is
void ht_insert(linked_list** table, int size, linked_list* item){
	//TODO: log something
	
	//Key we are searching for
	int key=item->key;
	//Item in list we are at
	linked_list* head = table[key%size];
	
	linked_list* searchedList = ll_search(head, key);
	if(searchedList == NULL){
		table[key%size]=ll_insert(table[key%size],item);
	}
	//If it already exists swap the data
	else{
		searchedList->data = item->data;
		free(item);
	}
}

void ht_delete(linked_list** table, int size, linked_list* item){
	//log
	int key= item->key;
	table[key%size]=ll_delete(table[key%size],item);
}

void put(unsigned int address, int value){
	
	linked_list* item = ll_new(address, value);
	ht_insert(table, table_size, item); 
	opertation(1, address);
}

int get(unsigned int address){
	
	linked_list* head = table[address%table_size];
	linked_list* list = ll_search(head,address);
	opertation(0, address);
	return list->data;
	
}

int main(){
	/* This process function generates a number of integer */
/* keys and sorts them using bubblesort.               */
	int N, i, j, k, t, min, f;
	scanf ("%d", &N);
	init ();

	/* Generate the sorting problem (just random numbers) */
	for (i = 0; i < N; i++){
	 	int randomNumber = lrand48();
	 	put(i, randomNumber);
	}

	/* Sort the numbers */
	for (i = 0; i < N-1; i++) {
		for (j = i+1, f = min = get (i), k = i; j < N; j++){
			
			if ((t = get (j)) < min) {
			k = j;
			min = t;
			}
		}

		put (i, min);
		put (k, f);
	}
	done ();
}



