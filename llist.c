/*
 * listtest.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ldata.h"
#include "llist.h"

// ==============================================================
// Utility operations
// ==============================================================

struct LNode *create_new_node(struct LData *data){
	struct LNode *fin = malloc(sizeof(struct LNode));
	fin->data = data; 
	fin->next = NULL;
	return fin;
}

struct LList *create_empty_list(){
	struct LList *fin = malloc(sizeof(struct LList)); 

	struct LData *data = create_empty_data();

	struct LNode *root     = create_new_node(data); 
	struct LNode *sentinal = create_new_node(data);

	fin->root = root;
	fin->root->next = sentinal;
	fin->sentinal = sentinal;
	fin->size = 0;

	return fin;
}

void clear_list(struct LList *list){
	struct LNode* itr_node = list->root;
	struct LNode* hold;
	
	int count = list->size;
	while(itr_node != NULL || list->size == 0){
		count--;
		hold = itr_node->next;
		free(itr_node);
		itr_node = hold;
		list->size--;
	}
	list->size++;

	list = create_empty_list();

}

void swap_elems(struct LList *list, int idx1, int idx2){
	struct LNode* hold1 = list->root;
	struct LNode* hold2 = list->root;

	int count = 0;
	while(count < idx1){
		hold1 = hold1->next;
		count++;
	}
	count = 0;
	while(count < idx2){
		hold2 = hold2->next;
		count++;
	}

	swap_data(hold1->data, hold2->data);

}


void print_list(struct LList *list){
	int count;
	int size = list->size;

	if(size == 0){
		printf("[ ]: %d\n", size);
		return;
	}

	struct LNode* itr_node = list->root;

	printf("[");	
	for(count = 0; count < size; count++){
		print_data(itr_node->data);
		itr_node = itr_node->next;
		if(count != size-1){
			printf(", ");
		}

	}
	printf("]: %d\n", size); 
}


// ==============================================================
// Query functions (no side effects)
// ==============================================================

// Checks if the list is empty
int is_empty(struct LList *list){
	if(list->size == 0)
		return 1;

	return 0;
}

// Returns the size of the list
int size(struct LList *list){
	return list->size;
}

// Checks of the list contains the specified data
// Uses the are_equal operation of LData
int contains(struct LList *list, struct LData *data){
	struct LNode *itr_node = list->root; 

	int count;
	for(count = 0; count < size(list); count++){
		if(data == itr_node->data)
			return 1;

		itr_node = itr_node->next; 
		count++;
	}
	return 0; 
}

// ==============================================================
// Add operations
// ==============================================================

// Adds the specified element to the specified position
void add_elem(struct LList *list, struct LData *data, int idx){
	struct LNode *add = malloc(sizeof(struct LNode));
	struct LNode *itr_node = list->root;

	add->data = data;

	if(idx == 0){
		add->next = list->root;
		list->root = add;
		list->size++;
		return;
	}

	int count; 
	for(count = 1; count < idx; count++){
		itr_node = itr_node->next;
	}

	add->next = itr_node->next;
	itr_node->next = add;
	list->size++; 
}

// Adds the specified data to the front of the list
void add_first(struct LList *list, struct LData *data){
	struct LNode *add = malloc(sizeof(struct LNode)); 

	add->data = data; 
	add->next = list->root;
	list->root = add;
	list->size++;
}

// Adds the specified data to the end of the list
void add_last(struct LList *list, struct LData *data){
	print_data(data); printf("\n");
	if(list->size == 0){
		struct LNode *add = malloc(sizeof(struct LNode)); 

		add->data = data; 
		add->next = list->root;
		list->root = add;
		list->size++;
		return;
	}
	struct LNode *add = create_new_node(data); 
	add->data = data; 

	struct LNode *itr_node = list->root;
	while(itr_node->next->next != list->sentinal){
		itr_node = itr_node->next;
	}
	itr_node->next = add; 
	add->next = list->sentinal; 
	list->size++; 
}


// ==============================================================
// Get operation
// ==============================================================

// Returns a handle (pointer) to the element of the list at the specified position
struct LData *get_elem(struct LList *list, int idx){
	struct LNode* itr_node = list->root;
	int count;
	
	for(count = 0; count < idx; count++){
		itr_node = itr_node->next;
	}

	return itr_node->data;
}

// ==============================================================
// Remove operations
// ==============================================================

// Removes and returns the specified element from the specified position
struct LData *rem_elem(struct LList *list, int idx){
	if(idx == 0) return rem_first(list);
	if(idx == list->size) return rem_last(list);

	struct LNode *itr_node = list->root;
	struct LData *data_hold;

	int count = 0;
	while(count +1 < idx){
		itr_node = itr_node->next;
		count++;
	}

	data_hold = itr_node->next->data;
	itr_node->next = itr_node->next->next;
	if(list->size == 0){
		return data_hold;
	}
	list->size--;
	return data_hold; 
}

// Removes and returns the first element in the list
// Assumes that the list is not empty
struct LData *rem_first(struct LList *list){
	struct LNode *itr_node = list->root;
	struct LData *data_hold;


	data_hold = itr_node->data;
	list->root = itr_node->next;
	list->size--;
	return data_hold; 

}

// Removes and returns the last element in the list
// Assumes that the list is not empty
struct LData *rem_last(struct LList *list){
	struct LNode *itr_node = list->root; 
	struct LData* data_hold;

	while(itr_node->next->next != list->sentinal)
		itr_node = itr_node->next;

	data_hold = itr_node->next->data; 
	itr_node->next = list->sentinal;
	list->size--; 
	return data_hold;
}

// ==============================================================
// Sort operations
// ==============================================================

// Sorts the list according to the are_ordered operation of LData
void insertion_sort(struct LList *list){
	struct LNode *node_i = list->root;
	struct LNode *node_j;

	int i,j;
	for(i = 0; i < list->size-1; i++){
		j = i;
		node_i = node_i->next;
		node_j = node_i;
		while(j < list->size && !are_ordered(node_i->data, node_j->data)){
			j++;
			swap_elems(list, i, j);
			node_j = node_j->next;
		}
	}
}