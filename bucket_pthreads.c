#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>
#include <pthread.h>

#define n_thread 8

#define tam1 1000
#define tam2 10000
#define tam3 20000
#define bucket_size (tam3 / n_thread) * 2

typedef struct bucket {
	int num;
	int bucket[bucket_size]; 
} Bucket_t;

typedef struct args {
	int *arr;
	int sz;
} Args_t;

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
//void bubble(int *v, int size);

/*
 * Sorting function for pthreads
 * @param *params sole argument for starting routine
 */ 
void *sort_threads(void *params);

int main() {
	/*
	int *vet1 = malloc(sizeof(int)* tam1);
	fill(vet1, tam1);
	//printVec(vet1, tam1);
	bucketSort(vet1, tam1);
	//printVec(vet1, tam1);
	free(vet1);
	*/
		
	int *vet2 = malloc(sizeof(int)* tam2);
	fill(vet2, tam2);
	bucketSort(vet2, tam2);
	free(vet2);
	
	/*
	int *vet3 = malloc(sizeof(int)* tam3);
	fill(vet3, tam3);
	bucketSort(vet3, tam3);
	free(vet3);
	return 0;
	*/
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
	Bucket_t *b = calloc(sizeof(Bucket_t), n_thread); //creates a vector of buckets, initializing with 0
	assert(b);

	pthread_t thr[n_thread];
	Args_t *args = malloc(sizeof(Args_t));
	assert(args);

	args->arr = v; 
	args->sz = size;

	int i, j, idx, res;
	for(i = 0; i < size; ++i) {
		idx = v[i] % n_thread; //calculates the index of the value in the new vector		
		(b[idx].num) += 1;

		b[idx].bucket[(b[idx].num)-1] = v[i];
	}
	
	for(i = 0; i < n_thread; ++i) { //sort each bucket
		if(b[i].num != 0)
			res = pthread_create(&thr[i], NULL, sort_threads, (void *)args);
	}
	
	idx = 0;
	for(i = 0; i < n_thread; ++i) //put all the sorted buckets in the original vector
		for(j = 0; j < b[i].num; ++j)
			v[idx++] = b[i].bucket[j];
	free(b);
	free(args);
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

/*
 * Sorting function for pthreads
 */ 
void *sort_threads(void *params) {
	sort(((Args_t *)params)->arr, ((Args_t *)params)->sz);
}
/*
void bubble(int *v, int size){
	char changed = 'n';
	while (changed == 'n'){
		changed = 'n';
		for (int i=0 ; i<size-1 ; ++i){
			if (v[i] > v[i+1]) {
				int aux = v[i+1];
				v[i+1] = v[i];
				v[i] = aux;
				changed = 'y';
			}
		}
	}
}
*/				