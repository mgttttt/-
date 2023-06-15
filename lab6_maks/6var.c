#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // количество предметов
#define W 14 // вместимость рюкзака

int weights[N] = {5, 10, 6, 5}; 
int values[N] = {3, 5, 4, 2}; 
int max_value = 0; 

pthread_mutex_t lock; 
void *knapsack(void *arg) {
    int start = *((int *) arg); 
    int end = start + N/4; 

    int dp[end+1][W+1];
    for (int i = 0; i <= end; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= W; j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= end; i++) {
        for (int j = 1; j <= W; j++) {
            if (weights[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = (values[i-1] + dp[i-1][j-weights[i-1]]) > dp[i-1][j] ?
                           (values[i-1] + dp[i-1][j-weights[i-1]]) : dp[i-1][j];
            }
        }
    }
    int local_max = 0;
    for (int i = start; i < end; i++) {
        if (dp[i][W] > local_max) {
            local_max = dp[i][W];
        }
    }
    pthread_mutex_lock(&lock);
    if (local_max > max_value) {
        max_value = local_max;
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    pthread_mutex_init(&lock, NULL);

    int indexes[4] = {0, N/4, N/2, 3*N/4};
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, knapsack, &indexes[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Max value: %d\n", max_value);

    pthread_mutex_destroy(&lock);

    return 0;
}