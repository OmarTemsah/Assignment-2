#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define M 1000
#define P 500
#define N 700
#define NUM_THREADS 4

int A[M][P];
int B[P][N];
int C[M][N];

struct thread_region {
    int start;
    int end;
};


void *MatrixMultiplication(void *threadrgn) {

    struct thread_region *region;
    region = (struct thread_region *) threadrgn;
    
    int i, j, k;
    for (i = region->start; i < region->end; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < P; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    pthread_exit(NULL);
}



int main() {
    pthread_t threads[NUM_THREADS];
    struct thread_region thread_region_array[NUM_THREADS];
    int rc,t;
    void *status;

    // Initialize matrices

    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            A[i][j] = i+j;
        }
    }
    for (i = 0; i < P; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = i-j;
        }
    }

    // Record start time
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        thread_region_array[t].start = t * (M / NUM_THREADS);
        thread_region_array[t].end = (t + 1) * (M / NUM_THREADS);
        
        //if we have an odd number of rows then M/NUM_THREADS will miss the remaining rows at the end of the matrix
        if(t==NUM_THREADS-1){
        	        thread_region_array[t].end = M;
        }
        
        rc = pthread_create(&threads[t], NULL, MatrixMultiplication, (void *) &thread_region_array[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threads[t], NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    // Record end time
    gettimeofday(&end_time, NULL);
    double elapsed_seconds = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Elapsed time: %f seconds\n", elapsed_seconds);




    printf("Multiplication done successfully\n");

    pthread_exit(NULL);
    return 0;
}
