#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define bucket_size 100 

typedef struct b {
	int num;
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

/*
 * Print a vector
 * @param *v vector to be printed
 * @param size size of the vector
 */
void printVec(int *v, int size);

/*
 * Sort algorithm applied on each bucket (insertion sort)
 */
void sort(int *v, int size);

int main(){
	int *vet1 = malloc(sizeof(int)* 1000);
	fill(vet1, 1000);
	printVec(vet1, 1000);
	printf("\n");
	sort(vet1, 10);
	printVec(vet1, 10);
	free(vet1);

	int *vet2 = malloc(sizeof(int)* 10000);
	fill(vet2, 10000);
	printVec(vet2, 10000);
	printf("\n");
	sort(vet2, 10000);
	printVec(vet2, 10000);
	free(vet2);

	
	int *vet3 = malloc(sizeof(int)* 20000);
	fill(vet3, 20000);
	printVec(vet3, 20000);
	printf("\n");
	sort(vet3, 20000);
	printVec(vet3, 20000);
	free(vet3);
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
	Bucket_t *b = calloc(sizeof(Bucket_t), size); //creates a vector of buckets, initializing with 0
	
	int i, j, idx;

	for(i = 0; i < size; ++i) {
		idx = v[i] % size; //calculates the index of the value in the new vector		
		(b[idx].num) += 1;
		b[idx].bucket[(b[idx].num)-1] = v[i];
	}
	
	for(i = 0; i < size; ++i) { //sort each bucket
		if(b[i].num != 0)
			sort(b[i].bucket, b[i].num);
	}
	
	idx = 0;
	for(i = 0; i < size; ++i) //put all the sorted buckets in the original vector
		for(j = 0; j < b[i].num; ++j)
			v[idx++] = b[i].bucket[j];
	free(b);
}

/*
 * Print a vector
 */
void printVec(int *v, int size) {
	int i;

	for(i = 0; i < size; ++i)
		printf("%d \n", v[i]);
}

/*
 * Sort algorithm applied on each bucket (insertion sort)
 */
void sort(int *v, int size) {
	int i, j, tmp;

	for(i = 1; i < size; ++i) { //i starts in 1 
		tmp = v[i]; //tmp is the current value
		for(j = i - 1; (j >= 0) && (tmp < v[j]); --j) { //j starts one before i, j is between 0 and current
			v[j+1] = v[j]; //change places of the elements
		}
		v[j+1] = tmp;
	}
}

