#include <stdio.h>
#include <sys/time.h>

#define M 1000
#define P 500
#define N 700


int A[M][P];
int B[P][N];
int C[M][N];



int main() {

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


    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    // multiply matrices A and B
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < P; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

// Record end time
    gettimeofday(&end_time, NULL);
    double elapsed_seconds = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Elapsed time: %f seconds\n", elapsed_seconds);




    printf("Multiplication done successfully\n");

    return 0;
}