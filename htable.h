#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef htable_header
#define htable_header

typedef struct $linked_list{
	int key; int data; struct $linked_list *next; struct $linked_list *previous;
} linked_list;

//Current table
linked_list** table;

//Functions
void opertation(int read, int address);
void done();
void init();

//Linked List
linked_list* ll_insert(linked_list* head, linked_list* new);
linked_list* ll_delete(linked_list* head, linked_list* item);
linked_list* ll_search(linked_list* head, unsigned int key);
linked_list* ll_new(int key, int data);

//Hash Table
void ht_insert(linked_list** table, int size, linked_list* item);
void ht_delete(linked_list** table, int size, linked_list* item);

//Memory Access and Setting
void put(unsigned int address, int value);
int  get(unsigned int address);

#endif