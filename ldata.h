/*
 * data_rec.h
 */

#ifndef LDATA_H_
#define LDATA_H_

struct LData {
	char *word;
	int docID;
	int numOccurrences;
};

struct LData *create_empty_data();

struct LData *create_data(char *word, int docID, int numOccurrences);

int are_ordered(struct LData *data1, struct LData *data2);

int are_equal(struct LData *data1, struct LData *data2);

void swap_data(struct LData *data1, struct LData *data2);

void clear_data(struct LData *data);

void print_data(struct LData *data);

#endif /* LDATA_H_ */