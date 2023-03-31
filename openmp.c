#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 1000
#define P 500
#define N 700



/*void matrix_multiplication(int A, int B[], int C[])
{
    int i, j, k;
}
*/

int main()
{
    int i, j,k, **A, **B, **C;
    double start, end;
    
    //allocate memory for A,B and C
    A = (int **) malloc(M * sizeof(int *));
    B = (int **) malloc(P * sizeof(int *));
    C = (int **) malloc(M * sizeof(int *));
    
    for (i = 0; i < M; i++) {
        A[i] = (int *) malloc(P * sizeof(int));
        C[i] = (int *) malloc(N * sizeof(int));
    }
    for (i = 0; i < P; i++) {
        B[i] = (int *) malloc(N * sizeof(int));
    }
    
    
    // Initialize matrices A and B with random values
    for(i=0; i<M; i++)
    {
        for(j=0; j<P; j++)
        {
            A[i][j] = rand() % 10;

        }
    }
    
       for(i=0; i<P; i++)
    {
        for(j=0; j<N; j++)
        {

            B[i][j] = rand() % 10;
        }
    }


//record time
    start = omp_get_wtime();
    #pragma omp parallel for private(j,k) shared(A,B,C)
    for(i=0; i<M; i++)
    {
        for(j=0; j<N; j++)
        {
            for(k=0; k<P; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = omp_get_wtime();



    printf("Time taken for multiplication: %f seconds\n", end - start);



    // free the memory allocated for matrices A, B, and C
    for (i = 0; i < M; i++) {
        free(A[i]);
        free(C[i]);
    }
    free(A);
    free(C);
    for (i = 0; i < P; i++) {
        free(B[i]);
    }
    free(B);

    return 0;
}