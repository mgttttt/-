#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000 
#define NUM_THREADS 4 

int matrix_A[SIZE][SIZE];
int matrix_B[SIZE][SIZE];
int matrix_C[SIZE][SIZE];

void* multiply(void* arg) {
    int thread_id = *((int*)arg); 
    int chunk_size = SIZE / NUM_THREADS;
    int start_row = thread_id * chunk_size;
    int end_row = start_row + chunk_size;


    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix_C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix_A[i][j] = rand() % 10;
            matrix_B[i][j] = rand() % 10;
        }
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &thread_ids[i]);
    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("result:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix_C[i][j]);
        }
        printf("\n");
    }

    return 0;
}