#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ldata.h"
#include "llist.h"

// ==============================================================
// Data operations
// ==============================================================

struct LData *create_empty_data(){
	struct LData *data = malloc(sizeof(struct LData)); 
	data->word = "";
	data->docID = 0;
	data->numOccurrences = 0;
	return data; 
}


struct LData *create_data(char *word, int docID, int numOccurrences){
	struct LData *data = malloc(sizeof(struct LData)); 
	data->word  = word;
	data->docID = docID;
	data->numOccurrences = numOccurrences;
	return data; 
}


int are_ordered(struct LData *data1, struct LData *data2){
	if(strcmp(data1->word, data2->word)){
		return 1; 
	}
	return 0; 
}


int are_equal(struct LData *data1, struct LData *data2){ 
	if(strcmp(data1->word, data2->word)){
		return 1;
	}
	return 0; 
}


void swap_data(struct LData *data1, struct LData *data2){
	struct LData hold = *data1;
	*data1 = *data2;
	*data2 = hold;
}


void clear_data(struct LData *data){
	data->word = "";
	data->docID = 0;
	data->numOccurrences = 0; 
}


void print_data(struct LData *data){
	printf("(%s, %.1d, %.1d)", data->word, data->docID, data->numOccurrences);
}
