#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define bucket_size 100 

typedef struct b {
	int top;
	int bucket[bucket_size]; 
} Bucket_t;

/*
 * Fills the vector according to the size
 * @param *v allocated vector
 * @param size size of the vector
 */
void fill(int *v, int size);

/*
 * Bucket sort algorithm
 * @param *v vector to be divided
 * @param size size of the vector/number of buckets
 */
void bucketSort(int *v, int size);

int main(){
	int *vet1 = malloc(sizeof(int)* 1000);

	fill(vet1, 1000);

	free(vet1);
	return 0;
}

/*
 * Fills the vector according to the size
 */
void fill(int *v, int size) {	
	int i;
	for(i = 0; i < size; ++i)
		v[i] = rand()%RAND_MAX;
}

/*
 * Bucket sort algorithm
 */
void bucketSort(int *v, int size) {
	Bucket_t b[size]; //creates a vector of buckets

	int i;
	for(i = 0; i < size; ++i) //initializes the buckets
		b[i].top = 0;
}
